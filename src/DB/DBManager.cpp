#include "DBManager.hpp"

#include "QSQLCipherDriver/QSQLCipherDriver.hpp"

#include <QMetaEnum>
#include <QtSql>

using namespace PD::Database;

const static auto ConnectionName = u"PDData"_qs;

PDDatabaseManager::PDDatabaseManager(QObject *parent) : QObject(parent)
{
    const static auto dbType = u"PD_QSQLCIPHER"_qs;
    QSqlDatabase::registerSqlDriver(dbType, new QSqlDriverCreator<QSQLCipherDriver>);
    QSqlDatabase::addDatabase(dbType, ConnectionName);
}

PDDatabaseManager::~PDDatabaseManager()
{
    QSqlDatabase::removeDatabase(ConnectionName);
}

bool PDDatabaseManager::openDatabase(const QString &dbName, const QString &password)
{
    auto db = QSqlDatabase::database(ConnectionName);
    db.setDatabaseName(u"/home/leroy/pd_"_qs + dbName + u".db"_qs);
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
    auto db = QSqlDatabase::database(ConnectionName);

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
    auto db = QSqlDatabase::database(ConnectionName);

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
    auto db = QSqlDatabase::database(ConnectionName);
    if (!db.isOpen())
    {
        qWarning() << "Database not opened";
        return;
    }

    QString query;
    query += u"UPDATE %1 SET "_qs.arg(table);
    for (auto i = 0; i < fields.size(); i++)
    {
        const auto field = fields[i];
        query += u"%1=:%1,"_qs.arg(field);
    }
    query.chop(1);
    query += u" WHERE id = %1"_qs.arg(id);

    QSqlQuery q{ db };
    const auto prepare = q.prepare(query);
    if (!prepare)
        qWarning() << "Failed to prepare SQL statement:" << query;
    for (auto i = 0; i < fields.size(); i++)
        q.bindValue(i, fieldData[i]);

    if (!q.exec())
        qWarning() << "Failed to execute query";

    return;
}

bool PDDatabaseManager::CheckAndCreateTable()
{
    static const auto DBFieldTypeMetaEnum = QMetaEnum::fromType<DBFieldType>();

    auto db = QSqlDatabase::database(ConnectionName);
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
            const auto err = q.lastError();
            failedTables << tableName;
            qWarning() << "Failed to execute SQL.";
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
