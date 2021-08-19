#pragma once

#include <QQuickView>
#include <QResizeEvent>

class MainWindow : public QWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void resizeEvent(QResizeEvent *ev);
    QQuickView *quickWindow;

  private:
    QWindow *m_effectsWindow;
};
