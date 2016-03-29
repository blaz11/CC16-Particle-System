#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif // GLWIDGET_H
