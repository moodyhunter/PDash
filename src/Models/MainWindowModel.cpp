#include "MainWindowModel.hpp"

MainWindowModel::MainWindowModel(QObject *parent) : PDBaseListModel(parent)
{
    m_panel_list.append(new PanelModel{ 1, 1, 5, 6 });
    m_panel_list.append(new PanelModel{ 6, 13, 10, 6 });
    m_panel_list.append(new PanelModel{ 6, 1, 10, 12 });
    m_panel_list.append(new PanelModel{ 1, 13, 5, 6 });
    m_panel_list.append(new PanelModel{ 1, 7, 5, 6 });
}
