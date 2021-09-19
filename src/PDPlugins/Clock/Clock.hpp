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
    enum ClockType
    {
        DateTime,
        Date,
        Time,
        Week,
        CountDown,
        CountUp,
    };
    Q_ENUM(ClockType)

  public:
    PDClock(QObject *parent = nullptr) : QObject(parent){};
    virtual ~PDClock(){};
    virtual void RegisterQMLTypes() override;
    virtual QMap<QString, PD::Plugin::Types::PDPluginQmlTypeInfo> QmlComponentTypes() override;
};

class PDClockItem : public QQuickItem
{
    Q_OBJECT

    PD_PROPERTY(PDClock::ClockType, clockType, ClockType)

  public:
    PDClockItem(QQuickItem *parent = nullptr);
    virtual ~PDClockItem(){};
};
