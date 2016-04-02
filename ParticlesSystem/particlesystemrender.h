#ifndef PARTICLESYSTEMRENDER_H
#define PARTICLESYSTEMRENDER_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <QOpenGLVertexArrayObject>
#include "Logic/particlesystem.h"
#include "drawableobject.h"

using namespace std;

class ParticleSystemRender : public DrawableObject
{
public:
    ParticleSystemRender(ParticleSystem* sys);

    void initialize(QOpenGLFunctions *f) override;
    void draw(QOpenGLFunctions *f, Shader *shader, glm::mat4 view_matrix) override;
    void update() override;

private:
    glm::mat4 projection;
    int numberOfVertices;
    QOpenGLVertexArrayObject vao;

    ParticleSystem* system;

};

#endif // PARTICLESYSTEMRENDER_H
