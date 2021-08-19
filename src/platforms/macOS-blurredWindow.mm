#include "macOS-blurredWindow.hpp"

#import <AppKit/AppKit.h>

TopWindow::TopWindow() : QWindow()
{
    quickWindow = new QQuickView(this);
    quickWindow->setGeometry(0, 0, this->width(), this->height());
    quickWindow->show();

    quickWindow->setColor(Qt::transparent);

    // Create the native effects view
    NSVisualEffectView *effectsView = [[NSVisualEffectView alloc] init];
    effectsView.blendingMode = NSVisualEffectBlendingModeBehindWindow;
    effectsView.material = NSVisualEffectMaterialUnderWindowBackground;

    // Wrap effects view in a QWindow which will be used to control it
    m_effectsWindow = QWindow::fromWinId(reinterpret_cast<WId>(effectsView));

    // Add the effects window as a child QWindow.
    m_effectsWindow->setParent(this);
    m_effectsWindow->show();
}

void TopWindow::resizeEvent(QResizeEvent *ev)
{
    m_effectsWindow->setGeometry(0, 0, this->width(), this->height());
    m_effectsWindow->lower();
}
