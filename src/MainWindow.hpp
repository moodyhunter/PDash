#pragma once

#include <QWindow>

class QResizeEvent;
class QQuickView;

class MainWindow : public QWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
    QWindow *m_effectsBackgroundWindow;
};
