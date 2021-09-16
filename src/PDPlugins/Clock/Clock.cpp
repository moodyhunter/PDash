#include "Clock.hpp"

void PDClock::RegisterQMLTypes()
{
    qmlRegisterSingletonInstance<PDClockProp>(PDPLUGIN_QML_URI, 1, 0, "ClockProp", new PDClockProp(this));
    qmlRegisterModule(PDPLUGIN_QML_URI, 1, 0);
}

QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> PDClock::QmlComponentTypes()
{
    return {
        { u"PDClock 1"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
        { u"PDClock 2"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
        { u"PDClock 3"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
        { u"PDClock 4"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
        { u"PDClock 5"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
        { u"PDClock 6"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs } },
    };
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

PDClockProp::PDClockProp(QObject *parent) : QObject(parent)
{
    setVal(100);
}
