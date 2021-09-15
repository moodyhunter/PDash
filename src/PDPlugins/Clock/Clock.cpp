#include "Clock.hpp"

#include <QQmlComponent>

PDClock::PDClock(QObject *parent) : QObject(parent)
{
}

PDClock::~PDClock()
{
}

void PDClock::RegisterQMLTypes()
{
    qmlRegisterSingletonInstance<PDClockProp>(PDPLUGIN_QML_URI, 1, 0, "ClockProp", new PDClockProp);
    qmlRegisterModule(PDPLUGIN_QML_URI, 1, 0);
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
}

PDClockProp::~PDClockProp()
{
}
