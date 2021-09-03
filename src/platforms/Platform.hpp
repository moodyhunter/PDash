#pragma once

class QWindow;

namespace PD::Platform
{
    struct PDPlatformAPI
    {
        static QWindow *getEffectBackgroundWindow();
    };
} // namespace PD::Platform
