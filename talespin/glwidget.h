#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "ParticleManager.h"

#include <string>
#include <iostream>


class glwidget : public QGLWidget
{
    Q_OBJECT
public:
    glwidget(QWidget *parent = 0);
    ~glwidget();

    ParticleManager* ParticleMgr;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void timerEvent(QTimerEvent *event);
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void wheelEvent( QWheelEvent * event );

    void drawGrid();
    void drawBarText();

    void saveSettings();
    void loadSettings();

    QBasicTimer timer;
    float scene_zoom, scene_zoom_dx, mouse_pan_dx, mouse_pan_dy, scene_pan_x, scene_pan_y;
    float camera_friction;
    int mouse_state;
    int mouse_x, mouse_y;

private:

signals:

public slots:
    void particleSize(int value);
    void setNumberOfParticles(int value);
    void setSpacing(int value);
    void clearMgr();
};

#endif // GLWIDGET_H
