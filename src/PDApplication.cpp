#include "PDApplication.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/ComponentPropertyModel.hpp"
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
      m_pluginManager(new Core::PDPluginManager(this))    //
{
}

PDApplication::~PDApplication()
{
}

int PDApplication::run()
{
    QQmlApplicationEngine engine;
    QObject::connect(m_pluginManager, &Core::PDPluginManager::OnQmlImportPathAdded, &engine, &QQmlApplicationEngine::addImportPath);
    m_pluginManager->LoadPlugins();

    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages)
    {
        const auto fileName = u":/translations/PD_%1.qm"_qs.arg(QLocale(locale).name());
        if (QFile::exists(fileName))
        {
            auto translator = new QTranslator(this);
            if (translator->load(fileName))
            {
                installTranslator(translator);
                break;
            }
            delete translator;
        }
    }

    pdRegisterModelType<Models::ActivityModel>();
    qmlRegisterSingletonInstance<Models::ActivityModel>(PD_QML_URI, 1, 0, "ActivityModel", new Models::ActivityModel(this));

    pdRegisterModelType<Models::PanelModel>();
    qmlRegisterSingletonInstance<Models::PanelModel>(PD_QML_URI, 1, 0, "PanelModel", new Models::PanelModel(this));

    qmlRegisterType<Models::ComponentPropertyModel>(PD_QML_URI, 1, 0, "ComponentPropertyModel");

    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", new AppThemeModel(this));

    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<Database::PDDatabaseManager>(PD_QML_URI, 1, 0, "DBManager", m_dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);

#if defined(Q_OS_MAC) && defined(QT_DEBUG)
    engine.addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif
    engine.rootContext()->setContextProperty(u"fixedFont"_qs, QFontDatabase::systemFont(QFontDatabase::FixedFont));
    engine.rootContext()->setProperty("QtVersion", QStringLiteral(QT_VERSION_STR));

    const QUrl MainComponent{ u"qrc:/pd/mooody/me/MainComponent.qml"_qs };
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, this,
        [&](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && MainComponent == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(MainComponent);
    return exec();
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
