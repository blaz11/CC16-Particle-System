#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <Libraries/glm/glm.hpp>
#include <QWheelEvent>
#include <QMouseEvent>
#include <Libraries/glm/gtc/matrix_transform.hpp>
#include <qmath.h>
#include <QDebug>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{

public:
    Camera(glm::vec3 object_center, float dist);

    void WheelEvent(QWheelEvent* ev);
    bool MouseMove(QMouseEvent* ev);
    void MousePressed(QMouseEvent* ev);
    void MouseReleased(QMouseEvent* ev);

    glm::mat4 GetViewMatrix();

    glm::vec3 GetUpVector();
    glm::vec3 getCoordinatesVector();

private:
    const double ROTATION_MULTIPLIER = 0.005;
    const double EPSILON = 1e-4;

    glm::vec3 camera_position;
    glm::vec3 camera_target;
    glm::vec3 up_vector;
    QPoint last_position;

    double theta, phi, radius;
    int theta_sign = 1;
    float distance;
    bool leftButtonPressed;
    bool rightButtonPressed;

};

#endif // CAMERA_H
