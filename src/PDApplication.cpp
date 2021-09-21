#include "PDApplication.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/PanelModel.hpp"
#include "Models/ThemesModel.hpp"

#include <QDir>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include <QTranslator>

#define PD_QML_URI "pd.mooody.me"

#ifdef QT_DEBUG
const static auto DEBUG_SUFFIX = u"debug";
#else
const static auto DEBUG_SUFFIX = u"";
#endif

using namespace PD;

PDApplication::PDApplication(int &argc, char *argv[])
    : SingleApplication(argc, argv),                      //
      m_dbManager(new Database::PDDatabaseManager(this)), //
      m_pluginManager(new Core::PDPluginManager(this)),   //
      m_engine(new QQmlApplicationEngine(this))
{
    connect(pdApp->PluginManager(), &Core::PDPluginManager::OnQmlImportPathAdded, m_engine, &QQmlApplicationEngine::addImportPath);
}

PDApplication::~PDApplication()
{
}

void PDApplication::initialize()
{
    do
    {
        auto translator = new QTranslator(this);
        const auto uiLanguages = QLocale::system().uiLanguages();
        for (const auto &locale : uiLanguages)
        {
            const auto name = QLocale(locale).name();
            if (translator->load(u":/translations/PD_"_qs + name))
            {
                installTranslator(translator);
                break;
            }
        }
        delete translator;
    } while (false);

    m_pluginManager->LoadPlugins();

    pdRegisterModelType<Models::ActivityModel>();
    qmlRegisterSingletonInstance<Models::ActivityModel>(PD_QML_URI, 1, 0, "ActivityModel", new Models::ActivityModel(this));

    pdRegisterModelType<Models::PanelModel>();
    qmlRegisterSingletonInstance<Models::PanelModel>(PD_QML_URI, 1, 0, "PanelModel", new Models::PanelModel(this));

    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", new AppThemeModel(this));

    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<Database::PDDatabaseManager>(PD_QML_URI, 1, 0, "DBManager", m_dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);
#if defined(Q_OS_MAC) && defined(QT_DEBUG)
    m_engine->addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif
    m_engine->rootContext()->setContextProperty(u"fixedFont"_qs, QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_engine->rootContext()->setProperty("QtVersion", QStringLiteral(QT_VERSION_STR));

    const static QUrl MainComponent{ u"qrc:/pd/mooody/me/MainComponent.qml"_qs };
    m_engine->load(MainComponent);
}

Database::PDDatabaseManager *PDApplication::DatabaseManager() const
{
    return m_dbManager;
}

Core::PDPluginManager *PDApplication::PluginManager() const
{
    return m_pluginManager;
}

QStringList PDApplication::GetAssetsPath(const QString &dirName)
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
