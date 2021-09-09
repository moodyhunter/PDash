#pragma once

#include "Core/PDBaseModel.hpp"
#include "Core/QMLPropertyHelpers.hpp"

#include <QColor>

class AppThemeModel : public PDBaseListModel
{
    Q_OBJECT
  public:
    explicit AppThemeModel(QObject *parent = nullptr);

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
    PD_PROPERTY(QColor, handlerHover, HandlerHover)
    PD_PROPERTY(double, backgroundOpacity, BackgroudOpacity)
};
