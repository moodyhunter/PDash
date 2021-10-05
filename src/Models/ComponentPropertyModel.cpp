#include "ComponentPropertyModel.hpp"

#include "Core/PluginManager.hpp"
#include "PDApplication.hpp"

using namespace PD::Models;

enum Roles
{
    PropertyName = Qt::UserRole,
    PropertyDescriptions,
    PropertyValue,
    PropertyType,
};

ComponentPropertyModel::ComponentPropertyModel(QObject *parent) : QAbstractListModel(parent)
{
}

void ComponentPropertyModel::setCurrentPropertyValues(const QVariantMap &vals)
{
    for (auto i = 0; i < m_propertyList.count(); i++)
    {
        const auto &pName = std::get<0>(m_propertyList[i]);
        if (vals.contains(pName))
            std::get<2>(m_propertyList[i]) = vals[pName], emit dataChanged(index(i, 0), index(i, 0), { PropertyValue });
    }
}

QVariantMap ComponentPropertyModel::getCurrentPropertyValues() const
{
    QVariantMap result;
    for (const auto &[pName, pDescription, pValue] : m_propertyList)
        result[pName] = pValue;
    return result;
}

QHash<int, QByteArray> ComponentPropertyModel::roleNames() const
{
    return {
        { PropertyName, "name" },
        { PropertyDescriptions, "description" },
        { PropertyValue, "value" },
        { PropertyType, "type" },
    };
}

int ComponentPropertyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_propertyList.size();
}

QVariant ComponentPropertyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto r = index.row();
    switch (static_cast<Roles>(role))
    {
        case PropertyName: return std::get<0>(m_propertyList[r]);
        case PropertyDescriptions: return std::get<1>(m_propertyList[r]);
        case PropertyValue: return std::get<2>(m_propertyList[r]);
        case PropertyType: return std::get<2>(m_propertyList[r]).typeId();
    }

    qWarning() << "Unreachable";
    return QVariant();
}

bool ComponentPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        const auto r = index.row();
        if (role == PropertyValue)
        {
            std::get<2>(m_propertyList[r]) = value;
            emit dataChanged(index, index, { role });
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

Qt::ItemFlags ComponentPropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

const QString &ComponentPropertyModel::getComponentType() const
{
    return componentType;
}

void ComponentPropertyModel::setComponentType(const QString &newComponentType)
{
    if (componentType == newComponentType)
        return;
    componentType = newComponentType;
    emit componentTypeChanged();

    PDPropertyDescriptorList info;
    for (const auto &plugin : pdApp->PluginManager()->AllPlugins())
    {
        const auto types = plugin->pinterface->QmlComponentTypes();
        for (auto it = types.begin(); it != types.end(); it++)
            if (newComponentType == it.key())
                info = it.value().Properties;
    }

    emit rowsRemoved({}, 0, m_propertyList.size(), {});
    m_propertyList.clear();

    m_propertyList = info;
    emit rowsInserted({}, 0, info.size() - 1, {});
}
