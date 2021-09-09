#include "ActivitiesModel.hpp"

#include "DB/DBManager.hpp"

using namespace PD::Models;
namespace db = PD::Database;

enum Roles
{
    Type = Qt::UserRole,
    Title,
    Content,
    Date,
};

PDModelInfo ActivityModel::TypeInfo{
    { Type, u"type", { u"Type"_qs, db::DBFieldType::TEXT } },
    { Title, u"title", { u"Title"_qs, db::DBFieldType::TEXT } },
    { Content, u"content", { u"Content"_qs, db::DBFieldType::TEXT } },
    { Date, u"date", { u"Date"_qs, db::DBFieldType::INTEGER } },
};

QString ActivityModel::TableName = u"Activities"_qs;

PDModelOptions ActivityModel::ModelOptions{ MF_Editable };

ActivityModel::ActivityModel(QObject *parent) : Base::PDBaseListModel<ActivityModel>(parent){};
