#include "PDPlugin/PluginInterface.hpp"

#include <QQmlEngine>

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

class PDClockProp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int val READ getVal WRITE setVal NOTIFY valChanged)

  public:
    PDClockProp(QObject *parent = nullptr);
    virtual ~PDClockProp(){};

    int getVal() const;
    void setVal(int newVal);
  signals:
    void valChanged();

  private:
    int val;
};
