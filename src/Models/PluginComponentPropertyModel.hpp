#pragma once

#include "PDPlugin/PluginBase/PDBaseTypes.hpp"

#include <QAbstractItemModel>

namespace PD::Models
{
    typedef QList<PD::Plugin::Types::PDPropertyDescriptor> PDPropertyDescriptorList;

    class PluginComponentPropertyModel : public QAbstractListModel
    {
        Q_OBJECT

        Q_PROPERTY(QString componentType READ getComponentType WRITE setComponentType NOTIFY componentTypeChanged)

      public:
        Q_INVOKABLE void setCurrentPropertyValues(const QVariantMap &vals);

      public:
        explicit PluginComponentPropertyModel(QObject *parent = nullptr);
        virtual QHash<int, QByteArray> roleNames() const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        const QString &getComponentType() const;
        void setComponentType(const QString &newComponentType);

      signals:
        void componentTypeChanged();

      private:
        PDPropertyDescriptorList m_propertyList;
        QString componentType;
    };
} // namespace PD::Models
