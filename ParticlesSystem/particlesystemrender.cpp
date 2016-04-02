#include "particlesystemrender.h"

ParticleSystemRender::ParticleSystemRender(ParticleSystem* sys)
{
    system = sys;
}


void ParticleSystemRender::initialize(QOpenGLFunctions *f)
{
    projection = glm::perspective(45.0f, 2.0f, 0.01f, 100.0f);
//    vector<GLfloat> positions, normals, textures;
//    positions.push_back(0.0f);
//    positions.push_back(0.0f);
//    positions.push_back(0.0f);
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    numberOfVertices = 36;
    GLuint VBO;
    vao.create();
    f->glGenBuffers(1, &VBO);
    vao.bind();
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   // f->glBufferData(GL_ARRAY_BUFFER, positions.size(), positions.data(), GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    f->glEnableVertexAttribArray(0);
    vao.release();
}

void ParticleSystemRender::draw(QOpenGLFunctions *f, Shader *shader, glm::mat4 view)
{
    auto particlesPositions = system->getParticlePositions();
    shader->use(f);
    vao.bind();
    GLint modelLoc = f->glGetUniformLocation(shader->Program, "model");
    GLint viewLoc = f->glGetUniformLocation(shader->Program, "view");
    GLint projLoc = f->glGetUniformLocation(shader->Program, "projection");
    GLint colorLoc = f->glGetUniformLocation(shader->Program, "color");
    f->glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    f->glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    f->glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
    qDebug() << particlesPositions.size();
    for(auto i : particlesPositions)
    {
        glm::mat4 model;
        model = glm::translate(model, i);
        f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        f->glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
        //qDebug() << i.x << ", " << i.y << ", " << i.z;
    }
    vao.release();
}

void ParticleSystemRender::update()
{
}
