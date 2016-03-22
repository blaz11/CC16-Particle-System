#ifndef OBJECTSHOWERMAINWINDOW_H
#define OBJECTSHOWERMAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class ObjectShowerMainWindow : public QMainWindow
{
public:
    ObjectShowerMainWindow();

private:
    QGridLayout *layout;
};

#endif // OBJECTSHOWERMAINWINDOW_H
