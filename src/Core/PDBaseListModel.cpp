#include "Core/PDBaseListModel.hpp"

#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

using namespace PD::Models::Base;
using namespace std::chrono_literals;

constexpr static auto FState_CLEAN = true;
constexpr static auto FState_DIRTY = false;

PDBaseListModelImpl::PDBaseListModelImpl(const PDModelInfo &typeinfo, const QString &table, PDModelOptions flags, QObject *parent)
    : QAbstractListModel(parent), m_modelFlags(flags), m_tableName(u"pd_data_"_qs + table)
{
    for (auto it = typeinfo.begin(); it != typeinfo.end(); it++)
    {
        const auto &[role, roleName, dbInfo] = *it;

        if (role < Qt::UserRole)
            qWarning() << "Found a role smaller than" << Qt::UserRole;

        const auto &[dbName, dbType, dbDefaultValue] = dbInfo;
        Q_UNUSED(dbType);
        m_roleNamesMap.insert(role, roleName.toUtf8());
        m_roleDBNamesMap.insert(roleName.toString(), dbName);
    }
    connect(pdApp->DatabaseManager(), &Database::PDDatabaseManager::OnDatabaseOpened, this, &PDBaseListModelImpl::reloadData);
    startTimer(30s);
}

QVariant PDBaseListModelImpl::getDataForRole(Qt::ItemDataRole) const
{
    return {};
}

QHash<int, QByteArray> PDBaseListModelImpl::roleNames() const
{
    return m_roleNamesMap;
}

void PDBaseListModelImpl::saveToDatabase(bool fullSave)
{
    Q_UNUSED(fullSave)
    QStringList fields;
    QVariantList fieldsData;
    for (auto &&[dbId, dbData] : m_dbCache)
    {
        fields.clear();
        fieldsData.clear();
        for (auto it = dbData.begin(); it != dbData.end(); it++)
        {
            const auto fieldName = m_roleDBNamesMap[QString::fromUtf8(m_roleNamesMap[it.key()])];
            auto &&[fieldData, roleState] = it.value();
            if (fullSave || roleState.loadRelaxed() == FState_DIRTY)
                fields << fieldName, fieldsData << fieldData, roleState.storeRelaxed(FState_CLEAN);
        }
        if (!fields.isEmpty())
            pdApp->DatabaseManager()->Update(m_tableName, dbId, fields, fieldsData);
    }
}

void PDBaseListModelImpl::appendItem(const QVariantMap &data)
{
    QStringList dbFields;
    QMap<int, QPair<QVariant, PDAtomicDirtyState>> rolesData;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        const auto roleName = it.key();
        dbFields << m_roleDBNamesMap[roleName];
        rolesData.insert(m_roleNamesMap.key(roleName.toUtf8()), std::make_pair(it.value(), PDAtomicDirtyState{ FState_CLEAN }));
    }
    const auto dbId = pdApp->DatabaseManager()->Insert(m_tableName, dbFields, data.values());
    if (dbId >= 0)
    {
        beginInsertRows({}, m_dbCache.size(), m_dbCache.size());
        m_dbCache.append({ dbId, rolesData });
        m_tableSize++;
        endInsertRows();
    }
}

void PDBaseListModelImpl::removeItem(const QVariant &v)
{
    bool ok = false;
    const auto index = v.toInt(&ok);
    if (!ok)
        return;
    beginRemoveRows({}, index, index);
    m_tableSize--;
    const auto &[dbId, data] = m_dbCache.takeAt(index);
    pdApp->DatabaseManager()->Delete(m_tableName, dbId);
    qDebug() << data;
    endRemoveRows();
}

int PDBaseListModelImpl::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    if (m_modelFlags & MF_FetchDynamically)
        return m_dbCache.size();

    return std::max(m_tableSize, 0ll);
}

bool PDBaseListModelImpl::hasChildren(const QModelIndex &) const
{
    return false;
}

bool PDBaseListModelImpl::canFetchMore(const QModelIndex &) const
{
    if (m_tableSize < 0)
        return true;

    if (m_modelFlags ^ MF_FetchDynamically)
        return false;

    return m_dbCache.size() < m_tableSize;
}

void PDBaseListModelImpl::fetchMore(const QModelIndex &parent)
{
    if (m_modelFlags ^ MF_FetchDynamically)
    {
        if (m_tableSize < 0)
        {
            m_tableSize = pdApp->DatabaseManager()->GetTableSize(m_tableName);
            const auto result = pdApp->DatabaseManager()->Select(m_tableName, m_roleDBNamesMap.values());
            m_dbCache.clear();
            for (auto rit = result.begin(); rit != result.end(); rit++)
            {
                const auto dbId = rit.key();
                const auto dbData = rit.value();
                QMap<int, QPair<QVariant, PDAtomicDirtyState>> roleValueMap;
                const static PDAtomicDirtyState CleanState{ FState_CLEAN };
                for (auto it = m_roleNamesMap.begin(); it != m_roleNamesMap.end(); it++)
                    roleValueMap.insert(it.key(), { dbData[m_roleDBNamesMap[QString::fromUtf8(it.value())]], CleanState });

                m_dbCache << std::make_pair(dbId, roleValueMap);
            }
        }
        emit rowsInserted(parent, 0, m_tableSize - 1, {});
    }
}

QVariant PDBaseListModelImpl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto row = index.row();

    if (m_dbCache.length() < row)
        return QVariant();

    const auto &cacheItem = m_dbCache[row].second;

    if (role >= Qt::UserRole)
        return cacheItem[role].first;

    return getDataForRole((Qt::ItemDataRole) role);
}

Qt::ItemFlags PDBaseListModelImpl::flags(const QModelIndex &) const
{
    return Qt::NoItemFlags;
    //    qWarning() << "Unimplemented";
    //    if (!index.isValid())
    //        return Qt::NoItemFlags;
    //    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool PDBaseListModelImpl::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        m_dbCache[index.row()].second[role].first = value;
        m_dbCache[index.row()].second[role].second.storeRelaxed(FState_DIRTY);
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

bool PDBaseListModelImpl::insertRows(int row, int count, const QModelIndex &parent)
{
    qWarning() << "Unimplemented";
    beginInsertRows(parent, row, row + count - 1);
    //    const auto maxId = *std::max_element(m_dbCache.begin(), m_dbCache.end(), [](const auto &a, const auto &b) { return a.first < b.first; });
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool PDBaseListModelImpl::removeRows(int row, int count, const QModelIndex &parent)
{
    qWarning() << "Unimplemented";
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

void PDBaseListModelImpl::timerEvent(QTimerEvent *)
{
    saveToDatabase();
}

void PDBaseListModelImpl::reloadData()
{
    emit rowsRemoved({}, 0, m_dbCache.size(), {});
    m_dbCache.clear();
    m_tableSize = -1;
    fetchMore();
}
