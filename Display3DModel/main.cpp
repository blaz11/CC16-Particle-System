#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QMainWindow>
#include "openglwindow.h"
#include "modelwindow.h"
#include "uiconnector.h"

class UIConnector;

QString OpenGL_Model("/Handgun_Obj/Handgun_obj.obj");

QOpenGLContext *createOpenGLContext(int major, int minor) {
    QSurfaceFormat requestedFormat;
    requestedFormat.setDepthBufferSize( 24 );
    requestedFormat.setMajorVersion( major );
    requestedFormat.setMinorVersion( minor );

    requestedFormat.setSamples( 4 );
    requestedFormat.setProfile( QSurfaceFormat::CoreProfile );

    QOpenGLContext *context = new QOpenGLContext;
    context->setFormat( requestedFormat );
    context->create();

    // If unable to create 3.3 context return 0
    if(context->format().version() != qMakePair(major,minor)) {
        context->deleteLater();
        context = 0;
    }
    return context;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QOpenGLContext *context = createOpenGLContext(3, 3);

    if (!context)
        return 1;

    QPair<int, int> glVersion = context->format().version();

    ModelWindow *modelWindow = 0;

    qDebug() << "OpenGL Version:" << glVersion;

    if (glVersion == qMakePair(3,3)) {
        modelWindow = new ModelWindow(OpenGL_Model, ModelLoader::RelativePath);
    }
    else
        return -1;

    modelWindow->initializeWindow(context, 40);
    UIConnector uiConnector;
    uiConnector.model_window = modelWindow;
    QWidget* container = QWidget::createWindowContainer(modelWindow);
    container->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    QPushButton* selectModelButton = new QPushButton();

    selectModelButton->setFixedSize(200,50);
    selectModelButton->setText(QString("Load model"));
    QPushButton* resetPositionButton = new QPushButton();
    resetPositionButton->setFixedSize(200,50);
    resetPositionButton->setText(QString("Reset position"));
    QObject::connect(selectModelButton, SIGNAL (pressed()),&uiConnector, SLOT (handleLoadModelButtonClick()));
    QObject::connect(resetPositionButton, SIGNAL (pressed()),&uiConnector, SLOT (handlePositionResetClick()));
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(container, 0, 0, 3, 2);
    layout->addWidget(selectModelButton, 1, 1);
    layout->addWidget(resetPositionButton, 2, 1);

    QWidget* central = new QWidget();
    QMainWindow* mainWindow = new QMainWindow();
    mainWindow->setCentralWidget(central);
    mainWindow->centralWidget()->setLayout(layout);
    mainWindow->setFixedSize(1050,600);

    mainWindow->show();

    return a.exec();
}
