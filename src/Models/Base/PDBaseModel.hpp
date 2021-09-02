#pragma once

#include "QObjectPropertyMap.hpp"

#include <QAbstractTableModel>
#include <QMap>
#include <QObject>

class PDBaseListModel : public QObject // QAbstractListModel
{
    Q_OBJECT

  protected:
    PDBaseListModel(QObject *parent = nullptr);
    virtual ~PDBaseListModel();
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
