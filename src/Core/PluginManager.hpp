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
        PD::Plugin::PDPluginInterface *pinterface = nullptr;
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
        bool loadPluginInstanceObject(const QString &fullPath, QObject *instance, QPluginLoader *loader);

      private:
        QHash<PDPluginId, PluginInfo> m_plugins;
    };
} // namespace PD::Core
