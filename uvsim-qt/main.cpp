#include "mainwindow.h"
#include "../uvsim.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("UVSim");
    w.show();
    return a.exec();
}
