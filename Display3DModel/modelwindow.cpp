#include "modelwindow.h"

ModelWindow::ModelWindow(QString filepath, ModelLoader::PathType pathType, QString texturePath) :
    OpenGLWindow()
  , m_indexBuffer(QOpenGLBuffer::IndexBuffer)
  , m_filepath(filepath)
  , m_pathType(pathType)
  , m_texturePath(texturePath)
  , m_error(false)
{
    model_position = new ModelPosition();
}

void ModelWindow::mouseMoveEvent(QMouseEvent *ev)
{
    camera->MouseMove(ev);
    model_position->MouseMove(ev);
}

void ModelWindow::mousePressEvent(QMouseEvent *ev)
{
    camera->MousePressed(ev);
    model_position->MousePressed(ev);
}

void ModelWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    camera->MouseReleased(ev);
    model_position->MouseReleased(ev);
}

void ModelWindow::wheelEvent(QWheelEvent *ev)
{
    camera->WheelEvent(ev);
}

void ModelWindow::LoadModel(QString filepath, ModelLoader::PathType pathType, QString texturePath)
{
    m_filepath = filepath;
    m_pathType = pathType;
    m_texturePath = texturePath;
    loadModel();
}

QVector3D ModelWindow::GetObjectCenter()
{
    return object_center;
}

void ModelWindow::loadModel()
{
    if(!m_error)
    {
        m_vertexBuffer.destroy();
        m_normalBuffer.destroy();
        m_textureUVBuffer.destroy();
        m_indexBuffer.destroy();
        m_vao.destroy();
    }
    m_error = false;
    createBuffers();
    if(m_error)
        return;
    createAttributes();
    if(camera != 0)
        delete camera;
    camera = new Camera(object_center, model.distance);
    model_position->SetCamera(camera);
}

void ModelWindow::initializeGL()
{
    this->initializeOpenGLFunctions();

    createShaderProgram(":/ads_fragment.vert", ":/ads_fragment.frag");

    loadModel();
    setupLightingAndMatrices();

    glEnable(GL_DEPTH_TEST);
    glClearColor(BACKGROUND_COLOR);
}

void ModelWindow::createShaderProgram(QString vShader, QString fShader)
{
    // Compile vertex shader
    if ( !m_error && !m_shaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex, vShader.toUtf8() ) ) {
        qDebug() << "Error in vertex shader:" << m_shaderProgram.log();
        m_error = true;
    }

    // Compile fragment shader
    if ( !m_error && !m_shaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment, fShader.toUtf8() ) ) {
        qDebug() << "Error in fragment shader:" << m_shaderProgram.log();
        m_error = true;
    }

    // Link the shaders together into a program
    if ( !m_error && !m_shaderProgram.link() ) {
        qDebug() << "Error linking shader program:" << m_shaderProgram.log();
        m_error = true;
    }
}

void ModelWindow::createBuffers()
{
    if(m_error)
        return;

    model = ModelLoader();

    if(!model.Load(m_filepath, m_pathType))
    {
        m_error = true;
        return;
    }

    QVector<float> *vertices;
    QVector<float> *normals;
    QVector<QVector<float> > *textureUV;
    QVector<unsigned int> *indices;

    model.getBufferData(&vertices, &normals, &indices);
    model.getTextureData(&textureUV, 0, 0);

    auto v_vector = FloatVectorToQVector3D(*vertices);
    CalculateCenter(v_vector);

    // Create a vertex array object
    m_vao.create();
    m_vao.bind();

    // Create a buffer and copy the vertex data to it
    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate( &(*vertices)[0], vertices->size() * sizeof( float ) );

    // Create a buffer and copy the normals data to it
    m_normalBuffer.create();
    m_normalBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_normalBuffer.bind();
    m_normalBuffer.allocate( &(*normals)[0], normals->size() * sizeof( float ) );

    if(textureUV != 0 && textureUV->size() != 0)
    {
        // Create a buffer and copy the texture data to it
        m_textureUVBuffer.create();
        m_textureUVBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
        m_textureUVBuffer.bind();
        int texSize = 0;
        for(int ii=0; ii<textureUV->size(); ++ii)
            texSize += textureUV->at(ii).size();

        m_textureUVBuffer.allocate( &(*textureUV)[0][0], texSize * sizeof( float ) );
    }

    // Create a buffer and copy the index data to it
    m_indexBuffer.create();
    m_indexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_indexBuffer.bind();
    m_indexBuffer.allocate( &(*indices)[0], indices->size() * sizeof( unsigned int ) );

    m_rootNode = model.getNodeData();
}

