#include "PDApplication.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/PanelModel.hpp"
#include "Models/ThemesModel.hpp"

#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#define PD_QML_URI "pd.mooody.me"

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
}

int PDApplication::exec()
{
#if defined(Q_OS_MAC) && defined(QT_DEBUG)
    m_engine->addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif
    m_engine->rootContext()->setContextProperty(u"fixedFont"_qs, QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_engine->rootContext()->setProperty("QtVersion", QStringLiteral(QT_VERSION_STR));

    const static QUrl MainComponent{ u"qrc:/pd/mooody/me/MainComponent.qml"_qs };
    m_engine->load(MainComponent);

    return QCoreApplication::exec();
}

Database::PDDatabaseManager *PDApplication::DatabaseManager() const
{
    return m_dbManager;
}

Core::PDPluginManager *PDApplication::PluginManager() const
{
    return m_pluginManager;
}
