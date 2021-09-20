#include "PDApplication.hpp"

#include <QDirIterator>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    PD::PDApplication app(argc, argv);

    QDirIterator it(u":/"_qs, {}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();

    app.initialize();
    return app.exec();
}
