#include "uiconnector.h"

UIConnector::UIConnector(QObject *parent)
    :QObject(parent)
{

}

void UIConnector::handleLoadModelButtonClick()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setToolTip(QString("Select model"));
    QStringList fileNames;
    if(!dialog.exec())
        return;
    fileNames = dialog.selectedFiles();
    if(fileNames.count() != 1)
       return;
    QString model_file = fileNames.at(0);
    model_window->LoadModel(fileNames.at(0),ModelLoader::PathType::AbsolutePath);
}

void UIConnector::handlePositionResetClick()
{
    model_window->model_position->ResetPosition();
}
