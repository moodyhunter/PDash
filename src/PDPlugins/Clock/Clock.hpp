#include "PDPlugin/PluginInterface.hpp"

#include <QQmlEngine>

class PDClock
    : public QObject
    , public PDPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PDPluginInterface)
    Q_PLUGIN_METADATA(IID PDPlugin_IID)
    Q_DISABLE_COPY_MOVE(PDClock)

  public:
    PDClock(QObject *parent = nullptr);
    virtual ~PDClock();
    virtual void RegisterQMLTypes() override;
};

class PDClockProp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int val READ getVal WRITE setVal NOTIFY valChanged)

  public:
    PDClockProp();
    virtual ~PDClockProp();

    int getVal() const;
    void setVal(int newVal);
  signals:
    void valChanged();

  private:
    int val;
};
