#ifndef UICONNECTOR_H
#define UICONNECTOR_H

#include <QFileDialog>
//#include <QSlider>
#include "modelwindow.h"

class UIConnector : public QObject
{
    Q_OBJECT
public:
    explicit UIConnector(QObject* parent = 0);

    ModelWindow* model_window;

public slots:
    void handleLoadModelButtonClick();
    void handlePositionResetClick();

};

#endif // UICONNECTOR_H
