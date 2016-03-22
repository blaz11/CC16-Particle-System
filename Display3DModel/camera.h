#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QWheelEvent>
#include "modelwindow.h"

class Camera
{

public:
    Camera(QVector3D object_center, float dist);

    void WheelEvent(QWheelEvent* ev);
    void MouseMove(QMouseEvent* ev);
    void MousePressed(QMouseEvent* ev);
    void MouseReleased(QMouseEvent* ev);

    QMatrix4x4 GetViewMatrix();

    QVector3D GetUpVector();
    QVector3D getCoordinatesVector();

private:
    const double ROTATION_MULTIPLIER = 0.005;
    const double EPSILON = 1e-4;

    QVector3D camera_position;
    QVector3D camera_target;
    QVector3D up_vector;
    QPoint last_position;

    double theta, phi, radius;
    int theta_sign = 1;
    float distance;
    bool leftButtonPressed;
    bool rightButtonPressed;

};

#endif // CAMERA_H
