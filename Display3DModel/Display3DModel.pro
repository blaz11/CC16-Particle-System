#-------------------------------------------------
#
# Project created by QtCreator 2013-08-29T00:18:56
#
#-------------------------------------------------

QT       += core gui
CONFIG      += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

lessThan(QT_MAJOR_VERSION, 5): error(This project requires Qt 5 or later)

TARGET = Display3DModel
TEMPLATE = app


SOURCES += main.cpp\
    modelloader.cpp \
    openglwindow.cpp \
    camera.cpp \
    modelposition.cpp \
    resources.cpp \
    uiconnector.cpp \
    modelwindow.cpp

HEADERS  += \
    modelloader.h \
    openglwindow.h \
    camera.h \
    resources.h \
    modelposition.h \
    uiconnector.h \
    modelwindow.h


OTHER_FILES += ads_fragment.vert ads_fragment.frag

RESOURCES += \
    resources.qrc

INCLUDEPATH += $$PWD/Assimp/include
DEPENDPATH += $$PWD/Assimp/include

unix:!macx: LIBS += -L$$PWD/Assimp\Linux/usr/lib/ -lassimp
win32: LIBS += -L$$PWD/Assimp/Windows/ -lassimp
