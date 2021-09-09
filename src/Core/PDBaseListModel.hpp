#pragma once

#include <QAbstractListModel>

namespace PD::Database
{
    struct ModelDBField;
    enum class DBFieldType;
    void pdRegisterDBTable(const QString &tableName, const QList<ModelDBField> &fields);
} // namespace PD::Database

namespace PD::Models
{
    enum PDModelOption
    {
        MF_Editable = 0x0001,
        MF_FetchDynamically = 0x0010
    };
    Q_DECLARE_FLAGS(PDModelOptions, PDModelOption)
    Q_DECLARE_OPERATORS_FOR_FLAGS(PDModelOptions)
    typedef QList<std::tuple<int, QStringView, PD::Database::ModelDBField>> PDModelInfo;
}

namespace PD::Models::Base
{
    class PDBaseListModelImpl : public QAbstractListModel
    {
        constexpr static auto F_CLEAN = 0;
        constexpr static auto F_DIRTY = 1;
        typedef QAtomicInteger<int> AtomicFieldState;

        Q_OBJECT
      public:
        explicit PDBaseListModelImpl(const PDModelInfo &typeinfo, const QString &table, PDModelOptions flags, QObject *parent = nullptr);

        virtual QVariant getDataForRole(Qt::ItemDataRole r) const;

        QHash<int, QByteArray> roleNames() const override final;

        Q_INVOKABLE void saveToDatabase(bool fullSave = false);
        Q_INVOKABLE void appendItem(const QVariantMap &data);
        Q_INVOKABLE void removeItem(const QVariant &v);

        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual bool hasChildren(const QModelIndex &) const override;
        virtual bool canFetchMore(const QModelIndex &parent) const override;
        virtual void fetchMore(const QModelIndex &parent = QModelIndex()) override;

        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
        virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
        virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
        virtual void timerEvent(QTimerEvent *) override;

      private slots:
        void reloadData();

      private:
        const PDModelOptions m_flags;

      private:
        // ======== id,       role,      roleData, dirtyFlag
        QList<QPair<int, QMap<int, QPair<QVariant, AtomicFieldState>>>> m_dbCache;
        QHash<int, QByteArray> m_roleNamesMap;
        QMap<QString, QString> m_roleDBNamesMap;
        QString m_tableName;
        qlonglong m_tableSize = -1;
    };

    template<typename T>
    class PDBaseListModel : public PDBaseListModelImpl
    {
      protected:
        explicit PDBaseListModel(QObject *parent = nullptr) : PDBaseListModelImpl(T::TypeInfo, T::TableName, T::ModelOptions, parent)
        {
            static_assert(std::is_same_v<decltype(T::TableName), QString>);
            static_assert(std::is_same_v<decltype(T::TypeInfo), PDModelInfo>);
            static_assert(std::is_same_v<decltype(T::ModelOptions), PDModelOptions>);
        }
    };
} // namespace PD::Models::Base

template<typename T>
void pdRegisterModelType()
{
    static_assert(std::is_base_of_v<PD::Models::Base::PDBaseListModel<T>, T>, "Type must be a subclass of PDBaseModel");
    QList<PD::Database::ModelDBField> fields;
    for (const auto &[a, b, dbInfo] : T::TypeInfo)
        fields << dbInfo;
    PD::Database::pdRegisterDBTable(T::TableName, fields);
}
