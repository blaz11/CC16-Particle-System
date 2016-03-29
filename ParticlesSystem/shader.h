#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QOpenGLFunctions>
#include <Qdebug>

class Shader
{
public:
    // The program ID
    GLuint Program;
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, QOpenGLFunctions *f);
    // Use the program
    void use(QOpenGLFunctions *f);


};

#endif
