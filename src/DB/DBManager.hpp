#pragma once

#include <QObject>
#include <QSqlDatabase>

class DBManager : public QObject
{
    Q_OBJECT
  public:
    DBManager(QObject *parent = nullptr);
    virtual ~DBManager();
    Q_INVOKABLE bool openDatabase(const QString &dbName, const QString &password);
};
