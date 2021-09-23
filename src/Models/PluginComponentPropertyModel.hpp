#pragma once

#include "PDPlugin/PluginBase/PDBaseTypes.hpp"

#include <QAbstractItemModel>

namespace PD::Models
{
    typedef QList<PD::Plugin::Types::PDPropertyDescriptor> PDPropertyDescriptorList;

    class PluginComponentPropertyModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(PDPropertyDescriptorList propertyMap READ getPropertyMap WRITE setPropertyMap NOTIFY onPropertyMapChanged)

      public:
        explicit PluginComponentPropertyModel(QObject *parent = nullptr);

        virtual QHash<int, QByteArray> roleNames() const override;

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Editable:
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        PDPropertyDescriptorList getPropertyMap() const;
        void setPropertyMap(const PDPropertyDescriptorList &newValue);

        Q_SIGNAL void onPropertyMapChanged(const PDPropertyDescriptorList &v);

      private:
        PDPropertyDescriptorList m_propertyList;
    };
} // namespace PD::Models
