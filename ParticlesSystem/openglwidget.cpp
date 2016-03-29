#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

OpenGLWidget::~OpenGLWidget()
{
    delete camera;
    delete shader;
}

void OpenGLWidget::addObjectToScene(DrawableObject *object)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    object->initialize(f);
    objects.push_back(object);
}

void OpenGLWidget::removeObjectFromScene(DrawableObject *object)
{
    auto iterator = std::find(objects.begin(), objects.end(), object);
    objects.erase(iterator);
}

void OpenGLWidget::initializeGL()
{
    auto pipeObject = new PipeObject();
    addObjectToScene(pipeObject);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    camera = new Camera();
    shader = new Shader("C:\\Users\\Barbara\\Documents\\ParticlesSystem\\vertex_shader.glsl",
                        "C:\\Users\\Barbara\\Documents\\ParticlesSystem\\fragment_shader.glsl", f);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    qDebug() << "Initialized";
}

void OpenGLWidget::resizeGL(int w, int h)
{
    qDebug() << "Resizing";
    // Update projection matrix and other size related settings:
}

void OpenGLWidget::paintGL()
{
    qDebug() << "Painting";
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    shader->use(f);
    auto viewMatrix = camera->GetViewMatrix();
    f->glClear(GL_COLOR_BUFFER_BIT);
    for (auto i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->draw(f, shader, viewMatrix);
    }
}
