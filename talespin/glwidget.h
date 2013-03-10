#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "ParticleManager.h"
#include "draw.h"

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

    void showEvent(QShowEvent *event);

    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void wheelEvent( QWheelEvent * event );

    float scene_zoom, scene_zoom_dx, mouse_pan_dx, mouse_pan_dy, scene_pan_x, scene_pan_y;
    float camera_friction;
    int mouse_state;
    int mouse_x, mouse_y;

private:
void createObjects(int number);
QList<Draw*> objects;

signals:

public slots:
    void particleSize(int value);
    void setNumberOfParticles(int value);
    void setSpacing(int value);
};

#endif // GLWIDGET_H
