#ifndef RESOURCES
#define RESOURCES

#include <QMouseEvent>
#include <QVector3D>

#define SCENE_WIDTH 800
#define SCENE_HEIGHT 600
#define BACKGROUND_COLOR .1f, .0f, .6f ,1.0f

bool IsRightButtonPressed(QMouseEvent* ev);
bool IsLeftButtonPressed(QMouseEvent* ev);
bool IsMouseOutSideScene(QPoint new_position);

#endif // RESOURCES
