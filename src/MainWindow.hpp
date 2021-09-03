#pragma once

#include <QQuickView>
#include <QWindow>

class QResizeEvent;

class MainWindow : public QQuickWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
    QWindow *m_effectsBackgroundWindow;
};
