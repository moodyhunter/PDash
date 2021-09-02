#include "MainWindowModel.hpp"

MainWindowModel::MainWindowModel(QObject *parent) : PDBaseListModel(parent)
{
    m_panel_list.append(new PanelModel{ 1, 1, 5, 6 });
    m_panel_list.append(new PanelModel{ 6, 13, 10, 6 });
    m_panel_list.append(new PanelModel{ 6, 1, 10, 12 });
    m_panel_list.append(new PanelModel{ 1, 13, 5, 6 });
    m_panel_list.append(new PanelModel{ 1, 7, 5, 6 });

    m_activity_list.append(new ActivityModel{ u"type0"_qs, u"title0"_qs, u"text0"_qs, u"id0"_qs, u"date0"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title1"_qs, u"text1"_qs, u"id1"_qs, u"date1"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type2"_qs, u"title2"_qs, u"text2"_qs, u"id2"_qs, u"date2"_qs });
    m_activity_list.append(new ActivityModel{ u"type3"_qs, u"title3"_qs, u"text3"_qs, u"id3"_qs, u"date3"_qs });
    m_activity_list.append(new ActivityModel{ u"type4"_qs, u"title4"_qs, u"text4"_qs, u"id4"_qs, u"date4"_qs });
}
