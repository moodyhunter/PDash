#include "PanelModel.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

#include <QVariantMap>

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

QVariantMap PanelModel::getQmlInfoFromType(const QString &type)
{
    const auto &typeinfo = m_typeinfo[type];
    return {
        { u"iconPath"_qs, typeinfo.IconPath },
        { u"description"_qs, typeinfo.Description },
        { u"qmlPath"_qs, typeinfo.QmlFilePath },
    };
}

QStringList PanelModel::getAllQmlTypes() const
{
    return m_typeinfo.keys();
}
