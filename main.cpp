#include "mainwindow.h"
#include <QApplication>
#include "tools.h"
#include "array.h"
#include "learning.h"
#include <qdebug>
#include <list>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    w.show();




    return a.exec();
}
