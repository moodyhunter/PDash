#include "PDApplication.hpp"

#include "Core/PluginManager.hpp"
#include "DB/DBManager.hpp"
#include "MainWindow.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/PanelModel.hpp"
#include "Models/ThemesModel.hpp"

#include <QTranslator>

#if PD_DEBUG_MODEL
#include <QListView>
#endif

#define PD_QML_URI "pd.mooody.me"

using namespace PD;

PDApplication::PDApplication(int &argc, char *argv[])
    : PD_APP_CLASS(argc, argv),                           //
      m_dbManager(new Database::PDDatabaseManager(this)), //
      m_pluginManager(new Core::PDPluginManager(this))
{
    QQuickWindow::setDefaultAlphaBuffer(true);
    m_mainWindow = new PDMainWindow;
    pdRegisterModelType<Models::ActivityModel>();
    qmlRegisterSingletonInstance<Models::ActivityModel>(PD_QML_URI, 1, 0, "ActivityModel", new Models::ActivityModel(this));

    pdRegisterModelType<Models::PanelModel>();
    qmlRegisterSingletonInstance<Models::PanelModel>(PD_QML_URI, 1, 0, "PanelModel", new Models::PanelModel(this));

    qpmRegisterType<AppThemeModel>();
    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", new AppThemeModel(this));

    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<Database::PDDatabaseManager>(PD_QML_URI, 1, 0, "DBManager", m_dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);
}

PDApplication::~PDApplication()
{
    delete m_mainWindow;
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
}

int PDApplication::exec()
{
#if PD_DEBUG_MODEL
    Models::ActivityModel model;
    m_dbManager->openDatabase(u"default"_qs, {});
    QListView listview;
    listview.setModel(&model);
    listview.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    listview.show();
#else
    m_mainWindow->Open();
#endif
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
