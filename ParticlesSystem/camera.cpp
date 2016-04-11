#include "camera.h"

const int CAMERA_RADIUS = 8;
const double ZOOM_SPEED = 0.0003;
#define SCENE_WIDTH 800
#define SCENE_HEIGHT 600

bool IsLeftButtonPressed(QMouseEvent* ev)
{
    return ev->buttons() & Qt::LeftButton;
}

bool IsRightButtonPressed(QMouseEvent* ev)
{
    return ev->buttons() & Qt::RightButton;
}

bool IsMouseOutSideScene(QPoint new_position)
{
    return new_position.x() < 0 ||
           new_position.x() > SCENE_WIDTH ||
           new_position.y() < 0 ||
           new_position.y() > SCENE_HEIGHT;
}

Camera::Camera(glm::vec3 object_center, float dist) :
    camera_target(object_center),
    up_vector(glm::vec3(0.0f, 1.0f, 0.0f))
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

bool Camera::MouseMove(QMouseEvent* ev)
{
    QPoint new_position = ev->pos();
    if(IsMouseOutSideScene(new_position))
    {
        rightButtonPressed = false;
        leftButtonPressed = false;
        return false;
    }
    bool res = false;
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
        res = true;
    }
    if(rightButtonPressed)
    {

    }
    last_position = new_position;
    return res;
}

void Camera::MousePressed(QMouseEvent* ev)
{
    if(IsLeftButtonPressed(ev))
    {
        leftButtonPressed = true;
    }
    if(IsRightButtonPressed(ev))
    {
       rightButtonPressed = true;
    }
    last_position = ev->pos();
}

void Camera::MouseReleased(QMouseEvent* ev)
{
    if(!IsLeftButtonPressed(ev))
        leftButtonPressed = false;
    if(!IsRightButtonPressed(ev))
        rightButtonPressed = false;
}

glm::mat4 Camera::GetViewMatrix()
{
    auto new_coordinates = getCoordinatesVector();
    camera_position = new_coordinates;
    return glm::lookAt(camera_position, camera_target, up_vector);
}

glm::vec3 Camera::getCoordinatesVector()
{
    auto new_x = -radius*sin(theta)*cos(phi);
    auto new_y = -radius*cos(theta);
    auto new_z = -radius*sin(theta)*sin(phi);
    return glm::vec3(new_x,new_y,new_z) + camera_target;
}

glm::vec3 Camera::GetUpVector()
{
    return up_vector;
}
