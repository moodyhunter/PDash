#pragma once

#include <QQuickWindow>

class QResizeEvent;
class QQuickView;

class PDMainWindow : public QQuickWindow
{
    Q_OBJECT
  public:
    PDMainWindow();
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
    QWindow *m_effectsBackgroundWindow;
};
