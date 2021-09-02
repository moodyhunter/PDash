#include "PDApplication.hpp"

#include "DB/DBManager.hpp"
#include "Models/ActivitiesModel.hpp"
#include "Models/MainWindowModel.hpp"
#include "Models/ThemesModel.hpp"

#include <QFontDatabase>
#include <QQmlContext>
#include <QTranslator>

#ifdef Q_OS_MAC
#include "platforms/MainWindow-macOS.hpp"
#else
#include <QQmlApplicationEngine>
#endif

#if PD_DEBUG_MODEL
#include <QListView>
#endif

#define PD_QML_URI "pd.mooody.me"

PDApplication::PDApplication(int &argc, char *argv[])
    : PD_APP_CLASS(argc, argv),                        //
      m_appTheme(new AppThemeModel),                   //
      m_mainWindowModel(new MainWindowModel),          //
      m_dbManager(new PD::Database::PDDatabaseManager) //
{
    qpmRegisterType<MainWindowModel>();
    qpmRegisterType<AppThemeModel>();
    pdRegisterModelType<PD::Models::ActivityModel>();
    qmlRegisterType<PanelModel>(PD_QML_URI, 1, 0, "PanelModel");
    qmlRegisterType<MainWindowModel>(PD_QML_URI, 1, 0, "MainWindowModel");
    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", m_appTheme);
    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<PD::Database::PDDatabaseManager>(PD_QML_URI, 1, 0, "DBManager", m_dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);
}

PDApplication::~PDApplication()
{
    delete m_appTheme;
    delete m_dbManager;
    delete m_mainWindowModel;
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
#ifdef Q_OS_MAC
    MainWindow window;
    window.setTitle(QObject::tr("PD - The Personal Dashboard"));
    window.show();
#else
    QQmlApplicationEngine engine;
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    engine.rootContext()->setContextProperty(QStringLiteral("fixedFont"), fixedFont);

    const static QUrl url(u"qrc:/qml/MainWindow.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, this,
        [](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
#endif
#endif
    return QCoreApplication::exec();
}

PD::Database::PDDatabaseManager *PDApplication::DatabaseManager() const
{
    return m_dbManager;
}
