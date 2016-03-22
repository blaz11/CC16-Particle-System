#ifndef MODELPOSITION_H
#define MODELPOSITION_H

#include <QVector3D>
#include <QMatrix4x4>
#include "modelwindow.h"

class Camera;

class ModelPosition
{
public:
    ModelPosition();

    void MouseMove(QMouseEvent* ev);
    void MousePressed(QMouseEvent* ev);
    void MouseReleased(QMouseEvent* ev);
    QMatrix4x4 GetModelMatrix();

    void SetCamera(Camera* new_camera);
    QVector3D FindDominantCameraAxis();
    void ResetPosition();
private:
    Camera* camera;
    QMatrix4x4 model_matrix;
    QPoint last_position;

    bool rightButtonPressed;
    const double TRANSLATE_MULTIPLIER = 0.005;

};

#endif // MODELPOSITION_H
