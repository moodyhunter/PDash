#include "PDBaseModel.hpp"

#include "DB/DBManager.hpp"
#include "PDApplication.hpp"

PDBaseListModel::PDBaseListModel(QObject *parent) : QObject(parent)
{
    //    connect(pdApp->DatabaseManager(), &PD::Database::PDDatabaseManager::OnDatabaseOpened, this, &PDBaseListModel::p_OnDatabaseOpened);
}

PDBaseListModel::~PDBaseListModel()
{
}

void PDBaseListModel::p_OnDatabaseOpened()
{
}
