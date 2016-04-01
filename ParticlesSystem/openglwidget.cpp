#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), system(25)
{
    isMoving = false;
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
    shader = new Shader("../ParticlesSystem/vertex_shader.glsl",
                        "../ParticlesSystem/fragment_shader.glsl", f);
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

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    const float sensitivity = 0.01f;
    if(camera == NULL)
        return;
    system.update(1);
    auto test = system.getParticlePositions();
    qDebug() << "Particle count: " << test.size();
    switch(event->key())
    {
        case Qt::Key_Up:
            camera->ProcessKeyboard(FORWARD, sensitivity);
            this->update();
            break;
        case Qt::Key_Down:
            camera->ProcessKeyboard(BACKWARD, sensitivity);
            this->update();
            break;
        case Qt::Key_Right:
            camera->ProcessKeyboard(RIGHT, sensitivity);
            this->update();
            break;
        case Qt::Key_Left:
            camera->ProcessKeyboard(LEFT, sensitivity);
            this->update();
            break;
    }

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!isMoving)
        return;
    auto dx = lastPosition.x() - event->pos().x();
    auto dy = lastPosition.y() - event->pos().y();
    lastPosition = event->pos();
    camera->ProcessMouseMovement(dx, dy);
    this->update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
   isMoving = true;
   lastPosition = event->pos();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isMoving = false;
}
