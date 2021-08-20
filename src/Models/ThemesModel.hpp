#pragma once

#include "Base/PDBaseModel.hpp"
#include "Base/QMLPropertyHelpers.hpp"

#include <QColor>

class AppThemeModel : public PDBaseModel
{
    Q_OBJECT
  public:
    explicit AppThemeModel(QObject *parent = nullptr);
    virtual void LoadData() override;

    PD_PROPERTY(QColor, background, Background)
    PD_PROPERTY(QColor, dark, Dark)
    PD_PROPERTY(QColor, highlight, Highlight)
    PD_PROPERTY(QColor, highlightText, HighlightText)
    PD_PROPERTY(QColor, text, Text)
    PD_PROPERTY(QColor, warn, Warn)
    PD_PROPERTY(QColor, shadow, Shadow)
    PD_PROPERTY(QColor, border, Border)
    PD_PROPERTY(QColor, deep, Deep)
    PD_PROPERTY(QColor, deepText, DeepText)
    PD_PROPERTY(double, backgroundOpacity, BackgroudOpacity)
    PD_PROPERTY(double, handlerHover, HandlerHover)
};
