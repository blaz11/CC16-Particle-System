#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, QOpenGLFunctions *f)
 {
     // 1. Retrieve the vertex/fragment source code from filePath
     std::string vertexCode;
     std::string fragmentCode;
     std::ifstream vShaderFile;
     std::ifstream fShaderFile;
     // ensures ifstream objects can throw exceptions:
     vShaderFile.exceptions (std::ifstream::badbit);
     fShaderFile.exceptions (std::ifstream::badbit);
     try
     {
         // Open files
         vShaderFile.open(vertexPath);
         fShaderFile.open(fragmentPath);
         std::stringstream vShaderStream, fShaderStream;
         // Read file's buffer contents into streams
         vShaderStream << vShaderFile.rdbuf();
         fShaderStream << fShaderFile.rdbuf();
         // close file handlers
         vShaderFile.close();
         fShaderFile.close();
         // Convert stream into string
         vertexCode = vShaderStream.str();
         fragmentCode = fShaderStream.str();
     }
     catch (std::ifstream::failure e)
     {
         qDebug() << ("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
     }
     const GLchar* vShaderCode = vertexCode.c_str();
     const GLchar * fShaderCode = fragmentCode.c_str();
     // 2. Compile shaders
     GLuint vertex, fragment;
     GLint success;
     GLchar infoLog[512];
     // Vertex Shader
     vertex = f->glCreateShader(GL_VERTEX_SHADER);
     f->glShaderSource(vertex, 1, &vShaderCode, NULL);
     f->glCompileShader(vertex);
     // Print compile errors if any
     f->glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
     if (!success)
     {
         f->glGetShaderInfoLog(vertex, 512, NULL, infoLog);
         qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
         qDebug() << infoLog;
     }
     // Fragment Shader
     fragment = f->glCreateShader(GL_FRAGMENT_SHADER);
     f->glShaderSource(fragment, 1, &fShaderCode, NULL);
     f->glCompileShader(fragment);
     // Print compile errors if any
     f->glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
     if (!success)
     {
         f->glGetShaderInfoLog(fragment, 512, NULL, infoLog);
         qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
         qDebug() << infoLog;
     }
     // Shader Program
     this->Program = f->glCreateProgram();
     f->glAttachShader(this->Program, vertex);
     f->glAttachShader(this->Program, fragment);
     f->glLinkProgram(this->Program);
     // Print linking errors if any
     f->glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
     if (!success)
     {
         f->glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
         qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED";
         qDebug() << infoLog;
     }
     // Delete the shaders as they're linked into our program now and no longer necessery
     f->glDeleteShader(vertex);
     f->glDeleteShader(fragment);
 }

 void Shader::use(QOpenGLFunctions *f)
 {
     f->glUseProgram(this->Program);
 }
