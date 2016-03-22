#include "modelposition.h"

ModelPosition::ModelPosition()
{
    ResetPosition();
}

void ModelPosition::MouseMove(QMouseEvent* ev)
{
    QPoint new_position = ev->pos();
    if(rightButtonPressed)
    {
        auto d_x = (new_position.x() - last_position.x()) * TRANSLATE_MULTIPLIER;
        auto d_y = (new_position.y() - last_position.y()) * TRANSLATE_MULTIPLIER;
        auto camera_coordinates = camera->getCoordinatesVector();
        if(camera_coordinates.x() >= 0 && camera_coordinates.y() >= 0 && camera_coordinates.z() >= 0)
        {
            model_matrix.translate(-d_x, -d_y, 0);
            //qDebug() << "+++";
        }
        else if(camera_coordinates.x() < 0 && camera_coordinates.y() >= 0 && camera_coordinates.z() >= 0)
        {
            model_matrix.translate(0, -d_y, -d_x);
            //qDebug() << "-++";
        }
        else if(camera_coordinates.x() >= 0 && camera_coordinates.y() < 0 && camera_coordinates.z() >= 0)
        {
            model_matrix.translate(-d_x, -d_y, 0);
            //qDebug() << "+-+";
        }
        else if(camera_coordinates.x() >= 0 && camera_coordinates.y() >= 0 && camera_coordinates.z() < 0)
        {
            model_matrix.translate(0, -d_y, d_x);
            //qDebug() << "++-";
        }
        else if(camera_coordinates.x() < 0 && camera_coordinates.y() < 0 && camera_coordinates.z() >= 0)
        {
            model_matrix.translate(-d_x, -d_y, 0);
            //qDebug() << "--+";
        }
        else if(camera_coordinates.x() < 0 && camera_coordinates.y() >= 0 && camera_coordinates.z() < 0)
        {
            model_matrix.translate(d_y, 0, -d_x);
            //qDebug() << "-+-";
        }
        else if(camera_coordinates.x() >= 0 && camera_coordinates.y() < 0 && camera_coordinates.z() < 0)
        {
            model_matrix.translate(0, -d_y, -d_x);
            //qDebug() << "+--";
        }
        else if(camera_coordinates.x() < 0 && camera_coordinates.y() < 0 && camera_coordinates.z() < 0)
        {
            model_matrix.translate(d_y, 0, -d_x);
            //qDebug() << "---";
        }
        //qDebug() << "translating by: " << d_x << "," << d_y;
        //model_matrix.translate(-d_x, -d_y, 0);
    }
    last_position = new_position;
}

void ModelPosition::MousePressed(QMouseEvent* ev)
{
    if(IsRightButtonPressed(ev))
    {
       rightButtonPressed = true;
    }
}

void ModelPosition::MouseReleased(QMouseEvent* ev)
{
    if(!IsRightButtonPressed(ev))
        rightButtonPressed = false;
}

QMatrix4x4 ModelPosition::GetModelMatrix()
{
    return model_matrix;
}

void ModelPosition::SetCamera(Camera *new_camera)
{
    camera = new_camera;
}

void ModelPosition::ResetPosition()
{
    model_matrix.setToIdentity();
}
