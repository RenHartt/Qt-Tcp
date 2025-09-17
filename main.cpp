#include <QApplication>
#include "Controller.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Controller ctor;
    ctor.show();

    return app.exec();
}