void ModelWindow::createAttributes()
{
    if(m_error)
        return;

    m_vao.bind();
    // Set up the vertex array state
    m_shaderProgram.bind();

    // Map vertex data to the vertex shader's layout location '0'
    m_vertexBuffer.bind();
    m_shaderProgram.enableAttributeArray( 0 );      // layout location
    m_shaderProgram.setAttributeBuffer( 0,          // layout location
                                        GL_FLOAT,   // data's type
                                        0,          // Offset to data in buffer
                                        3);         // number of components (3 for x,y,z)

    // Map normal data to the vertex shader's layout location '1'
    m_normalBuffer.bind();
    m_shaderProgram.enableAttributeArray( 1 );      // layout location
    m_shaderProgram.setAttributeBuffer( 1,          // layout location
                                        GL_FLOAT,   // data's type
                                        0,          // Offset to data in buffer
                                        3);         // number of components (3 for x,y,z)

    if(m_textureUVBuffer.isCreated()) {
        m_textureUVBuffer.bind();
        m_shaderProgram.enableAttributeArray( 2 );      // layout location
        m_shaderProgram.setAttributeBuffer( 2,          // layout location
                                            GL_FLOAT,   // data's type
                                            0,          // Offset to data in buffer
                                            2);         // number of components (2 for u,v)
    }

}

void ModelWindow::setupLightingAndMatrices()
{
    float aspect = 4.0f/3.0f;
    m_projection.setToIdentity();
    m_projection.perspective(
                60.0f,          // field of vision
                aspect,         // aspect ratio
                0.3f,           // near clipping plane
                1000.0f);       // far clipping plane

    m_lightInfo.Position = QVector4D( -1.0f, 1.0f, 1.0f, 1.0f );
    m_lightInfo.Intensity = QVector3D( 1.0f, 1.0f, 1.0f);

    m_materialInfo.Ambient = QVector3D( 0.05f, 0.2f, 0.05f );
    m_materialInfo.Diffuse = QVector3D( 0.3f, 0.5f, 0.3f );
    m_materialInfo.Specular = QVector3D( 0.6f, 0.6f, 0.6f );
    m_materialInfo.Shininess = 50.0f;
}

void ModelWindow::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, h );

    m_projection.setToIdentity();
    m_projection.perspective(60.0f, (float)w/h, .3f, 1000);
}

void ModelWindow::paintGL()
{
    if(m_error)
        return;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind shader program
    m_shaderProgram.bind();

    // Set shader uniforms for light information
    m_shaderProgram.setUniformValue( "lightPosition", m_lightInfo.Position );
    m_shaderProgram.setUniformValue( "lightIntensity", m_lightInfo.Intensity );

    // Bind VAO and draw everything
    m_vao.bind();
    drawNode(m_rootNode.data(), QMatrix4x4());
    m_vao.release();
}

void ModelWindow::drawNode(const Node *node, QMatrix4x4 objectMatrix)
{
    // Prepare matrices
    //objectMatrix if for fitting object onto the screen
    //objectMatrix *= node->transformation;
    QMatrix4x4 modelMatrix = model_position->GetModelMatrix() * objectMatrix;
    QMatrix4x4 viewMatrix = camera->GetViewMatrix();
    QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;
    QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();
    QMatrix4x4 mvp = m_projection * modelViewMatrix;

    m_shaderProgram.setUniformValue( "MV", modelViewMatrix );// Transforming to eye space
    m_shaderProgram.setUniformValue( "N", normalMatrix );    // Transform normal to Eye space
    m_shaderProgram.setUniformValue( "MVP", mvp );           // Matrix for transforming to Clip space

    // Draw each mesh in this node
    for(int imm = 0; imm<node->meshes.size(); ++imm)
    {
        if(node->meshes[imm]->material->Name == QString("DefaultMaterial"))
            setMaterialUniforms(m_materialInfo);
        else
            setMaterialUniforms(*node->meshes[imm]->material);

        glDrawElements( GL_TRIANGLES, node->meshes[imm]->indexCount, GL_UNSIGNED_INT
                            , (const void*)(node->meshes[imm]->indexOffset * sizeof(unsigned int)) );
    }

    // Recursively draw this nodes children nodes
    for(int inn = 0; inn<node->nodes.size(); ++inn)
        drawNode(&node->nodes[inn], objectMatrix);
}

void ModelWindow::setMaterialUniforms(MaterialInfo &mater)
{
    m_shaderProgram.setUniformValue( "Ka", mater.Ambient );
    m_shaderProgram.setUniformValue( "Kd", mater.Diffuse );
    m_shaderProgram.setUniformValue( "Ks", mater.Specular );
    m_shaderProgram.setUniformValue( "shininess", mater.Shininess );
}

QVector<QVector3D> ModelWindow::FloatVectorToQVector3D(QVector<float> f_vector)
{
    QVector<QVector3D> v_vector;
    for(int i = 0 ; i < f_vector.length(); i+=3)
    {
        QVector3D vector3d(f_vector[i], f_vector[i+1], f_vector[i+2]);
        v_vector.append(vector3d);
    }
    return v_vector;
}

void ModelWindow::CalculateCenter(QVector<QVector3D> v_vector)
{
    QVector3D sum;
    for(int i = 0 ; i < v_vector.length(); i++)
    {
        auto v = v_vector[i];
        sum.setX(sum.x() + v.x());
        sum.setY(sum.y() + v.y());
        sum.setZ(sum.z() + v.z());
    }
    object_center = sum / v_vector.length();
    qDebug() << "object_center: " << object_center.x() << "," << object_center.y() << "," << object_center.z();
}

void ModelWindow::cleanupGL()
{
}
