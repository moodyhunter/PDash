#pragma once

#include "PluginInterface.hpp"

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class PluginManager : public QObject
{
    Q_OBJECT
  public:
    explicit PluginManager(QObject *parent = nullptr);
    void loadPlugins();

  signals:
};
