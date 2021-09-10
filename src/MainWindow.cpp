#include "MainWindow.hpp"

#include "Core/PluginManager.hpp"
#include "PDApplication.hpp"
#include "platforms/Platform.hpp"

#include <QCoreApplication>
#include <QDirIterator>
#include <QFontDatabase>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

constexpr auto WINDOW_WIDTH = 1300;
constexpr auto WINDOW_HEIGHT = 700;

using namespace PD;

PDMainWindow::PDMainWindow() : QQuickView(), quickWindow(this)
{
    connect(pdApp->PluginManager(), &Core::PDPluginManager::OnQmlImportPathAdded, this, &PDMainWindow::p_QmlImportPathAdded);

    const static auto prop_RootWindow = u"rootWindow"_qs;
    const static auto prop_hasBackgroundEffect = u"hasBackgroundEffect"_qs;

#ifdef Q_OS_MACOS
    quickWindow = new QQuickView(this);
#endif

#ifdef QT_DEBUG
    quickWindow->engine()->addImportPath(qApp->applicationDirPath() + u"/../../../");
#endif
    quickWindow->rootContext()->setContextProperty(prop_RootWindow, this);
    quickWindow->rootContext()->setContextProperty(prop_hasBackgroundEffect, false);
    quickWindow->rootContext()->setContextProperty(u"fixedFont"_qs, QFontDatabase::systemFont(QFontDatabase::FixedFont));
}

void PDMainWindow::Open()
{
    QDirIterator it(u":/pd/mooody/me/"_qs, {}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();
    const static QUrl MainComponent{ u"qrc:/pd/mooody/me/MainComponent.qml"_qs };
    quickWindow->setSource(MainComponent);
#ifdef Q_OS_MACOS
    quickWindow->show();
    quickWindow->requestActivate();
    m_effectsBackgroundWindow = Platform::PDPlatformAPI::getEffectBackgroundWindow();
    m_effectsBackgroundWindow->setParent(this);
    m_effectsBackgroundWindow->show();
    m_effectsBackgroundWindow->lower();
#endif
    setWidth(WINDOW_WIDTH);
    setHeight(WINDOW_HEIGHT);
    setTitle(tr("PD - The Personal Dashboard"));
    show();
}


void PDMainWindow::p_QmlImportPathAdded(const QString &path)
{
#ifdef Q_OS_MACOS
    quickWindow->engine()->addImportPath(path);
#else

    QDirIterator it(u":/pdplugins/"_qs, {}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();

    this->engine()->addImportPath(path);
    this->engine()->addImportPath(u":/pdplugins/"_qs);
#endif
}

#ifdef Q_OS_MAC
void PDMainWindow::resizeEvent(QResizeEvent *)
{
    quickWindow->setGeometry(0, 0, this->width(), this->height());
    if (m_effectsBackgroundWindow)
        m_effectsBackgroundWindow->setGeometry(0, 0, this->width(), this->height());
}
#endif
