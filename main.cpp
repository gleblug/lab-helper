#include "widget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget window;

    window.resize(350, 150);
    window.setWindowTitle("Lab Helper");

    window.show();
    return app.exec();
}
