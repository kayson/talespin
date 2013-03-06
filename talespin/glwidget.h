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
    explicit glwidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void keyPressEvent( QKeyEvent *k );

    int scene_zoom;
    int mouse_state;
    int mouse_x, mouse_y;

    ParticleManager* ParticleMgr;
signals:

public slots:
    void addBar(int particles);
    void setNumberOfParticles(int value);
    
};

#endif // GLWIDGET_H
