#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Settings* sett;
    ~MainWindow();

    private slots:
        void on_horizontalSlider_sliderMoved(int position);
        void on_horizontalSlider_2_sliderMoved(int position);
        void on_spinBox_valueChanged(int arg);
        void on_spinBox_2_valueChanged(int arg);
        void on_spinBox_3_valueChanged(int arg);
        void on_spinBox_4_valueChanged(int arg);
        void on_spinBox_5_valueChanged(int arg);
        void on_spinBox_6_valueChanged(int arg);
        void on_spinBox_7_valueChanged(int arg);
        void on_spinBox_8_valueChanged(int arg);
        void normalize();

    private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
