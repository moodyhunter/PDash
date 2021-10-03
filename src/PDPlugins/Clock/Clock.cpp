#include "Clock.hpp"

#include "PDPlugin/PluginBase/QObjectPropertyMap.hpp"

void PDClock::RegisterQMLTypes()
{
    qpmRegisterType<PDClockItem>();
    qmlRegisterType<PDClockItem>(PDPLUGIN_QML_URI, 1, 0, "Clock");
    qmlRegisterModule(PDPLUGIN_QML_URI, 1, 0);
}

QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> PDClock::QmlComponentTypes()
{
    static const PD::Plugin::Types::PDPropertyDescriptor empty{ u"formatString"_qs, u"Datetime Format"_qs, "dd" };
    return {
        { u"Clock 1"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
        { u"Clock 2"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
        { u"Clock 3"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
        { u"Clock 4"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
        { u"Clock 5"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
        { u"Clock 6"_qs, { u"Shows a Clock"_qs, QmlInternalImportPath() + u"qml/ClockItem.qml"_qs, u"/assets/pd-frameless.svg"_qs, { empty } } },
    };
}

PDClockItem::PDClockItem(QQuickItem *parent) : QQuickItem(parent)
{
}
