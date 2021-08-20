#include "PDApplication.hpp"

int main(int argc, char *argv[])
{
    PDApplication app(argc, argv);
    app.initialize();
    return app.exec();
}
