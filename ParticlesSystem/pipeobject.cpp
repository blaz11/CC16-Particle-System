#include "pipeobject.h"

PipeObject::PipeObject()
{

}

PipeObject::~PipeObject()
{

}

void PipeObject::initialize(QOpenGLFunctions *f)
{
    projection = glm::perspective(45.0f, 2.0f, 0.01f, 100.0f);
    vector<GLfloat> positions, normals;
    Cylinder cylinder;
    cylinder.generateDataForVBOs(positions, normals);
    numberOfVertices = positions.size() / 3;
    GLuint VBO;
    vao.create();
    f->glGenBuffers(1, &VBO);
    vao.bind();
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    f->glEnableVertexAttribArray(0);
    vao.release();
}

void PipeObject::draw(QOpenGLFunctions *f, Shader* shader, glm::mat4 view)
{
    glm::vec3 position(0.0f,  0.0f,  0.0f);
    glm::mat4 model;
    model = glm::translate(model, position);
    shader->use(f);
    vao.bind();
    GLint modelLoc = f->glGetUniformLocation(shader->Program, "model");
    GLint viewLoc = f->glGetUniformLocation(shader->Program, "view");
    GLint projLoc = f->glGetUniformLocation(shader->Program, "projection");
    GLint colorLoc = f->glGetUniformLocation(shader->Program, "color");
    f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    f->glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    f->glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    f->glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
    f->glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
    vao.release();
}

void PipeObject::update()
{
}

vector<GLfloat> PipeObject::generatePipeVertices(const float R1, const float R2, const float H)
{
    vector<GLfloat> vertices;
    double phi = 0;
    double dphi = 2 * M_PI / steps;
    numberOfVertices = 0;
    for(int i = 0; i <= steps; ++i, phi += dphi, numberOfVertices += 2)
    {
        GLfloat x1 = R1*cos(phi);
        GLfloat y1 = R1*sin(phi);
        GLfloat z1 = -H/2;
        GLfloat x2 = R2*cos(phi);
        GLfloat y2 = R2*sin(phi);
        GLfloat z2 = H/2;
        vertices.push_back(x1);
        vertices.push_back(y1);
        vertices.push_back(z1);
        vertices.push_back(x2);
        vertices.push_back(y2);
        vertices.push_back(z2);
    }
    return vertices;
}
