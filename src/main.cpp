#include "PDApplication.hpp"

#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QQuickWindow::setDefaultAlphaBuffer(true);
    PD::PDApplication app(argc, argv);
    app.initialize();
    return app.exec();
}
