#pragma once

#include <QQuickView>

class QResizeEvent;

class PDMainWindow : public QQuickView
{
    Q_OBJECT
  public:
    PDMainWindow();
#ifdef Q_OS_MACOS
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
    QWindow *m_effectsBackgroundWindow;
#endif
};
