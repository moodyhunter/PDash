#pragma once

#include <QtPlugin>

#define PDPlugin_IID "plugin.pd.mooody.me"

class PDPluginInterface
{
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(PDPluginInterface, PDPlugin_IID)
QT_END_NAMESPACE
