#include "PDPlugin/PluginBase/QObjectPropertyHelpers.hpp"
#include "PDPlugin/PluginInterface.hpp"

#include <QQmlEngine>
#include <QQuickItem>

class PDClock
    : public QObject
    , public PD::Plugin::PDPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PD::Plugin::PDPluginInterface)
    Q_PLUGIN_METADATA(IID PDPlugin_IID)
    Q_DISABLE_COPY_MOVE(PDClock)

  public:
    PDClock(QObject *parent = nullptr) : QObject(parent){};
    virtual ~PDClock(){};
    virtual void RegisterQMLTypes() override;
    virtual QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> QmlComponentTypes() override;
};

class PDClockItem : public QQuickItem
{
    Q_OBJECT

    PD_PROPERTY(QString, formatString, FormatString)
    PD_PROPERTY(QString, prefix, Prefix)
    PD_PROPERTY(bool, prefixSpace, PrefixSpace)
    PD_PROPERTY(QString, suffix, Suffix)
    PD_PROPERTY(bool, suffixSpace, SuffixSpace)
    PD_PROPERTY(bool, autoSize, AutoSize)
    PD_PROPERTY(int, fontSize, FontSize)

  public:
    PDClockItem(QQuickItem *parent = nullptr);
    virtual ~PDClockItem(){};
};
