#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "ParticleManager.h"

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

    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );



    int scene_zoom;
    int mouse_state;
    int mouse_x, mouse_y;

signals:

public slots:
    void particleSize(int value);
    void setNumberOfParticles(int value);
    
};

#endif // GLWIDGET_H
