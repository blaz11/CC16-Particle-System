#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <algorithm>
#include <Libraries/glm/glm.hpp>
#include <Qdebug>
#include "drawableobject.h"
#include "camera.h"
#include "shader.h"
#include "pipeobject.h"

using namespace std;

class OpenGLWidget : public QOpenGLWidget
{
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
    vector<DrawableObject*> objects;

};

#endif // OPENGLWIDGET_H