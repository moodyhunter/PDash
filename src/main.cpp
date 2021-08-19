
#include "platforms/macOS-blurredWindow.hpp"

#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QTranslator>
#include <QtGui>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickWindow::setDefaultAlphaBuffer(true);

    TopWindow window;
    window.quickWindow->setSource({ "qrc:/qml/main.qml" });
    window.show();

    QTranslator translator;
    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages)
    {
        const auto baseName = "PD_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            app.installTranslator(&translator);
            break;
        }
    }

    //    QQmlApplicationEngine engine;
    //    const QUrl url(u"qrc:/qml/main.qml"_qs);
    //    QObject::connect(
    //        &engine, &QQmlApplicationEngine::objectCreated, &app,
    //        [url](QObject *obj, const QUrl &objUrl)
    //        {
    //            if (!obj && url == objUrl)
    //                QCoreApplication::exit(-1);
    //        },
    //        Qt::QueuedConnection);

    //    engine.load(url);

    return app.exec();
}
