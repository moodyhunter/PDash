#pragma once

#include "PDPlugin/PluginInterface.hpp"

class QPluginLoader;

namespace PD::Core
{
    struct PluginInfo
    {
        QString libraryPath;
        QPluginLoader *loader;
        PDPluginId id;
        PDPluginInterface *pinterface = nullptr;
    };

    class PDPluginManager : public QObject
    {
        Q_OBJECT
      public:
        PDPluginManager(QObject *parent = nullptr);
        virtual ~PDPluginManager();

        void LoadPlugins();

        const QList<const PluginInfo *> AllPlugins() const;
        const PluginInfo *GetPlugin(const PDPluginId &pid);

      signals:
        void OnQmlImportPathAdded(const QString &path);

      private:
        bool tryLoadPlugin(const QString &pluginFullPath);
        bool loadPluginInstanceObject(const QString &fullPath, QObject *instance, QPluginLoader *loader);

      private:
        QHash<PDPluginId, PluginInfo> plugins;
    };
} // namespace PD::Core