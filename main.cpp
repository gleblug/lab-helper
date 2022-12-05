#include "mainwindow.hpp"

#include <QApplication>
#include <locale>

int main(int argc, char *argv[])
{
//    std::locale::global("eng");
    std::locale lcl; // создает копию текущей глобальной локали
    const auto & facet = std::use_facet<std::numpunct<char>>(lcl);
    std::cout << facet.decimal_point() << std::endl; // печатает точку!

    QApplication a(argc, argv);
    MainWindow w;

    w.resize(800, 600);
    w.show();

    return a.exec();
}
