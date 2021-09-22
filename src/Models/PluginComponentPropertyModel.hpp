#pragma once

#include "PDPlugin/PluginBase/PDBaseTypes.hpp"

#include <QAbstractItemModel>

class PluginComponentPropertyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PD::Plugin::Types::PDPropertyMap propertyMap READ getPropertyMap WRITE setPropertyMap NOTIFY onPropertyMapChanged)

  public:
    explicit PluginComponentPropertyModel(QObject *parent = nullptr);

    virtual QHash<int, QByteArray> roleNames() const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    PD::Plugin::Types::PDPropertyMap getPropertyMap() const;
    void setPropertyMap(const PD::Plugin::Types::PDPropertyMap &newValue);

    Q_SIGNAL void onPropertyMapChanged(const PD::Plugin::Types::PDPropertyMap &v);

  private:
    PD::Plugin::Types::PDPropertyMap m_propertyMap;
    QList<std::tuple<QString, QString, QVariant>> m_propertyList;
};
