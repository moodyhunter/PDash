#include "ThemesModel.hpp"

AppThemeModel::AppThemeModel(QObject *parent) : PDBaseModel(parent)
{
#pragma message("TODO: Use LoadData")
    setBackground("#3B4252");
    setDark("#2E3440");
    setHighlight("#5E81AC");
    setHighlightText("#ECEFF4");
    setText("#ECEFF4");
    setWarn("#BF616A");
    setShadow("#29000000");
    setBorder("#3381A1C1");
    setDeep("#3B4252");
    setDeepText("#ECEFF4");
}

const QColor &AppThemeModel::getBackground() const
{
    return background;
}

void AppThemeModel::setBackground(const QColor &newBackground)
{
    if (background == newBackground)
        return;
    background = newBackground;
    emit backgroundChanged();
}

const QColor &AppThemeModel::getDark() const
{
    return dark;
}

void AppThemeModel::setDark(const QColor &newDark)
{
    if (dark == newDark)
        return;
    dark = newDark;
    emit darkChanged();
}

const QColor &AppThemeModel::getHighlight() const
{
    return highlight;
}

void AppThemeModel::setHighlight(const QColor &newHighlight)
{
    if (highlight == newHighlight)
        return;
    highlight = newHighlight;
    emit highlightChanged();
}

const QColor &AppThemeModel::getHighlightText() const
{
    return highlightText;
}

void AppThemeModel::setHighlightText(const QColor &newHighlightText)
{
    if (highlightText == newHighlightText)
        return;
    highlightText = newHighlightText;
    emit highlightTextChanged();
}

const QColor &AppThemeModel::getText() const
{
    return text;
}

void AppThemeModel::setText(const QColor &newText)
{
    if (text == newText)
        return;
    text = newText;
    emit textChanged();
}

const QColor &AppThemeModel::getWarn() const
{
    return warn;
}

void AppThemeModel::setWarn(const QColor &newWarn)
{
    if (warn == newWarn)
        return;
    warn = newWarn;
    emit warnChanged();
}

const QColor &AppThemeModel::getShadow() const
{
    return shadow;
}

void AppThemeModel::setShadow(const QColor &newShadow)
{
    if (shadow == newShadow)
        return;
    shadow = newShadow;
    emit shadowChanged();
}

const QColor &AppThemeModel::getBorder() const
{
    return border;
}

void AppThemeModel::setBorder(const QColor &newBorder)
{
    if (border == newBorder)
        return;
    border = newBorder;
    emit borderChanged();
}

const QColor &AppThemeModel::getDeep() const
{
    return deep;
}

void AppThemeModel::setDeep(const QColor &newDeep)
{
    if (deep == newDeep)
        return;
    deep = newDeep;
    emit deepChanged();
}

const QColor &AppThemeModel::getDeepText() const
{
    return deepText;
}

void AppThemeModel::setDeepText(const QColor &newDeepText)
{
    if (deepText == newDeepText)
        return;
    deepText = newDeepText;
    emit deepTextChanged();
}

void AppThemeModel::LoadData()
{
}
