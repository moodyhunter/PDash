#include "PDApplication.hpp"

#include <iostream>

void logger(QtMsgType, const QMessageLogContext &ctx, const QString &str)
{
    std::cout << ctx.file << ":" << ctx.line << "[" << ctx.function << "]: " << str.toStdString();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logger);
    PDApplication app(argc, argv);
    app.initialize();
    return app.exec();
}
