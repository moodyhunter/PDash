#include "back.hpp"

#include <QQmlComponent>

PDClock::PDClock(QObject *parent) : QObject(parent)
{
    qDebug() << "Plugin constructed";
    qmlRegisterSingletonInstance<PDClockProp>("PDPlugins.Clock", 1, 0, "ClockProp", new PDClockProp);
    qmlRegisterModule("PDPlugins.Clock", 1, 0);
}

PDClock::~PDClock()
{
    qDebug() << "Plugin destructed";
}

PDPluginId PDClock::PluginId() const
{
    return PDPluginId{ u"clock"_qs };
}

QString PDClock::QmlImportPath() const
{
    return u"/PDPlugins/Clock"_qs;
}

// =====================================================================
int PDClockProp::getVal() const
{
    return val;
}

void PDClockProp::setVal(int newVal)
{
    if (val == newVal)
        return;
    val = newVal;
    emit valChanged();
}

PDClockProp::PDClockProp()
{
    setVal(100);
    qDebug() << "prop constructed";
}

PDClockProp::~PDClockProp()
{
}
