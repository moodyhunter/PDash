#include "DBManager.hpp"

#include <QSqlDatabase>
#include <QtPlugin>

Q_IMPORT_PLUGIN(QSQLCipherDriverPlugin)

const static QString ConnectionName = u"PDData"_qs;

DBManager::DBManager(QObject *parent) : QObject(parent)
{
}

DBManager::~DBManager()
{
}

bool DBManager::OpenDatabase()
{
    return false;
}

void DBManager::OnProvideDBPassword(const QString &password)
{
    qDebug() << password;
}
