#pragma once

#include <QQuickView>
#include <QResizeEvent>

class TopWindow : public QWindow
{
    Q_OBJECT
  public:
    TopWindow();
    void resizeEvent(QResizeEvent *ev);
    QQuickView *quickWindow;

  private:
    QWindow *m_effectsWindow;
};
