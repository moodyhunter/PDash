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
    { Type, u"type"_qs, { u"Type"_qs, db::DBFieldType::TEXT } },
    { Title, u"title"_qs, { u"Title"_qs, db::DBFieldType::TEXT } },
    { Content, u"content"_qs, { u"Content"_qs, db::DBFieldType::TEXT } },
    { Date, u"date"_qs, { u"Date"_qs, db::DBFieldType::INTEGER } },
};

QString ActivityModel::TableName = u"Activities"_qs;

ActivityModel::ActivityModel(QObject *parent) : Base::PDBaseModel<ActivityModel>(false, true, parent){};
