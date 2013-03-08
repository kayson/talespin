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
    ParticleContainer.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    ParticleManager.h \
    ParticleContainer.h \
    Particle.h

INCLUDEPATH += ./glm

FORMS    += mainwindow.ui
