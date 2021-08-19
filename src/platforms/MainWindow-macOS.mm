#include "MainWindow.hpp"

#ifndef Q_OS_MAC
#error "You should not build this file on non-macOS platforms"
#endif

#import <AppKit/AppKit.h>

MainWindow::MainWindow() : QWindow()
{
    setWidth(1300);
    setHeight(700);
    quickWindow = new QQuickView(this);
    quickWindow->show();
    quickWindow->setColor(Qt::transparent);

    // Create the native effects view
    NSVisualEffectView *effectsView = [[NSVisualEffectView alloc] init];
    effectsView.blendingMode = NSVisualEffectBlendingModeBehindWindow;
    effectsView.material = NSVisualEffectMaterialUnderWindowBackground;
    m_effectsWindow = QWindow::fromWinId(reinterpret_cast<WId>(effectsView));
    m_effectsWindow->setParent(this);
    m_effectsWindow->show();
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    m_effectsWindow->setGeometry(0, 0, this->width(), this->height());
    quickWindow->setGeometry(0, 0, this->width(), this->height());
    m_effectsWindow->lower();
}
