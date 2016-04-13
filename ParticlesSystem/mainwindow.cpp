#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sett = new Settings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    sett->velocityValue = position;
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    sett->variation = position;
}

void MainWindow::on_spinBox_valueChanged(int arg)
{
    sett->valocityVector->x = arg;
    normalize();
}

void MainWindow::on_spinBox_2_valueChanged(int arg)
{
    sett->valocityVector->y = arg;
    normalize();
}

void MainWindow::on_spinBox_3_valueChanged(int arg)
{
    sett->valocityVector->z = arg;
    normalize();
}

void MainWindow::normalize()
{
    float x = sett->valocityVector->x;
    float y = sett->valocityVector->y;
    float z = sett->valocityVector->z;

    float length = (float)sqrt(x*x + y*y + z*z);

    if(length > 0)
    {
        sett->valocityVector->x = x / length;
        sett->valocityVector->y = y / length;
        sett->valocityVector->z = z / length;
    }
}

void MainWindow::on_spinBox_4_valueChanged(int arg)
{
    sett->liveTime = arg;
}

void MainWindow::on_spinBox_5_valueChanged(int arg)
{
    sett->count = arg;
}
