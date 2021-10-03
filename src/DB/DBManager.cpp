#include "DBManager.hpp"

#include "QSQLCipherDriver/QSQLCipherDriver.hpp"

#include <QStandardPaths>
#include <QtSql>

using namespace PD::Database;

const static auto DBConnectionName = u"PDData"_qs;
const static auto QSqlCipherDBType = u"PD_QSQLCIPHER"_qs;

PDDatabaseManager::PDDatabaseManager(QObject *parent) : QObject(parent)
{
    QSqlDatabase::registerSqlDriver(QSqlCipherDBType, new QSqlDriverCreator<QSQLCipherDriver>);
    QSqlDatabase::addDatabase(QSqlCipherDBType, DBConnectionName);
}

PDDatabaseManager::~PDDatabaseManager()
{
    QSqlDatabase::removeDatabase(DBConnectionName);
}

bool PDDatabaseManager::openDatabase(const QString &dbName, const QString &password)
{
    const auto configDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation);
    if (QDir d(configDir); !d.exists())
        d.mkpath(configDir);
    auto db = QSqlDatabase::database(DBConnectionName);
    db.setDatabaseName(u"%1/pd_%2.db"_qs.arg(configDir, dbName));
    qDebug() << db.databaseName();
    const auto result = db.open({}, password);

    if (!result)
        return false;

    if (db.tables().isEmpty())
        db.exec(uR"(CREATE TABLE "PD_MetaData" ("DBCreation" INTEGER NOT NULL);)"_qs);

    CheckAndCreateTable();
    m_isDatabaseOpened = true;
    emit OnDatabaseOpened();
    qDebug() << "DB Opened";
    return true;
}

qlonglong PDDatabaseManager::GetTableSize(const QString &table)
{
    if (!m_isDatabaseOpened)
        return {};
    auto db = QSqlDatabase::database(DBConnectionName);

    auto q = db.exec(u"SELECT COUNT(*) FROM %1;"_qs.arg(table));
    if (!q.isActive())
        qWarning() << q.lastError().text();
    q.first();
    return q.value(0).toLongLong();
}

QMap<int, QVariantMap> PDDatabaseManager::Select(const QString &table, const QStringList &fields, int offset, int limit)
{
    if (!m_isDatabaseOpened)
        return {};
    auto db = QSqlDatabase::database(DBConnectionName);

    auto query = u"SELECT id,%1 FROM %2 ORDER BY id "_qs.arg(fields.join(u", "_qs), table);
    if (limit > 0)
        query += u"LIMIT %1 "_qs.arg(limit);
    if (offset > 0)
        query += u"OFFSET %1 "_qs.arg(offset);
    query += u";";

    auto q = db.exec(query);

    if (!q.isActive())
        qWarning() << q.lastError().text();

    QMap<int, QVariantMap> result;
    while (q.next())
    {
        QVariantMap map;
        for (const auto &field : fields)
            map.insert(field, q.value(field));
        result[q.value(0).toInt()] = map;
    }
    return result;
}

void PDDatabaseManager::Update(const QString &table, int id, const QStringList &fields, const QVariantList &fieldData)
{
    Q_ASSERT_X(fields.size() == fieldData.size(), Q_FUNC_INFO, "Size of data doesn't equal to size of fields.");
    auto db = QSqlDatabase::database(DBConnectionName);
    if (!db.isOpen())
    {
        qWarning() << "Database not opened";
        return;
    }

    QString query;
    query += u"UPDATE %1 SET "_qs.arg(table);
    for (auto i = 0; i < fields.size(); i++)
        query.append(u"%1=:%1,"_qs.arg(fields[i]));

    query.chop(1);
    query += u" WHERE id = %1"_qs.arg(id);

    QSqlQuery q{ db };
    const auto prepare = q.prepare(query);
    if (!prepare)
    {
        qWarning() << "Failed to prepare SQL statement:" << query;
        return;
    }

    for (auto i = 0; i < fields.size(); i++)
        q.bindValue(i, fieldData[i]);

    if (!q.exec())
        qWarning() << "Failed to execute query";

    return;
}

int PDDatabaseManager::Insert(const QString &table, const QStringList &fields, const QVariantList &data)
{
    auto db = QSqlDatabase::database(DBConnectionName);
    if (!db.isOpen())
    {
        qWarning() << "Database not opened";
        return -1;
    }

    QString query;
    QStringList placeholders(fields.size());
    placeholders.fill(u"?"_qs);
    query += u"INSERT INTO %1 (%2) VALUES (%3)"_qs.arg(table, fields.join(u','), placeholders.join(u','));
    QSqlQuery q{ db };

    const auto prepare = q.prepare(query);
    if (!prepare)
    {
        qWarning() << "Failed to prepare SQL statement:" << query;
        return -1;
    }

    for (auto i = 0; i < fields.size(); i++)
        q.bindValue(i, data[i]);

    if (!q.exec())
    {
        qWarning() << "Failed to execute query" << query;
        return -1;
    }

    auto rowIdQuery = db.exec(u"SELECT last_insert_rowid();"_qs);
    rowIdQuery.first();
    return rowIdQuery.value(0).toInt();
}

void PDDatabaseManager::Delete(const QString &table, int id)
{
    auto db = QSqlDatabase::database(DBConnectionName);
    if (!db.isOpen())
    {
        qWarning() << "Database not opened";
        return;
    }
    db.exec(u"DELETE FROM %1 WHERE id = %2"_qs.arg(table).arg(id)).first();
}

bool PDDatabaseManager::CheckAndCreateTable()
{
    static const auto DBFieldTypeMetaEnum = QMetaEnum::fromType<DBFieldType>();

    auto db = QSqlDatabase::database(DBConnectionName);
    if (!db.isOpen())
    {
        qWarning() << "Database not opened";
        return false;
    }

    QStringList failedTables;
    for (auto it = tableFields.begin(); it != tableFields.end(); it++)
    {
        const auto tableName = it.key();
        const auto fields = it.value();

        if (db.tables().contains(tableName))
            continue;

        QString query;
        query += u"CREATE TABLE \"%1\" (\n"_qs.arg(tableName);
        query += uR"("id" INTEGER NOT NULL UNIQUE,)";
        query += u"\n";
        for (const auto &[dbName, dbType, defaultVal] : fields)
        {
            query += uR"("%1" %2 NOT NULL)"_qs.arg(dbName, QString::fromLatin1(DBFieldTypeMetaEnum.valueToKey((int) dbType)));
            if (defaultVal.isValid())
                query += u" DEFAULT " + (defaultVal.typeId() == QMetaType::QString ? (u"\" " + defaultVal.toString() + u"\"") : defaultVal.toString());
            query += u",\n";
        }
        query += uR"(PRIMARY KEY("id" AUTOINCREMENT));)";
        qDebug() << query;
        if (auto q = db.exec(query); !q.isActive())
        {
            failedTables << tableName;
            qWarning() << "Failed to execute SQL." << q.lastError().text();
            return false;
        }
    }

    if (!failedTables.isEmpty())
        qWarning() << "Failed creating tables: " << failedTables;
    return failedTables.isEmpty();
}

void PD::Database::pdRegisterDBTable(const QString &tableName, const QList<ModelDBField> &fields)
{
    PDDatabaseManager::tableFields[u"pd_data_"_qs + tableName] = fields;
}
