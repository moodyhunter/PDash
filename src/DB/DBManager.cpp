#include "DBManager.hpp"

#include "QSQLCipherDriver/QSQLCipherDriver.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>

const static QString ConnectionName = u"PDData"_qs;

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    QSqlDatabase::registerSqlDriver(u"PD_QSQLCIPHER"_qs, new QSQLCipherDriverCreator);
    QSqlDatabase::addDatabase(u"PD_QSQLCIPHER"_qs, ConnectionName);
}

DBManager::~DBManager()
{
    QSqlDatabase::removeDatabase(ConnectionName);
}

bool DBManager::openDatabase(const QString &dbName, const QString &password)
{
    auto db = QSqlDatabase::database(ConnectionName);
    db.setDatabaseName(dbName + u".db"_qs);
    const auto result = db.open({}, password);

    if (!result)
        return false;

    if (db.tables().isEmpty())
        db.exec(uR"(CREATE TABLE "PD_MetaData" ("DBCreation" NUMERIC NOT NULL);)"_qs);
    return true;
}
