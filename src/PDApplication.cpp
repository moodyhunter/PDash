#include "PDApplication.hpp"

#include "DB/DBManager.hpp"
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

#define PD_QML_URI "pd.mooody.me"

PDApplication::PDApplication(int &argc, char *argv[])
    : QGuiApplication(argc, argv),          //
      appTheme(new AppThemeModel),          //
      mainWindowModel(new MainWindowModel), //
      dbManager(new DBManager)
{
    qmlRegisterType<MainWindowModel>(PD_QML_URI, 1, 0, "MainWindowModel");
    qmlRegisterSingletonInstance<AppThemeModel>(PD_QML_URI, 1, 0, "AppTheme", appTheme);
    qmlRegisterSingletonInstance<PDApplication>(PD_QML_URI, 1, 0, "PDApp", this);
    qmlRegisterSingletonInstance<DBManager>(PD_QML_URI, 1, 0, "DBManager", dbManager);
    qmlRegisterModule(PD_QML_URI, 1, 0);
}

PDApplication::~PDApplication()
{
    delete appTheme;
    delete dbManager;
    delete mainWindowModel;
}

void PDApplication::initialize()
{
    auto translator = new QTranslator(this);
    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages)
    {
        const auto baseName = "PD_" + QLocale(locale).name();
        if (translator->load(":/translations/" + baseName))
        {
            installTranslator(translator);
            return;
        }
    }
    delete translator;
}

int PDApplication::exec()
{
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
    return QGuiApplication::exec();
}