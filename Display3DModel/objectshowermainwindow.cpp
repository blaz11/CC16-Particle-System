#include "objectshowermainwindow.h"

ObjectShowerMainWindow::ObjectShowerMainWindow()
{
    layout = new QGridLayout;

    QWidget * central = new QWidget();
    setCentralWidget(central);
    centralWidget()->setLayout(layout);

    setWindowTitle("Camera Window");
    setFixedSize(1000, 800);
}
