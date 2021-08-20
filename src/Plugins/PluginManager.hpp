#pragma once

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class PluginManager : public QObject
{
    Q_OBJECT
  public:
    explicit PluginManager(QObject *parent = nullptr);

  signals:
};
