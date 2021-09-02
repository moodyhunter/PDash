#include "ThemesModel.hpp"

AppThemeModel::AppThemeModel(QObject *parent) : PDBaseListModel(parent)
{
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
    setHandlerHover(m_dark.lighter(150));
    setBackgroudOpacity(0.3);
}
