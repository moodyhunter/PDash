#include "MainWindow-macOS.hpp"

#ifndef Q_OS_MAC
#error "You should not build this file on non-macOS platforms"
#endif

#import <AppKit/AppKit.h>

namespace
{
    constexpr auto WINDOW_WIDTH = 1300;
    constexpr auto WINDOW_HEIGHT = 700;
} // namespace

MainWindow::MainWindow() : QWindow()
{
    QQuickWindow::setDefaultAlphaBuffer(true);

    setWidth(WINDOW_WIDTH);
    setHeight(WINDOW_HEIGHT);
    quickWindow = new QQuickView(this);
    quickWindow->setSource({ u"qrc:/qml/MainComponent.qml"_qs });
    quickWindow->setColor(Qt::transparent);
    quickWindow->show();

    // Create the native effects view
    NSVisualEffectView *effectsView = [[NSVisualEffectView alloc] init];
    effectsView.blendingMode = NSVisualEffectBlendingModeBehindWindow;
    effectsView.material = NSVisualEffectMaterialUnderWindowBackground;
    m_effectsWindow = QWindow::fromWinId(reinterpret_cast<WId>(effectsView));
    m_effectsWindow->setParent(this);
    m_effectsWindow->show();
    m_effectsWindow->lower();
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    m_effectsWindow->setGeometry(0, 0, this->width(), this->height());
    quickWindow->setGeometry(0, 0, this->width(), this->height());
}
