#ifndef OPENGLSURFACE_H
#define OPENGLSURFACE_H

#include <QSurface>

class OpenGLSurface : public QSurface
{
    Q_OBJECT

public:
    OpenGLSurface();
    ~OpenGLSurface();
    void initializeSurface(QOpenGLContext *glContext, int refreshRate);

protected:
    virtual void initializeGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    virtual void paintGL() = 0;
    virtual void cleanupGL() = 0;

private slots:
    void _initializeGL();
    void _resizeGL();
    void _paintGL();
    void _cleanupGL();

private:
    QOpenGLContext* m_context;
    QTimer *m_timer;
};

#endif // OPENGLSURFACE_H
