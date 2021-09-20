#include "PDApplication.hpp"

#include <QQuickWindow>

int main(int argc, char *argv[])
{
    PD::PDApplication app(argc, argv);
    app.initialize();
    return app.exec();
}
