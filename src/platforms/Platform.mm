#include "Platform.hpp"

#import <AppKit/AppKit.h>
#include <QWindow>

using namespace PD::Platform;

QWindow *PDPlatformAPI::getEffectBackgroundWindow()
{
    NSVisualEffectView *effectsView = [[NSVisualEffectView alloc] init];
    effectsView.blendingMode = NSVisualEffectBlendingModeBehindWindow;
    effectsView.material = NSVisualEffectMaterialUnderWindowBackground;
    return QWindow::fromWinId(reinterpret_cast<WId>(effectsView));
}
