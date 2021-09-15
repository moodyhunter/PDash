#pragma once

#include "Core/PDBaseListModel.hpp"
#include "PDPlugin/PluginBase/PDBaseTypes.hpp"

namespace PD::Models
{
    class PanelModel : public Base::PDBaseListModel<PanelModel>
    {
        Q_OBJECT

      public:
        static PDModelInfo TypeInfo;
        static QString TableName;
        static PDModelOptions ModelOptions;

      public:
        explicit PanelModel(QObject *parent = nullptr);
        virtual ~PanelModel() = default;

        Q_INVOKABLE QVariantMap getQmlInfoFromType(const QString &type);
        Q_INVOKABLE QStringList getAllQmlTypes() const;

      private:
        QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> m_typeinfo;
    };
} // namespace PD::Models
