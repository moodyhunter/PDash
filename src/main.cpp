#include "PDApplication.hpp"

int main(int argc, char *argv[])
{
    PD::PDApplication app(argc, argv);
    app.initialize();
    return app.exec();
}
