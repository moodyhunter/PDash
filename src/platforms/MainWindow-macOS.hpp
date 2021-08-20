#pragma once

#include <QQuickView>
#include <QWindow>

#ifndef Q_OS_MAC
#error "You should not build this file on non-macOS platforms"
#endif

class QResizeEvent;

class MainWindow : public QWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
};
