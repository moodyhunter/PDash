#pragma once

#include "QObjectPropertyMap.hpp"

#include <QAbstractTableModel>
#include <QMap>
#include <QObject>

class PDBaseObjectPropertyModel : public QObject
{
    Q_OBJECT

  protected:
    PDBaseObjectPropertyModel(QObject *parent = nullptr);
    virtual ~PDBaseObjectPropertyModel();
    virtual void OnDatabaseOpened(){};
    virtual QString CreateDBCommand()
    {
        return u""_qs;
    };

  private slots:
    void p_OnDatabaseOpened();

  private:
    const QString m_table;
};
