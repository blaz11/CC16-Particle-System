#ifndef PIPEOBJECT_H
#define PIPEOBJECT_H

#include <QOpenGLVertexArrayObject>
#include <vector>
#include <qmath.h>
#include <Libraries/glm/gtc/matrix_transform.hpp>
#include <Libraries/glm/gtc/type_ptr.hpp>
#include "drawableobject.h"
#include "shader.h"
#include "triangle.h"

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
    const float steps = 32;
    glm::mat4 projection;
    int numberOfVertices;
    QOpenGLVertexArrayObject vao;
    vector<GLfloat> generatePipeVertices(const float R1, const float R2, const float H);

};

#endif // PIPEOBJECT_H
