#include "MainWindow.hpp"

#include "platforms/Platform.hpp"

#include <QCoreApplication>
#include <QFontDatabase>
#include <QQmlContext>
#include <QQmlEngine>

constexpr auto WINDOW_WIDTH = 1300;
constexpr auto WINDOW_HEIGHT = 700;

MainWindow::MainWindow() : QQuickWindow()
{
    setTitle(tr("PD - The Personal Dashboard"));
    QQuickWindow::setDefaultAlphaBuffer(true);

    setWidth(WINDOW_WIDTH);
    setHeight(WINDOW_HEIGHT);
    quickWindow = new QQuickView(this);

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    quickWindow->rootContext()->setContextProperty(u"fixedFont"_qs, fixedFont);
    quickWindow->rootContext()->setContextProperty(u"rootWindow"_qs, quickWindow);

    quickWindow->engine()->addImportPath(qApp->applicationDirPath() + u"/../../../");
    quickWindow->setSource({ u"qrc:/qml/MainComponent.qml"_qs });
    quickWindow->setColor(Qt::transparent);
    quickWindow->show();

    // Create the native effects view
    m_effectsBackgroundWindow = PD::Platform::PDPlatformAPI::getEffectBackgroundWindow();
    m_effectsBackgroundWindow->setParent(this);
    m_effectsBackgroundWindow->show();
    m_effectsBackgroundWindow->lower();
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    m_effectsBackgroundWindow->setGeometry(0, 0, this->width(), this->height());
    quickWindow->setGeometry(0, 0, this->width(), this->height());
}
