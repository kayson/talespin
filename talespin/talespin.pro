 #-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T13:45:00
#
#-------------------------------------------------

QT       += core gui opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = talespin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    ParticleManager.cpp \
    ParticleContainer.cpp \
    drawgrid.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    Particle.h \
    ParticleManager.h \
    ParticleContainer.h \
    drawgrid.h

INCLUDEPATH += ./glm ./ftgl/2.1.3-rc5/include ./freetype/2.4.10/include/freetype2 ./freetype/2.4.10/include/

FORMS    += mainwindow.ui

win32 {
    LIBS += -lfreetype2411 -lftgl
}

RESOURCES += \
    MyResources.qrc


