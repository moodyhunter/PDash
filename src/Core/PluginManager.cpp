#include "PluginManager.hpp"

#include "PDApplication.hpp"

#include <QDir>
#include <QPluginLoader>

using namespace PD::Core;

PDPluginManager::PDPluginManager(QObject *parent) : QObject(parent)
{
}

PDPluginManager::~PDPluginManager()
{
    for (auto &&plugin : m_plugins)
    {
        qDebug() << "Unloading plugin:" << plugin.libraryPath;

        // Static plugins doesn't have a loader.
        if (plugin.loader)
        {
            plugin.loader->unload();
            plugin.loader->deleteLater();
        }
    }
    m_plugins.clear();
}

void PDPluginManager::LoadPlugins()
{
    qInfo() << "Reloading plugin list";

    for (const auto &plugin : QPluginLoader::staticInstances())
    {
        loadPluginInstanceObject(u"[STATIC]"_qs, plugin, nullptr);
    }

#ifndef QT_STATIC
    for (const auto &pluginDirPath : PDApplication::GetAssetsPath(u"plugins"_qs))
    {
        const auto entries = QDir(pluginDirPath).entryList(QDir::Files);
        if (entries.isEmpty())
            continue;

        if (QDir libsDir(pluginDirPath + u"/libs"); libsDir.exists())
            qputenv("PATH", QDir::toNativeSeparators(qEnvironmentVariable("PATH") + QDir::listSeparator() + libsDir.absolutePath()).toUtf8());

        for (const auto &fileName : entries)
        {
            const auto pluginFullPath = QDir(pluginDirPath).absoluteFilePath(fileName);

            if (!pluginFullPath.endsWith(u".dll"_qs) && !pluginFullPath.endsWith(u".so"_qs) && !pluginFullPath.endsWith(u".dylib"_qs))
                continue;

            if (pluginFullPath.isEmpty())
                continue;

            auto loader = new QPluginLoader(pluginFullPath, this);

            QObject *instance = loader->instance();
            if (!instance)
            {
                const auto errMessage = loader->errorString();
                qWarning() << errMessage << "plugin:" << pluginFullPath;
                continue;
            }

            loadPluginInstanceObject(pluginFullPath, instance, loader);
        }
    }
#else
    qInfo() << "PD is statically linked against Qt, not loading dynamic plugins.";
#endif

    for (auto it = m_plugins.constKeyValueBegin(); it != m_plugins.constKeyValueEnd(); it++)
    {
        const auto &[pid, pinfo] = *it;
        Q_UNUSED(pid)
        pinfo.pinterface->RegisterQMLTypes();
        for (const auto &str : pinfo.pinterface->QmlImportPaths())
            emit OnQmlImportPathAdded(str);
    }
}

const QList<const PluginInfo *> PDPluginManager::AllPlugins() const
{
    QList<const PluginInfo *> list;
    list.reserve(m_plugins.size());
    for (const auto &plugin : m_plugins)
        list << &plugin;
    return list;
}

const PluginInfo *PDPluginManager::GetPlugin(const PDPluginId &pid)
{
    return !m_plugins.isEmpty() && m_plugins.contains(pid) ? &m_plugins[pid] : nullptr;
}

bool PDPluginManager::loadPluginInstanceObject(const QString &fullPath, QObject *instance, QPluginLoader *loader)
{
    PluginInfo info;
    info.libraryPath = fullPath;
    info.loader = loader;
    info.pinterface = qobject_cast<PD::Plugin::PDPluginInterface *>(instance);

    if (!info.pinterface)
    {
        qWarning() << "Cannot to cast from QObject to PDPluginInterface";
        // Static plugins doesn't have a loader.
        if (info.loader)
        {
            info.loader->unload();
            info.loader->deleteLater();
        }
        return false;
    }

    if (m_plugins.contains(info.id))
    {
        qWarning() << "Found another plugin with the same internal name:" << info.id << ". Skipped";
        return false;
    }

    qInfo() << "Loaded plugin:" << info.libraryPath;
    m_plugins.insert(info.id, info);
    return true;
}
