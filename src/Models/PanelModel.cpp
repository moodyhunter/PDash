#include "PanelModel.hpp"

#include "DB/DBManager.hpp"

using namespace PD::Models;
namespace db = PD::Database;

enum Roles
{
    Row = Qt::UserRole,
    Column,
    RowSpan,
    ColumnSpan,
};

PDModelInfo PanelModel::TypeInfo{
    { Row, u"row", { u"Row"_qs, db::DBFieldType::INTEGER } },
    { Column, u"column", { u"Column"_qs, db::DBFieldType::INTEGER } },
    { RowSpan, u"rowSpan", { u"RowSpan"_qs, db::DBFieldType::INTEGER } },
    { ColumnSpan, u"columnSpan", { u"ColumnSpan"_qs, db::DBFieldType::INTEGER } },
};

QString PanelModel::TableName = u"MainWindowPanels"_qs;

PDModelOptions PanelModel::ModelOptions{ MF_Editable };

PanelModel::PanelModel(QObject *parent) : Base::PDBaseListModel<PanelModel>(parent){};
