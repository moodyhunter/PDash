#include "MainWindow.hpp"

#include "platforms/Platform.hpp"

#include <QCoreApplication>
#include <QFontDatabase>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

constexpr auto WINDOW_WIDTH = 1300;
constexpr auto WINDOW_HEIGHT = 700;

void SetupQMLContext(QQmlContext *ctx)
{
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ctx->setContextProperty(u"fixedFont"_qs, fixedFont);
}

PDMainWindow::PDMainWindow() : QQuickView()
{
    const static QUrl MainComponent{ u"qrc:/qml/MainComponent.qml"_qs };
#ifdef Q_OS_MACOS
    m_effectsBackgroundWindow = PD::Platform::PDPlatformAPI::getEffectBackgroundWindow();
    quickWindow = new QQuickView(this);
#ifdef QT_DEBUG
    quickWindow->engine()->addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif

    SetupQMLContext(quickWindow->rootContext());
    quickWindow->rootContext()->setContextProperty(u"rootWindow"_qs, quickWindow);
    quickWindow->rootContext()->setContextProperty(u"hasBackgroundEffect"_qs, m_effectsBackgroundWindow != nullptr);

    quickWindow->setSource(MainComponent);
    quickWindow->show();
    quickWindow->requestActivate();

    if (m_effectsBackgroundWindow)
    {
        m_effectsBackgroundWindow->setParent(this);
        m_effectsBackgroundWindow->show();
        m_effectsBackgroundWindow->lower();
    }
#else
    rootContext()->setContextProperty(u"rootWindow"_qs, this);
    rootContext()->setContextProperty(u"hasBackgroundEffect"_qs, false);
    SetupQMLContext(this->rootContext());
    setSource(MainComponent);
#endif
    setWidth(WINDOW_WIDTH);
    setHeight(WINDOW_HEIGHT);
    setTitle(tr("PD - The Personal Dashboard"));
}

#ifdef Q_OS_MAC
void PDMainWindow::resizeEvent(QResizeEvent *)
{
    quickWindow->setGeometry(0, 0, this->width(), this->height());
    if (m_effectsBackgroundWindow)
        m_effectsBackgroundWindow->setGeometry(0, 0, this->width(), this->height());
}
#endif
