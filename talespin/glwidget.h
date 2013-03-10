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
    void paintEvent(QPaintEvent *event);

    void showEvent(QShowEvent *event);

    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );

    int scene_zoom;
    int mouse_state;
    int mouse_x, mouse_y;

private:
void createObjects(int number);
QList<Draw*> objects;

signals:

public slots:
    void particleSize(int value);
    void setNumberOfParticles(int value);
    
};

#endif // GLWIDGET_H
