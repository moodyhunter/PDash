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
    virtual ~PanelModel(){};
};

class ActivityModel : public QObject
{
    Q_OBJECT
    PD_PROPERTY(QString, type, Type)
    PD_PROPERTY(QString, title, Title)
    PD_PROPERTY(QString, text, Text)
    PD_PROPERTY(QString, id, Id)
    PD_PROPERTY(QString, date, Date)

  public:
    explicit ActivityModel(QObject *parent = nullptr) : QObject(parent){};
    ActivityModel(const QString &type, const QString &title, const QString &text, const QString &id, const QString &date, QObject *parent = nullptr)
        : QObject(parent), m_type(type), m_title(title), m_text(text), m_id(id), m_date(date){};
    virtual ~ActivityModel(){};
};

class MainWindowModel : public PDBaseModel
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<PanelModel> panels READ panel_list NOTIFY panelListChanged)
    PD_LIST_PROPERTY(PanelModel, panel, Panel, MainWindowModel);

    Q_PROPERTY(QQmlListProperty<ActivityModel> activities READ activity_list NOTIFY activityListChanged)
    PD_LIST_PROPERTY(ActivityModel, activity, Activity, MainWindowModel);

  public:
    MainWindowModel(QObject *parent = nullptr);
    virtual ~MainWindowModel();

    virtual void LoadData() override;
};

Q_DECLARE_METATYPE(MainWindowModel)
