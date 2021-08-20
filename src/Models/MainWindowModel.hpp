#pragma once

#include "Base/PDBaseModel.hpp"
#include "Base/QMLListPropertyHelper.hpp"

#include <QQmlListProperty>

class PanelModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int row READ getRow WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(int column READ getColumn WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(int rowSpan READ getRowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
    Q_PROPERTY(int columnSpan READ getColumnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)

  public:
    explicit PanelModel(QObject *parent = nullptr) : QObject(parent){};
    PanelModel(int r, int c, int rs, int cs, QObject *parent = nullptr) : QObject(parent)
    {
        setRow(r), setColumn(c), setRowSpan(rs), setColumnSpan(cs);
    }
    virtual ~PanelModel()
    {
    }

    int getRow() const;
    int getColumn() const;
    int getRowSpan() const;
    int getColumnSpan() const;

    void setRow(int newRow);
    void setColumn(int newColumn);
    void setRowSpan(int newRowSpan);
    void setColumnSpan(int newColumnSpan);

  signals:
    void rowChanged();
    void columnChanged();
    void rowSpanChanged();
    void columnSpanChanged();

  private:
    int row;
    int column;
    int rowSpan;
    int columnSpan;
};

class MainWindowModel : public PDBaseModel
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<PanelModel> panels READ panels)

  public:
    MainWindowModel(QObject *parent = nullptr);
    virtual ~MainWindowModel();
    virtual void LoadData() override;
    QMLListFunctions(panel, Panel, MainWindowModel, PanelModel, m_panelModels);

  private:
    QList<PanelModel *> m_panelModels;
};

Q_DECLARE_METATYPE(MainWindowModel)
