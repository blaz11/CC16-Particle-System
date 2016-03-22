#ifndef MODELWINDOW_GL_2_H
#define MODELWINDOW_GL_2_H

#include <string>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include "modelloader.h"
#include "openglwindow.h"

// OpenGL 2.1/OpenGL ES -- Inherit from QOpenGLFunctions to get OpenGL 2.1/OpenGL ES 2.0 functions
class ModelWindow_GL_2 : public QOpenGLFunctions, public OpenGLWindow
{
public:
    ModelWindow_GL_2(QString filepath, ModelLoader::PathType pathType, QString texturePath="");

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void cleanupGL();

private:
    void createShaderProgram( QString vShader, QString fShader);
    void createBuffers();
    void createAttributes();
    void setupLightingAndMatrices();

    void draw();
    void drawNode(const Node *node, QMatrix4x4 objectMatrix);
    void setMaterialUniforms(MaterialInfo &mater);

    QOpenGLShaderProgram m_shaderProgram;

    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_normalBuffer;
    QOpenGLBuffer m_textureUVBuffer;
    QOpenGLBuffer m_indexBuffer;

    QSharedPointer<Node> m_rootNode;

    QMatrix4x4 m_projection, m_view, m_model;

    QString m_filepath;
    ModelLoader::PathType m_pathType;
    QString m_texturePath;

    LightInfo m_lightInfo;
    MaterialInfo m_materialInfo;

    bool m_error;
};

#endif // MODELWINDOW_GL_2_H
