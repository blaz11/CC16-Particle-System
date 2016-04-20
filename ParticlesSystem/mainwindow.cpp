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
    sett->velocityVector.x = arg;
    normalize();
}

void MainWindow::on_spinBox_2_valueChanged(int arg)
{
    sett->velocityVector.y = arg;
    normalize();
}

void MainWindow::on_spinBox_3_valueChanged(int arg)
{
    sett->velocityVector.z = arg;
    normalize();
}

void MainWindow::normalize()
{
    float x = sett->velocityVector.x;
    float y = sett->velocityVector.y;
    float z = sett->velocityVector.z;

    float length = (float)sqrt(x*x + y*y + z*z);

    if(length > 0)
    {
        sett->velocityVector.x = x / length;
        sett->velocityVector.y = y / length;
        sett->velocityVector.z = z / length;
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

void MainWindow::on_spinBox_6_valueChanged(int arg)
{
    sett->startPosition.x = arg;
}

void MainWindow::on_spinBox_7_valueChanged(int arg)
{
    sett->startPosition.y = arg;
}

void MainWindow::on_spinBox_8_valueChanged(int arg)
{
    sett->startPosition.z = arg;
}
