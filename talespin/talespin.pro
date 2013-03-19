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
    draw.cpp \
    BarChart.cpp \
    VisualizationManager.cpp \
    Visualization.cpp \
    Bar.cpp \
    Circles.cpp \
    Circle.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    Particle.h \
    draw.h \
    BarChart.h \
    VisualizationManager.h \
    Visualization.h \
    Bar.h \
    Circles.h \
    Circle.h

INCLUDEPATH += ./glm

FORMS    += mainwindow.ui
