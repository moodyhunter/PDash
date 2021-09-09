#include "PluginManager.hpp"

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QStandardPaths>

#ifdef QT_DEBUG
const static auto DEBUG_SUFFIX = u"debug";
#else
const static auto DEBUG_SUFFIX = u"";
#endif

using namespace PD::Core;

QStringList GetAssetsPath(const QString &dirName)
{
    static constexpr auto makeAbs = [](const QString &p) { return QDir(p).absolutePath(); };

    QStringList list;
    // Default behavior on Windows
    list << makeAbs(QCoreApplication::applicationDirPath() + u"/" + dirName);

    list << u":/" + dirName;

    list << QStandardPaths::locateAll(QStandardPaths::AppDataLocation, dirName, QStandardPaths::LocateDirectory);
    list << QStandardPaths::locateAll(QStandardPaths::AppConfigLocation, dirName, QStandardPaths::LocateDirectory);

    if (qEnvironmentVariableIsSet("XDG_DATA_DIRS"))
        list << makeAbs(qEnvironmentVariable("XDG_DATA_DIRS") + u"/" + dirName);

#ifdef Q_OS_UNIX
    if (qEnvironmentVariableIsSet("APPIMAGE"))
        list << makeAbs(QCoreApplication::applicationDirPath() + u"/../share/PersonalDashboard" + DEBUG_SUFFIX + dirName);

    if (qEnvironmentVariableIsSet("SNAP"))
        list << makeAbs(qEnvironmentVariable("SNAP") + u"/usr/share/PersonalDashboard" + DEBUG_SUFFIX + dirName);

    list << makeAbs(u"/usr/local/share/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
    list << makeAbs(u"/usr/local/lib64/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
    list << makeAbs(u"/usr/local/lib/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);

    list << makeAbs(u"/usr/share/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
    list << makeAbs(u"/usr/lib64/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
    list << makeAbs(u"/usr/lib/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);

    list << makeAbs(u"/lib64/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
    list << makeAbs(u"/lib/PersonalDashboard"_qs + DEBUG_SUFFIX + dirName);
#endif

#ifdef Q_OS_MAC
    // macOS platform directories.
    list << QDir(QCoreApplication::applicationDirPath() + u"/../Resources/" + dirName).absolutePath();
#endif
    list.removeDuplicates();
    return list;
}

PDPluginManager::PDPluginManager(QObject *parent) : QObject(parent)
{
}

PDPluginManager::~PDPluginManager()
{
    for (auto &&plugin : plugins)
    {
        qDebug() << "Unloading plugin:" << plugin.libraryPath;

        // Static plugins doesn't have a loader.
        if (plugin.loader)
        {
            plugin.loader->unload();
            plugin.loader->deleteLater();
        }
    }
    plugins.clear();
}

void PDPluginManager::LoadPlugins()
{
    qInfo() << "Reloading plugin list";

    for (const auto &plugin : QPluginLoader::staticInstances())
    {
        loadPluginImpl(u"[STATIC]"_qs, plugin, nullptr);
    }
#ifndef QT_STATIC
    for (const auto &pluginDirPath : GetAssetsPath(u"plugins"_qs))
    {
        const auto entries = QDir(pluginDirPath).entryList(QDir::Files);
        if (entries.isEmpty())
            continue;

#ifdef Q_OS_WINDOWS
        // qgetenv is lossy on Windows
        qputenv("PATH", QDir::toNativeSeparators(qEnvironmentVariable("PATH") + QDir::listSeparator() + pluginDirPath + "/libs").toUtf8());
#else
        // qEnvironmentVariable is lossy
        qputenv("PATH", QDir::toNativeSeparators(QString::fromUtf8(qgetenv("PATH")) + QDir::listSeparator() + pluginDirPath + u"/libs"_qs).toUtf8());
#endif

        for (const auto &fileName : entries)
        {
            tryLoadPlugin(QDir(pluginDirPath).absoluteFilePath(fileName));
        }
    }
#else
    qInfo() << "PD is statically linked against Qt, skipping loading dynamic plugins.";
#endif

    for (auto it = plugins.constKeyValueBegin(); it != plugins.constKeyValueEnd(); it++)
    {
        // auto wd = PersonalDashboardLibrary::StorageProvider()->GetPluginWorkingDirectory(it->first);
        // auto conf = PersonalDashboardLibrary::StorageProvider()->GetPluginSettings(it->first);
        // it->second.pinterface->m_Settings = conf;
        // it->second.pinterface->m_WorkingDirectory.setPath(wd.absolutePath());
        // it->second.pinterface->m_ProfileManager = PersonalDashboardLibrary::ProfileManager();
        // it->second.pinterface->m_NetworkRequestHelper = &helperstub;
        // it->second.pinterface->InitializePlugin();
        // it->second.pinterface->SettingsUpdated();
    }
}

const QList<const PluginInfo *> PDPluginManager::AllPlugins() const
{
    QList<const PluginInfo *> list;
    list.reserve(plugins.size());
    for (const auto &plugin : plugins)
        list << &plugin;
    return list;
}

const PluginInfo *PDPluginManager::GetPlugin(const PDPluginId &pid)
{
    return !plugins.isEmpty() && plugins.contains(pid) ? &plugins[pid] : nullptr;
}

bool PDPluginManager::tryLoadPlugin(const QString &pluginFullPath)
{
    if (!pluginFullPath.endsWith(u".dll"_qs) && !pluginFullPath.endsWith(u".so"_qs) && !pluginFullPath.endsWith(u".dylib"_qs))
        return false;

    if (pluginFullPath.isEmpty())
        return false;

    auto loader = new QPluginLoader(pluginFullPath, this);

    QObject *instance = loader->instance();
    if (!instance)
    {
        const auto errMessage = loader->errorString();
        qInfo() << errMessage << "plugin:" << pluginFullPath;
        return false;
    }

    return loadPluginImpl(pluginFullPath, instance, loader);
}

bool PDPluginManager::loadPluginImpl(const QString &fullPath, QObject *instance, QPluginLoader *loader)
{
    PluginInfo info;
    info.libraryPath = fullPath;
    info.loader = loader;
    info.pinterface = qobject_cast<PDPluginInterface *>(instance);

    if (!info.pinterface)
    {
        qInfo() << "Failed to cast from QObject to PluginInterface";
        // Static plugins doesn't have a loader.
        if (info.loader)
        {
            info.loader->unload();
            info.loader->deleteLater();
        }
        return false;
    }

    if (plugins.contains(info.id))
    {
        qInfo() << "Found another plugin with the same internal name:" << info.id << ". Skipped";
        return false;
    }

    qInfo() << "Loaded plugin:" << info.libraryPath;
    plugins.insert(info.id, info);
    return true;
}
