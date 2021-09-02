#pragma once

#include "Base/PDBaseModel.hpp"
#include "Base/QMLPropertyHelpers.hpp"

#include <QQmlListProperty>

class PanelModel : public QObject
{
    Q_OBJECT
    PD_PROPERTY(int, row, Row)
    PD_PROPERTY(int, column, Column)
    PD_PROPERTY(int, rowSpan, RowSpan)
    PD_PROPERTY(int, columnSpan, ColumnSpan)

  public:
    explicit PanelModel(QObject *parent = nullptr) : QObject(parent){};
    PanelModel(int r, int c, int rs, int cs, QObject *parent = nullptr) : QObject(parent), m_row(r), m_column(c), m_rowSpan(rs), m_columnSpan(cs){};
    virtual ~PanelModel() = default;
};
class MainWindowModel : public PDBaseListModel
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<PanelModel> panels READ panel_list NOTIFY panelListChanged)
    PD_PROPERTY_QMLLIST(PanelModel, panel, Panel, MainWindowModel);

  public:
    MainWindowModel(QObject *parent = nullptr);
    virtual ~MainWindowModel() = default;
};

Q_DECLARE_METATYPE(MainWindowModel)
