#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    private slots:
        void on_horizontalSlider_sliderMoved(int position);
        void on_spinBox_valueChanged(int arg);
        void on_horizontalSlider_2_sliderMoved(int position);
        void on_spinBox_2_valueChanged(int arg);
        void on_spinBox_3_valueChanged(int arg);
        void on_spinBox_4_valueChanged(int arg);
        void on_spinBox_5_valueChanged(int arg);

    private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
