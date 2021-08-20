#pragma once

#include <QObject>

class DBManager : public QObject
{
    Q_OBJECT
  public:
    DBManager(QObject *parent = nullptr);
    virtual ~DBManager();
    bool OpenDatabase();

  signals:
    void OnDBPasswordRequested();

  public slots:
    void OnProvideDBPassword(const QString &);
};
