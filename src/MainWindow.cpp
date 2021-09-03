#include "MainWindow.hpp"

#include "platforms/Platform.hpp"

#include <QCoreApplication>
#include <QFontDatabase>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

constexpr auto WINDOW_WIDTH = 1300;
constexpr auto WINDOW_HEIGHT = 700;

PDMainWindow::PDMainWindow() : QQuickWindow()
{
    setTitle(tr("PD - The Personal Dashboard"));

    setWidth(WINDOW_WIDTH);
    setHeight(WINDOW_HEIGHT);

    m_effectsBackgroundWindow = PD::Platform::PDPlatformAPI::getEffectBackgroundWindow();
    quickWindow = new QQuickView(this);
#if defined(QT_DEBUG) && defined(Q_OS_MAC)
    quickWindow->engine()->addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    quickWindow->rootContext()->setContextProperty(u"fixedFont"_qs, fixedFont);
    quickWindow->rootContext()->setContextProperty(u"rootWindow"_qs, quickWindow);
    quickWindow->rootContext()->setContextProperty(u"hasBackgroundEffect"_qs, m_effectsBackgroundWindow != nullptr);

    quickWindow->setSource({ u"qrc:/qml/MainComponent.qml"_qs });
    quickWindow->show();

    if (m_effectsBackgroundWindow)
    {
        m_effectsBackgroundWindow->setParent(this);
        m_effectsBackgroundWindow->show();
        m_effectsBackgroundWindow->lower();
    }
}

void PDMainWindow::resizeEvent(QResizeEvent *)
{
    quickWindow->setGeometry(0, 0, this->width(), this->height());
    if (m_effectsBackgroundWindow)
        m_effectsBackgroundWindow->setGeometry(0, 0, this->width(), this->height());
}
