#include "PanelModel.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

using namespace PD::Models;
using namespace PD::Database;

enum Roles
{
    Row = Qt::UserRole,
    Column,
    RowSpan,
    ColumnSpan,

    ContentQmlType,
    ContentQmlData,
};

PDModelInfo PanelModel::TypeInfo{
    { Row, u"row", { u"Row"_qs, DBFieldType::INTEGER } },
    { Column, u"column", { u"Column"_qs, DBFieldType::INTEGER } },
    { RowSpan, u"rowSpan", { u"RowSpan"_qs, DBFieldType::INTEGER } },
    { ColumnSpan, u"columnSpan", { u"ColumnSpan"_qs, DBFieldType::INTEGER } },

    { ContentQmlType, u"contentType", { u"ContentType"_qs, DBFieldType::TEXT } },
    { ContentQmlData, u"contentData", { u"ContentData"_qs, DBFieldType::TEXT } },
};

QString PanelModel::TableName = u"MainWindowPanels"_qs;

PDModelOptions PanelModel::ModelOptions{ MF_Editable };

PanelModel::PanelModel(QObject *parent) : Base::PDBaseListModel<PanelModel>(parent)
{
    for (const auto &plugin : pdApp->PluginManager()->AllPlugins())
        m_typeinfo.insert(plugin->pinterface->QmlComponentTypes());
}

QVariantMap PanelModel::getQmlInfoFromType(const QString &type) const
{
    if (!m_typeinfo.contains(type))
        qWarning() << "Unknown plugin component type:" << type;
    const auto &typeinfo = m_typeinfo[type];

    QVariantMap initialProperties;
    for (const auto &[pName, pDescription, pDefaultValue] : typeinfo.Properties)
        initialProperties.insert(pName, pDefaultValue);

    return {
        { u"iconPath"_qs, typeinfo.IconPath },
        { u"description"_qs, typeinfo.Description },
        { u"qmlPath"_qs, typeinfo.QmlFilePath },
        { u"initialProperties"_qs, initialProperties },
        { u"properties"_qs, QVariant::fromValue(typeinfo.Properties) },
    };
}

QStringList PanelModel::getAllQmlTypes() const
{
    return m_typeinfo.keys();
}
