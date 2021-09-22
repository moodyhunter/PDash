#include "Clock.hpp"

#include "PDPlugin/PluginBase/QObjectPropertyMap.hpp"

void PDClock::RegisterQMLTypes()
{
    qpmRegisterType<PDClockItem>();
    qRegisterMetaType<ClockType>();
    qmlRegisterType<ClockType>(PDPLUGIN_QML_URI, 1, 0, "ClockType");
    qmlRegisterType<PDClockItem>(PDPLUGIN_QML_URI, 1, 0, "Clock");
    qmlRegisterModule(PDPLUGIN_QML_URI, 1, 0);
}

QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> PDClock::QmlComponentTypes()
{
    static const PD::Plugin::Types::PDPropertyMap empty{ { u"clockType"_qs, { u"Type of the clock"_qs, ClockType::DateTime } } };
    return {
        { u"Clock 1"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
        { u"Clock 2"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
        { u"Clock 3"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
        { u"Clock 4"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
        { u"Clock 5"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
        { u"Clock 6"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, empty } },
    };
}

PDClockItem::PDClockItem(QQuickItem *parent) : QQuickItem(parent), m_clockType(PDClock::ClockType::DateTime)
{
}
