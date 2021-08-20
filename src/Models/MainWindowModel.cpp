#include "MainWindowModel.hpp"

MainWindowModel::MainWindowModel(QObject *parent) : PDBaseModel(parent)
{
    m_panel_list.append(new PanelModel{ 1, 1, 5, 6 });
    m_panel_list.append(new PanelModel{ 6, 13, 10, 6 });
    m_panel_list.append(new PanelModel{ 6, 1, 10, 12 });
    m_panel_list.append(new PanelModel{ 1, 13, 5, 6 });
    m_panel_list.append(new PanelModel{ 1, 7, 5, 6 });

    m_activity_list.append(new ActivityModel{ "type0", "title0", "text0", "id0", "date0" });
    m_activity_list.append(new ActivityModel{ "type2", "title1", "text1", "id1", "date1" });
    m_activity_list.append(new ActivityModel{ "type2", "title2", "text2", "id2", "date2" });
    m_activity_list.append(new ActivityModel{ "type3", "title3", "text3", "id3", "date3" });
    m_activity_list.append(new ActivityModel{ "type4", "title4", "text4", "id4", "date4" });
}

MainWindowModel::~MainWindowModel()
{
}

void MainWindowModel::LoadData()
{
}
