#ifndef PIPEOBJECT_H
#define PIPEOBJECT_H

#include <QOpenGLVertexArrayObject>
#include <vector>
#include <qmath.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    void generatePipeVertices(const float radius, const float height, vector<GLfloat>& vertices,
                              vector<GLfloat>& normals, vector<GLfloat>& textures);

};

#endif // PIPEOBJECT_H
