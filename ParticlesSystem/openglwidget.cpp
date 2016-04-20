#include "openglwidget.h"
#include "mainwindow.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), system(500000, (MainWindow*)(this->parentWidget()->parentWidget()))
{
    MainWindow* t = (MainWindow*)(this->parentWidget()->parentWidget());
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
    auto pipeObject1 = new PipeObject(M_PI / 4, 15, glm::vec3(0, 10, 0));
    addObjectToScene(pipeObject1);
    auto pipeObject2 = new PipeObject(3 * M_PI / 4, 20, glm::vec3(0, 30, 5));
    addObjectToScene(pipeObject2);
    auto particleRenderer = new ParticleSystemRender(&system);
    addObjectToScene(particleRenderer);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    camera = new Camera(glm::vec3(0,0,0), 75);
    shader = new Shader("../ParticlesSystem/vertex_shader.glsl",
                        "../ParticlesSystem/fragment_shader.glsl", f);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    qDebug() << "GL: Initialized";
}

void OpenGLWidget::resizeGL(int w, int h)
{
    qDebug() << "GL: Resizing";
    // Update projection matrix and other size related settings:
}

void OpenGLWidget::paintGL()
{
    qDebug() << "GL: Painting";
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
    system.update(1);
#ifdef NO_CHANCE_THAT_THIS_SYMBOL_WILL_EVER_EXIST
    auto test = system.getParticlePositions();
    qDebug() << "Particle count: " << test.size();
    for(auto i : test)
    {
        qDebug() << i.x << ", " << i.y << ", " << i.z;
    }
#endif
    this->update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    camera->WheelEvent(event);
    this->update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(camera->MouseMove(event))
        this->update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    camera->MousePressed(event);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    camera->MouseReleased(event);
}
