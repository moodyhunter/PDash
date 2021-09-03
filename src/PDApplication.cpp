#include "PDApplication.hpp"

#include "DB/DBManager.hpp"
#include "MainWindow.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/PanelModel.hpp"
#include "Models/ThemesModel.hpp"

#include <QQmlEngine>
#include <QQuickWindow>
#include <QTranslator>

#if PD_DEBUG_MODEL
#include <QListView>
#endif

#define PD_QML_URI "pd.mooody.me"

PDApplication::PDApplication(int &argc, char *argv[]) : PD_APP_CLASS(argc, argv), m_dbManager(new PD::Database::PDDatabaseManager)
{
    pdRegisterModelType<PD::Models::ActivityModel>();
    qmlRegisterSingletonInstance<PD::Models::ActivityModel>(PD_QML_URI, 1, 0, "ActivityModel", new PD::Models::ActivityModel(this));

    pdRegisterModelType<PD::Models::PanelModel>();
    qmlRegisterSingletonInstance<PD::Models::PanelModel>(PD_QML_URI, 1, 0, "PanelModel", new PD::Models::PanelModel(this));

    qpmRegisterType<AppThemeModel>();
    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", new AppThemeModel(this));

    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<PD::Database::PDDatabaseManager>(PD_QML_URI, 1, 0, "DBManager", m_dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);
}

PDApplication::~PDApplication()
{
    delete m_dbManager;
}

void PDApplication::initialize()
{
    auto translator = new QTranslator(this);
    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages)
    {
        if (translator->load(u":/translations/PD_"_qs + QLocale(locale).name()))
        {
            installTranslator(translator);
            return;
        }
    }
    delete translator;
}

int PDApplication::exec()
{
#if PD_DEBUG_MODEL
    PD::Models::ActivityModel model;
    m_dbManager->openDatabase(u"default"_qs, {});
    QListView listview;
    listview.setModel(&model);
    listview.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    listview.show();
#else
    QQuickWindow::setDefaultAlphaBuffer(true);
    MainWindow window;
    window.show();
#endif
    return QCoreApplication::exec();
}

PD::Database::PDDatabaseManager *PDApplication::DatabaseManager() const
{
    return m_dbManager;
}
