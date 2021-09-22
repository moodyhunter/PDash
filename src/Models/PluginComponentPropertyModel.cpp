#include "PluginComponentPropertyModel.hpp"

enum Roles
{
    PropertyName = Qt::UserRole,
    PropertyDescription,
    PropertyDefaultValue,
};

PluginComponentPropertyModel::PluginComponentPropertyModel(QObject *parent) : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> PluginComponentPropertyModel::roleNames() const
{
    return {
        { PropertyName, "name" },
        { PropertyDescription, "description" },
        { PropertyDefaultValue, "defaultValue" },
    };
}

int PluginComponentPropertyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_propertyMap.size();
}

QVariant PluginComponentPropertyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch ((Roles) role)
    {
        case PropertyName: return std::get<0>(m_propertyList.at(index.row()));
        case PropertyDescription: return std::get<1>(m_propertyList.at(index.row()));
        case PropertyDefaultValue: return std::get<2>(m_propertyList.at(index.row()));
    }

    qWarning() << "Unreachable";
    return QVariant();
}

bool PluginComponentPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

Qt::ItemFlags PluginComponentPropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

PD::Plugin::Types::PDPropertyMap PluginComponentPropertyModel::getPropertyMap() const
{
    return m_propertyMap;
}

void PluginComponentPropertyModel::setPropertyMap(const PD::Plugin::Types::PDPropertyMap &newValue)
{
    if (m_propertyMap == newValue)
        return;

    beginRemoveRows({}, 0, m_propertyMap.size());
    m_propertyMap.clear();
    endRemoveRows();

    beginInsertRows({}, 0, newValue.size());
    m_propertyMap = newValue;
    endInsertRows();

    Q_EMIT onPropertyMapChanged(m_propertyMap);
}
