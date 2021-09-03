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
    typedef QList<std::tuple<int, QString, PD::Database::ModelDBField>> PDModelInfo;
}

namespace PD::Models::Base
{
    class PDBaseModelImpl : public QAbstractListModel
    {
        Q_OBJECT
      public:
        explicit PDBaseModelImpl(const PDModelInfo &typeinfo, const QString &table, PDModelOptions flags, QObject *parent = nullptr);

        virtual QVariant getDataForRole(Qt::ItemDataRole r) const;

        QHash<int, QByteArray> roleNames() const override final;

        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual bool hasChildren(const QModelIndex &) const override;
        virtual bool canFetchMore(const QModelIndex &parent) const override;
        virtual void fetchMore(const QModelIndex &parent = QModelIndex()) override;

        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
        virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
        virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

      private slots:
        void reloadData();

      private:
        const PDModelOptions m_flags;

      private:
        QMap<int, QMap<int, QVariant>> m_dbCache;
        QHash<int, QByteArray> m_roleNamesMap;
        QMap<QString, QString> m_roleDBNamesMap;
        QString m_tableName;
        qlonglong m_tableSize = -1;
        qlonglong m_currentFetchedSize = 0;
    };

    template<typename T>
    class PDBaseModel : public PDBaseModelImpl
    {
      protected:
        explicit PDBaseModel(QObject *parent = nullptr) : PDBaseModelImpl(T::TypeInfo, T::TableName, T::ModelOptions, parent)
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
    static_assert(std::is_base_of_v<PD::Models::Base::PDBaseModel<T>, T>, "Type must be a subclass of PDBaseModel");
    QList<PD::Database::ModelDBField> fields;
    for (const auto &[a, b, dbInfo] : T::TypeInfo)
        fields << dbInfo;
    PD::Database::pdRegisterDBTable(T::TableName, fields);
}
