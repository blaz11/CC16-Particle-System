#include "openglsurface.h"

OpenGLSurface::OpenGLSurface() :
    QSurface(OpenGLSurface)
    , m_context(0)
    , m_timer(0)
{

}

OpenGLSurface::~OpenGLSurface()
{

}


void OpenGLSurface::initializeSurface(QOpenGLContext *glContext, int refreshRate)
{

    if (m_context) {
        qDebug() << "Window has already been initialized";
        return;
    }

    m_context = glContext;

    //setSurfaceType(OpenGLSurface);
    setFormat( m_context->format() );
    resize( 800, 600 );
    create();

    //connect( this, SIGNAL( widthChanged( int ) ), this, SLOT( _resizeGL() ) );
    //connect( this, SIGNAL( heightChanged( int ) ), this, SLOT( _resizeGL() ) );
    //connect( m_context, SIGNAL(aboutToBeDestroyed()), this, SLOT(_cleanupGL()), Qt::DirectConnection );

    _initializeGL();
    _resizeGL();

    m_timer = new QTimer;
    m_timer->setInterval(refreshRate);
    connect(m_timer, &QTimer::timeout, this, &OpenGLWindow::_paintGL);
    m_timer->start();
}

void OpenGLSurface::_initializeGL()
{
    m_context->makeCurrent( this );

    this->initializeGL();
}

void OpenGLSurface::_paintGL()
{
    if(!isExposed())
        return;

    m_context->makeCurrent( this );

    this->paintGL();

    m_context->swapBuffers( this );
}

void OpenGLSurface::_resizeGL()
{
    m_context->makeCurrent( this );

    this->resizeGL( width(), height() );
    _paintGL();
}

void OpenGLSurface::_cleanupGL()
{
    m_context->makeCurrent( this );

    this->cleanupGL();
}
