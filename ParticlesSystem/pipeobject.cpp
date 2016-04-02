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
    vector<GLfloat> positions, normals, textures;
 //   generatePipeVertices(1, 1, positions, normals, textures);
 //   numberOfVertices = positions.size() / 3;
    Cylinder cylinder;
    cylinder.generateDataForVBOs(positions, normals);
    numberOfVertices = positions.size() / 3;
    GLuint VBO;
    vao.create();
    f->glGenBuffers(1, &VBO);
    vao.bind();
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, positions.size(), positions.data(), GL_STATIC_DRAW);
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
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, numberOfVertices);
    vao.release();
}

void PipeObject::update()
{
}

void PipeObject::generatePipeVertices(const float radius, const float height, vector<GLfloat>& vertices,
                                      vector<GLfloat>& normals, vector<GLfloat>& textures)
{
    const int sides = 32;
    const float theta = 2 * M_PI / (float) sides,
                c = cos(theta),
                s = sin(theta);
    const float x = 0, y = 0, z = 0;
    float x2 = radius, z2 = 0;
    for(int i = 0 ; i <= sides; i++)
    {
        const float tx = (float) i / sides;
        const float nf = 1 / sqrt(x2*x2+z2*z2),
                    xn = x2*nf,
                    zn = z2*nf;
        normals.push_back(xn);
        normals.push_back(0);
        normals.push_back(zn);
        textures.push_back(tx);
        textures.push_back(0);
        vertices.push_back(x+x2);
        vertices.push_back(y);
        vertices.push_back(z+z2);

        normals.push_back(xn);
        normals.push_back(0);
        normals.push_back(zn);
        textures.push_back(tx);
        textures.push_back(1);
        vertices.push_back(x+x2);
        vertices.push_back(y + height);
        vertices.push_back(z+z2);

        const float x3 = x2;
        x2 = c * x2 - s * z2;
        z2 = s * x3 + c * z2;
    }
}
