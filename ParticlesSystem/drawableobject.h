#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <Libraries/glm/glm.hpp>
#include <QOpenGLFunctions>
#include "shader.h"

class DrawableObject
{
public:
    DrawableObject();
    virtual ~DrawableObject() {}
    virtual void initialize(QOpenGLFunctions *f) = 0;
    virtual void draw(QOpenGLFunctions *f, Shader* shader, glm::mat4 view_matrix) = 0;
    virtual void update() = 0;

};

#endif // DRAWABLEOBJECT_H
