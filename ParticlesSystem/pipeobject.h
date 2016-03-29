#ifndef PIPEOBJECT_H
#define PIPEOBJECT_H

#include <QOpenGLVertexArrayObject>
#include <vector>
#include "drawableobject.h"
#include "shader.h"

using namespace std;

class PipeObject : public DrawableObject
{
public:
    PipeObject();
    ~PipeObject() override;

    void initialize(QOpenGLFunctions *f) override;
    void draw(QOpenGLFunctions *f, Shader* shader, glm::mat4 view_matrix) override;
    void update() override;

private:
   QOpenGLVertexArrayObject vao;
   vector<GLfloat> generatePipeVertices();

};

#endif // PIPEOBJECT_H
