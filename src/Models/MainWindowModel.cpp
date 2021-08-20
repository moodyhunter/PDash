#include "MainWindowModel.hpp"

int PanelModel::getColumn() const
{
    return column;
}

void PanelModel::setColumn(int newColumn)
{
    if (column == newColumn)
        return;
    column = newColumn;
    emit columnChanged();
}

int PanelModel::getRowSpan() const
{
    return rowSpan;
}

void PanelModel::setRowSpan(int newRowSpan)
{
    if (rowSpan == newRowSpan)
        return;
    rowSpan = newRowSpan;
    emit rowSpanChanged();
}

int PanelModel::getColumnSpan() const
{
    return columnSpan;
}

void PanelModel::setColumnSpan(int newColumnSpan)
{
    if (columnSpan == newColumnSpan)
        return;
    columnSpan = newColumnSpan;
    emit columnSpanChanged();
}

int PanelModel::getRow() const
{
    return row;
}

void PanelModel::setRow(int newRow)
{
    if (row == newRow)
        return;
    row = newRow;
    emit rowChanged();
}

MainWindowModel::MainWindowModel(QObject *parent) : PDBaseModel(parent)
{
    m_panelModels.append(new PanelModel{ 1, 1, 5, 6 });
    m_panelModels.append(new PanelModel{ 6, 13, 10, 6 });
    m_panelModels.append(new PanelModel{ 6, 1, 10, 12 });
    m_panelModels.append(new PanelModel{ 1, 13, 5, 6 });
    m_panelModels.append(new PanelModel{ 1, 7, 5, 6 });
}

MainWindowModel::~MainWindowModel()
{
}

void MainWindowModel::LoadData()
{
}
