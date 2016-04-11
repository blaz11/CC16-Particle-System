#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    qDebug() << position;
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    qDebug() << position;
}

void MainWindow::on_spinBox_valueChanged(int arg)
{
    qDebug() << arg;
}

void MainWindow::on_spinBox_2_valueChanged(int arg)
{
    qDebug() << arg;
}

void MainWindow::on_spinBox_3_valueChanged(int arg)
{
    qDebug() << arg;
}

void MainWindow::on_spinBox_4_valueChanged(int arg)
{
    qDebug() << arg;
}

void MainWindow::on_spinBox_5_valueChanged(int arg)
{
    qDebug() << arg;
}
