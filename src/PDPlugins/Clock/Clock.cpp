#include "Clock.hpp"

#include "PDPlugin/PluginBase/QObjectPropertyMap.hpp"

using namespace PD::Plugin::Types;

void PDClock::RegisterQMLTypes()
{
    qpmRegisterType<PDClockItem>();
    qmlRegisterType<PDClockItem>(PDPLUGIN_QML_URI, 1, 0, "Clock");
    qmlRegisterModule(PDPLUGIN_QML_URI, 1, 0);
}

QMap<QString, PDPluginQmlTypeInfo> PDClock::QmlComponentTypes()
{
    const auto pFormatDateString = makeDescriptor<PDClockItem>("formatString", u"Date Format"_qs, u"yyyy-MM-dd"_qs);
    const auto pFormatTimeString = makeDescriptor<PDClockItem>("formatString", u"Time Format"_qs, u"hh:mm:ss"_qs);
    const auto pFormatDateTimeString = makeDescriptor<PDClockItem>("formatString", u"DateTime Format"_qs, u"yyyy-MM-dd hh:mm:ss"_qs);

    const auto pPrefix = makeDescriptor<PDClockItem>("prefix", u"String Prefix"_qs, u""_qs);
    const auto pSuffix = makeDescriptor<PDClockItem>("suffix", u"String Suffix"_qs, u""_qs);
    const auto pPrefixSpace = makeDescriptor<PDClockItem>("prefixSpace", u"Add a space after prefix"_qs, false);
    const auto pSuffixSpace = makeDescriptor<PDClockItem>("suffixSpace", u"Add a space before suffix"_qs, false);
    const auto pAutoSize = makeDescriptor<PDClockItem>("autoSize", u"Automatically adjust font size"_qs, true);
    const auto pFontSize = makeDescriptor<PDClockItem>("fontSize", u"Font Size"_qs, 75);
    const auto fullProperty = { pFormatDateTimeString, pPrefix, pSuffix, pPrefixSpace, pSuffixSpace, pAutoSize, pFontSize };

    const static auto icon = u"/assets/pd-frameless.svg"_qs;
    const static auto mainQmlFile = QmlInternalImportPath() + u"qml/ClockItem.qml"_qs;

    const QSize size1{ 9, 5 };
    const QSize size2{ 12, 4 };

    return {
        { u"DateClock"_qs, { u"A Calender that Shows Date"_qs, mainQmlFile, icon, { pFormatDateString }, size1 } },
        { u"TimeClock"_qs, { u"A Simple Digital Clock"_qs, mainQmlFile, icon, { pFormatTimeString }, size1 } },
        { u"DateTimeClock"_qs, { u"A DateTime Clock"_qs, mainQmlFile, icon, { pFormatDateTimeString }, size2 } },
        { u"FullClock"_qs, { u"A Clock with Prefix and Suffix String Support"_qs, mainQmlFile, icon, fullProperty, size2 } },
    };
}

PDClockItem::PDClockItem(QQuickItem *parent) : QQuickItem(parent), m_prefixSpace(false), m_suffixSpace(false), m_autoSize(true), m_fontSize(75)
{
}
