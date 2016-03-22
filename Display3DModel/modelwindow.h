#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include "modelloader.h"
#include "openglwindow.h"
#include "camera.h"
#include "modelposition.h"
#include "resources.h"

class Camera;
class ModelPosition;

class ModelWindow : public QOpenGLFunctions_3_3_Core, public OpenGLWindow
{
public:
    ModelWindow(QString filepath, ModelLoader::PathType pathType, QString texturePath="");

    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void wheelEvent(QWheelEvent* ev);

    void LoadModel(QString filepath, ModelLoader::PathType pathType, QString texturePath="");
    QVector3D GetObjectCenter();
    ModelPosition* model_position;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void cleanupGL();

private:
    void loadModel();
    void createShaderProgram( QString vShader, QString fShader);
    void createBuffers();
    void createAttributes();
    void setupLightingAndMatrices();

    void draw();
    void drawNode(const Node *node, QMatrix4x4 objectMatrix);
    void setMaterialUniforms(MaterialInfo &mater);

    QVector<QVector3D> FloatVectorToQVector3D(QVector<float> f_vector);
    void CalculateCenter(QVector<QVector3D> v_vector);

    QOpenGLShaderProgram m_shaderProgram;

    QOpenGLVertexArrayObject m_vao;

    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_normalBuffer;
    QOpenGLBuffer m_textureUVBuffer;
    QOpenGLBuffer m_indexBuffer;

    QSharedPointer<Node> m_rootNode;

    QMatrix4x4 m_projection;

    QString m_filepath;
    ModelLoader::PathType m_pathType;
    QString m_texturePath;

    LightInfo m_lightInfo;
    MaterialInfo m_materialInfo;
    ModelLoader model;

    bool m_error;
    QVector3D object_center;
    Camera* camera;
};

#endif // MODELWINDOW_H
