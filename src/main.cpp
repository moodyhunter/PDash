#include "platforms/MainWindow.hpp"

#include <QGuiApplication>
#include <QLocale>
#include <QQuickWindow>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickWindow::setDefaultAlphaBuffer(true);

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

    MainWindow window;
    window.show();

    return app.exec();
}
