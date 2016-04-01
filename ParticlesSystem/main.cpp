#include "mainwindow.h"
#include "Logic/particleemitter.h"
#include "Logic/particledata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
