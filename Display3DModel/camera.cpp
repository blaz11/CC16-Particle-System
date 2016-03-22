#include "camera.h"
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const int CAMERA_RADIUS = 8;
const double ZOOM_SPEED = 0.0003;

Camera::Camera(QVector3D object_center, float dist) :
    camera_target(object_center),
    up_vector(QVector3D(0.0f, 1.0f, 0.0f))
{
    distance = dist + CAMERA_RADIUS;
    qDebug() << dist;
    radius = dist;
    phi = M_PI;
    theta = M_PI / 2;
    leftButtonPressed = false;
}

void Camera::WheelEvent(QWheelEvent *ev)
{
    auto zoom_change = distance * ev->angleDelta().y() * ZOOM_SPEED;
    radius -= zoom_change;
}

void Camera::MouseMove(QMouseEvent* ev)
{
    QPoint new_position = ev->pos();
    if(IsMouseOutSideScene(new_position))
    {
        rightButtonPressed = false;
        leftButtonPressed = false;
        return;
    }
    if(leftButtonPressed)
    {
        auto d_x = (new_position.x() - last_position.x()) * ROTATION_MULTIPLIER;
        auto d_y = (new_position.y() - last_position.y()) * ROTATION_MULTIPLIER;
        theta += d_y*theta_sign;
        phi += d_x*theta_sign;
        //qDebug() << "Phi: " << phi / M_PI;
        //qDebug() << "Theta: " << theta / M_PI;
        if(theta > M_PI)
        {
            theta = M_PI - EPSILON;
            phi += M_PI;
            up_vector *= -1;
            theta_sign *= -1;
        }
        else if(theta < EPSILON)
        {
            theta = EPSILON;
            phi += M_PI;
            up_vector *= -1;
            theta_sign *= -1;
        }
        if(phi < 0)
            phi += 2 * M_PI;
        else if(phi > 2*M_PI)
            phi -= 2 * M_PI;
    }
    if(rightButtonPressed)
    {

    }
    last_position = new_position;
}

void Camera::MousePressed(QMouseEvent* ev)
{
    if(IsLeftButtonPressed(ev))
    {
        leftButtonPressed = true;
        last_position = ev->pos();
    }
    if(IsRightButtonPressed(ev))
    {
       rightButtonPressed = true;
    }
}

void Camera::MouseReleased(QMouseEvent* ev)
{
    if(!IsLeftButtonPressed(ev))
        leftButtonPressed = false;
    if(!IsRightButtonPressed(ev))
        rightButtonPressed = false;
}

QMatrix4x4 Camera::GetViewMatrix()
{
    auto new_coordinates = getCoordinatesVector();
    camera_position = new_coordinates;
    QMatrix4x4 view_matrix;
    view_matrix.setToIdentity();
    view_matrix.lookAt(
                camera_position,
                camera_target,
                up_vector);
    return view_matrix;
}

QVector3D Camera::getCoordinatesVector()
{
    auto new_x = -radius*sin(theta)*cos(phi);
    auto new_y = -radius*cos(theta);
    auto new_z = -radius*sin(theta)*sin(phi);
    return QVector3D(new_x,new_y,new_z) + camera_target;
}

QVector3D Camera::GetUpVector()
{
    return up_vector;
}
