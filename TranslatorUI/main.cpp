#undef __STRICT_ANSI__
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    wchar_t x[5];
    swprintf(x,0,L"salam");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
