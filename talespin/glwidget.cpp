#include "glwidget.h"

#if defined __APPLE__
#include "GLUT/glut.h"
#elif defined _WIN32 || defined _WIN64 || __unix__
#include "GL/glut.h"
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


glwidget::glwidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    scene_zoom = -100;
    scene_zoom_dx = 0;
    scene_pan_x = -150;
    scene_pan_y = -90;
    mouse_pan_dx = 0;
    mouse_pan_dy = 0;
    mouse_state = -1;
    camera_friction = 0.998f;

    ParticleMgr = new ParticleManager();
    ParticleMgr->radius = 1.0f;
    ParticleMgr->columns = 10;
    ParticleMgr->spacing = 0;

    ParticleMgr->clearAllContainers();
    ParticleMgr->AddParticleContainer(1000, glm::vec4(1.0f,0.5f,1.0f,1.0f));
    ParticleMgr->AddParticleContainer(1250, glm::vec4(1.0f,0.5f,0.0f,1.0f));
    ParticleMgr->AddParticleContainer(1060, glm::vec4(0.0f,1.0f,0.5f,1.0f));
    ParticleMgr->update();
}

glwidget::~glwidget()
{
    makeCurrent();
    ParticleMgr->clearAllContainers();
}

void glwidget::initializeGL()
{

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_POINT_SMOOTH );

}

void glwidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90.f, // FOV
                    (GLfloat) width / (GLfloat) height, // Aspect Ratio
                    1.0f, // Z-Clipping Near
                    1000.0f); // Z-Clipping Far
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void glwidget::paintEvent(QPaintEvent *event)
{

    scene_pan_x -= mouse_pan_dx / 1000.0f;
    scene_pan_y += mouse_pan_dy / 1000.0f;
    mouse_pan_dx *= camera_friction;
    mouse_pan_dy *= camera_friction;

    qreal sc = powf(1.1, scene_zoom_dx);
    scene_zoom_dx *= camera_friction;
    scene_zoom /= sc;

    if( scene_pan_x > -190 * (scene_zoom / -100) ){ scene_pan_x = -190 * (scene_zoom / -100) ; }
    if( scene_pan_y > -90 * (scene_zoom / -100) ){ scene_pan_y = -90 * (scene_zoom / -100) ; }
    if( scene_zoom < -300 ){ scene_zoom = -300; }
    if( scene_zoom > -10 ){ scene_zoom = -10; }

    makeCurrent();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(scene_pan_x, scene_pan_y, scene_zoom);
    ParticleMgr->updateContainers();
    ParticleMgr->drawContainers();
    update();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    foreach (Draw *draw, objects)
    {
         draw->drawObject(&painter); //ritar ut objekten
    }
    painter.end();

}

void glwidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    createObjects(1);
}

void glwidget::createObjects(int number)
{
    for (int i = 0; i < number; ++i) {
        QPointF position(10,20);
        objects.append(new Draw(position));
    }
}

void glwidget::mousePressEvent ( QMouseEvent * event )
{
  mouse_state = event->button();
  mouse_x = event->x();
  mouse_y = event->y();
}

void glwidget::mouseReleaseEvent ( QMouseEvent * event )
{
  mouse_state = -1;
}

void glwidget::mouseMoveEvent ( QMouseEvent * event )
{

  switch(mouse_state){
  case 1:
    int dx_limit = 200 * ( scene_zoom / -200 );
    mouse_pan_dx += (mouse_x - event->x());
    mouse_pan_dy += (mouse_y - event->y());
    mouse_x = event->x();
    mouse_y = event->y();
    if(mouse_pan_dx > dx_limit)
        mouse_pan_dx = dx_limit;
    if(mouse_pan_dy > dx_limit)
        mouse_pan_dy = dx_limit;
    if(mouse_pan_dx < -dx_limit)
        mouse_pan_dx = -dx_limit;
    if(mouse_pan_dy < -dx_limit)
        mouse_pan_dy = -dx_limit;

    break;
  }
}

void glwidget::wheelEvent( QWheelEvent * event )
{
    int numSteps = event->delta() / 120;
    if (numSteps == 0)
    {
        event->ignore();
        return;
    }

    scene_zoom_dx += numSteps * 0.005f;

    event->accept();
}

void glwidget::particleSize(int value)
{
   ParticleMgr->radius = value;
   ParticleMgr->update();
   updateGL();
}

void glwidget::setNumberOfParticles(int value)
{
    ParticleMgr->columns = value;
    ParticleMgr->update();
    updateGL();
}

void glwidget::setSpacing(int value)
{
    ParticleMgr->spacing = value;
    ParticleMgr->update();
    updateGL();
}
