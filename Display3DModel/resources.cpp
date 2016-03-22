#include "resources.h"

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
