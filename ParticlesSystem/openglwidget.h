#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <vector>
#include <algorithm>
#include <Libraries/glm/glm.hpp>
#include <Qdebug>
#include <QPoint>
#include <QTimer>
#include "drawableobject.h"
#include "camera.h"
#include "shader.h"
#include "pipeobject.h"
#include "particlesystemrender.h"
#include "Logic/particlesystem.h"

using namespace std;

class OpenGLWidget : public QOpenGLWidget
{
        Q_OBJECT

public:
    OpenGLWidget(QWidget *parent);
    ~OpenGLWidget();
    void addObjectToScene(DrawableObject* object);
    void removeObjectFromScene(DrawableObject* object);



protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Camera* camera;
    Shader* shader;
    ParticleSystem system;
    vector<DrawableObject*> objects;

    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void drawingLoop();

};

#endif // OPENGLWIDGET_H
