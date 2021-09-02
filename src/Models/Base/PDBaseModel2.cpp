#include "PDBaseModel2.hpp"

#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

using namespace PD::Models::Base;

PDBaseModelImpl::PDBaseModelImpl(const PDModelInfo &typeinfo, const QString &table, bool dynamic, bool editable, QObject *parent)
    : QAbstractListModel(parent), m_tableName(u"pd_data_"_qs + table), m_editable(editable), m_dynamicFetch(dynamic)
{
    for (auto it = typeinfo.begin(); it != typeinfo.end(); it++)
    {
        const auto &[role, roleName, dbInfo] = *it;

        if (role < Qt::UserRole)
            qWarning() << "Found a role smaller than" << Qt::UserRole;

        const auto &[dbName, dbType, dbDefaultValue] = dbInfo;
        Q_UNUSED(dbType);
        m_roleNamesMap.insert(role, roleName.toUtf8());
        m_roleDBNamesMap.insert(roleName, dbName);
    }
}

QVariant PDBaseModelImpl::getDataForRole(Qt::ItemDataRole) const
{
    return {};
}

QHash<int, QByteArray> PDBaseModelImpl::roleNames() const
{
    return m_roleNamesMap;
}

int PDBaseModelImpl::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    if (m_dynamicFetch)
        return m_currentFetchedSize;

    return std::max(m_tableSize, 0ll);
}

bool PDBaseModelImpl::hasChildren(const QModelIndex &) const
{
    return false;
}

bool PDBaseModelImpl::canFetchMore(const QModelIndex &) const
{
    if (m_tableSize < 0)
        return true;

    if (!m_dynamicFetch)
        return false;

    return m_currentFetchedSize < m_tableSize;
}

void PDBaseModelImpl::fetchMore(const QModelIndex &parent)
{
    if (!m_dynamicFetch)
    {
        if (m_tableSize < 0)
        {
            m_tableSize = pdApp->DatabaseManager()->GetTableSize(m_tableName);
            const auto result = pdApp->DatabaseManager()->Select(m_tableName, m_roleDBNamesMap.values());
            m_dbCache.clear();
            for (auto i = 0; i < result.size(); i++)
            {
                QVariantMap roleValueMap;
                for (auto it = result[i].begin(); it != result[i].end(); it++)
                    roleValueMap.insert(m_roleDBNamesMap.key(it.key()), it.value());
                m_dbCache.insert(i, roleValueMap);
            }
        }
        emit rowsInserted(parent, 0, m_tableSize, {});
    }
}

QVariant PDBaseModelImpl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto row = index.row();

    if (!m_dbCache.contains(row))
        return {};

    const auto &cacheItem = m_dbCache[row];

    if (role >= Qt::UserRole)
        return cacheItem[QString::fromUtf8(m_roleNamesMap[role])];

    return getDataForRole((Qt::ItemDataRole) role);
}

Qt::ItemFlags PDBaseModelImpl::flags(const QModelIndex &index) const
{
    qWarning() << "Unimplemented";
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool PDBaseModelImpl::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qWarning() << "Unimplemented";
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

bool PDBaseModelImpl::insertRows(int row, int count, const QModelIndex &parent)
{
    qWarning() << "Unimplemented";
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool PDBaseModelImpl::removeRows(int row, int count, const QModelIndex &parent)
{
    qWarning() << "Unimplemented";
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}
