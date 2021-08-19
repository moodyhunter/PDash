#pragma once

#include <QCoreApplication>
#include <QQuickView>
#include <QWindow>

class QQuickView;
class QResizeEvent;

namespace
{
    constexpr auto WINDOW_WIDTH = 1300;
    constexpr auto WINDOW_HEIGHT = 700;
} // namespace

#ifdef Q_OS_MAC
class MainWindow : public QWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void resizeEvent(QResizeEvent *ev);

  private:
    QQuickView *quickWindow;
};
#else
class MainWindow
{
  public:
    MainWindow()
    {
        view = new QQuickView();
    }
    ~MainWindow()
    {
        delete view;
    }
    void show()
    {
        view->setColor(QColor("#3B4252"));
        view->setSource({ "qrc:/qml/main.qml" });
        view->setWidth(WINDOW_WIDTH);
        view->setHeight(WINDOW_HEIGHT);
        view->show();
    }

  private:
    QQuickView *view;
};
#endif
