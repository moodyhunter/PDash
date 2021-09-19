#include "PDBaseModel.hpp"

#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

PDBaseObjectPropertyModel::PDBaseObjectPropertyModel(QObject *parent) : QObject(parent)
{
    //    connect(pdApp->DatabaseManager(), &PD::Database::PDDatabaseManager::OnDatabaseOpened, this, &PDBaseListModel::p_OnDatabaseOpened);
}

PDBaseObjectPropertyModel::~PDBaseObjectPropertyModel()
{
}

void PDBaseObjectPropertyModel::p_OnDatabaseOpened()
{
}
