#include "particlesystemrender.h"

ParticleSystemRender::ParticleSystemRender(ParticleSystem* sys)
{
    system = sys;
}


void ParticleSystemRender::initialize(QOpenGLFunctions *f)
{
    int p = 0;
    GLfloat i, j, step, mirror, x, y, z, length;
    projection = glm::perspective(45.0f, 2.0f, 0.01f, 250.0f);
//    vector<GLfloat> positions, normals, textures;
//    positions.push_back(0.0f);
//    positions.push_back(0.0f);
//    positions.push_back(0.0f);
    const GLfloat part = 8;
    const int verticesCount = part*part*36*3;
    step = (GLfloat)2 / part;
    numberOfVertices = part * part * 36 * 3;
    GLfloat vertices[192*36];

    for(mirror = -1; mirror <= 1; mirror+=2)
        for(i = -1; i < 1; i+=step)
            for(j = -1; j < 1; j+=step)
            {
                //left right
                vertices[p++] = i;
                vertices[p++] = j;
                vertices[p++] = mirror;

                vertices[p++] = i + step;
                vertices[p++] = j;
                vertices[p++] = mirror;

                vertices[p++] = i;
                vertices[p++] = j + step;
                vertices[p++] = mirror;


                vertices[p++] = i + step;
                vertices[p++] = j;
                vertices[p++] = mirror;

                vertices[p++] = i;
                vertices[p++] = j + step;
                vertices[p++] = mirror;

                vertices[p++] = i + step;
                vertices[p++] = j + step;
                vertices[p++] = mirror;

                //top bottom
                vertices[p++] = i;
                vertices[p++] = mirror;
                vertices[p++] = j;

                vertices[p++] = i + step;
                vertices[p++] = mirror;
                vertices[p++] = j;

                vertices[p++] = i;
                vertices[p++] = mirror;
                vertices[p++] = j + step;


                vertices[p++] = i + step;
                vertices[p++] = mirror;
                vertices[p++] = j;

                vertices[p++] = i;
                vertices[p++] = mirror;
                vertices[p++] = j + step;

                vertices[p++] = i + step;
                vertices[p++] = mirror;
                vertices[p++] = j + step;

                //front back
                vertices[p++] = mirror;
                vertices[p++] = i;
                vertices[p++] = j;

                vertices[p++] = mirror;
                vertices[p++] = i + step;
                vertices[p++] = j;

                vertices[p++] = mirror;
                vertices[p++] = i;
                vertices[p++] = j + step;


                vertices[p++] = mirror;
                vertices[p++] = i + step;
                vertices[p++] = j;

                vertices[p++] = mirror;
                vertices[p++] = i;
                vertices[p++] = j + step;

                vertices[p++] = mirror;
                vertices[p++] = i + step;
                vertices[p++] = j + step;
            }

    for(p = 0; p < numberOfVertices; p += 3)
    {
        x = vertices[p];
        y = vertices[p + 1];
        z = vertices[p + 2];
        length = (GLfloat)sqrt((GLfloat)(x*x + y*y + z*z));
        if(length > 0)
        {
            vertices[p] = x/length;
            vertices[p+1] = y/length;
            vertices[p+2] = z/length;
        }
    }

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
    f->glUniform3f(colorLoc, 0.0f, 0.0f, 1.0f);
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
