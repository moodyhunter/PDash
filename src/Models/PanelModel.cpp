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
    { Row, u"row"_qs, { u"Row"_qs, db::DBFieldType::INTEGER } },
    { Column, u"column"_qs, { u"Column"_qs, db::DBFieldType::INTEGER } },
    { RowSpan, u"rowSpan"_qs, { u"RowSpan"_qs, db::DBFieldType::INTEGER } },
    { ColumnSpan, u"columnSpan"_qs, { u"ColumnSpan"_qs, db::DBFieldType::INTEGER } },
};

QString PanelModel::TableName = u"MainWindowPanels"_qs;

PanelModel::PanelModel(QObject *parent) : Base::PDBaseModel<PanelModel>(false, true, parent){};
