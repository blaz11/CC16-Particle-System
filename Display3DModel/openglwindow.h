#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLContext>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QWindow>

class QScreen;
class QTimer;
class QOpenGLContext;

class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    OpenGLWindow( QScreen* screen = 0 );
    ~OpenGLWindow();

    void initializeWindow(QOpenGLContext *glContext, int refreshRate);

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

#endif // OPENGLWINDOW_H
