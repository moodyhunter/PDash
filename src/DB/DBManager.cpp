#include "DBManager.hpp"

#include "QSQLCipherDriver/QSQLCipherDriver.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <private/qsqldriver_p.h>

const static QString ConnectionName = u"PDData"_qs;

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    QSqlDatabase::registerSqlDriver(u"PD_QSQLCIPHER"_qs, new QSQLCipherDriverCreator);
}

DBManager::~DBManager()
{
    db.close();
}

bool DBManager::openDatabase(const QString &dbName, const QString &password)
{
    if (db.isValid() && db.isOpen())
        return true;
    db = QSqlDatabase::addDatabase(u"PD_QSQLCIPHER"_qs, ConnectionName);
    db.setDatabaseName(dbName + u".db"_qs);
    const auto result = db.open({}, password);

    if (!result)
    {
        db.close();
        return false;
    }

    if (db.tables().isEmpty())
        db.exec(uR"(CREATE TABLE "PD_MetaData" ("DBCreation" NUMERIC NOT NULL);)"_qs);
    return true;
}
