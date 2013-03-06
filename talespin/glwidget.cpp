#include "glwidget.h"
#include "GL/glut.h"

glwidget::glwidget(QWidget *parent) :
    QGLWidget(parent)
{

}

void glwidget::initializeGL()
{
    scene_zoom = -100;
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable( GL_POINT_SMOOTH );

    glPointSize( 3.0 );

    mouse_state = -1;

    ParticleMgr = new ParticleManager();

    ParticleMgr->clearAllContainers();
    ParticleMgr->AddParticleContainer(1000, 5.0f, glm::vec3(-10.0f,10.0f,0.0f), glm::vec4(1.0f,0.5f,1.0f,1.0f));
    ParticleMgr->AddParticleContainer(1250, 5.0f, glm::vec3(0.0f,10.0f,0.0f), glm::vec4(1.0f,0.5f,0.0f,1.0f));
    ParticleMgr->AddParticleContainer(10060, 5.0f, glm::vec3(10.0f,10.0f,0.0f), glm::vec4(0.0f,1.0f,0.5f,1.0f));
    ParticleMgr->bars(5);
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
void glwidget::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,scene_zoom);

    ParticleMgr->updateContainers();
    ParticleMgr->drawContainers();

    QWidget::update();
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
    scene_zoom *= 1 - .01f*( event->y() - mouse_y );
    if( scene_zoom < -200 ){ scene_zoom = -200; }
    if( scene_zoom > -1 ){ scene_zoom = -1; }
    mouse_y = event->y();
    QWidget::update(0,0,width(),height());
    break;
  }
}

void glwidget::keyPressEvent(QKeyEvent *k)
{
    switch (k->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_1:
            std::cout<<"hej"<<std::endl;
            break;
    }

}

void glwidget::addBar(int particles)
{
    ParticleMgr->AddParticleContainer(particles, 5.0f, glm::vec3(-10.0f,10.0f,0.0f), glm::vec4(1.0f,0.5f,1.0f,1.0f));
    updateGL();
}

void glwidget::setNumberOfParticles(int value)
{
    ParticleMgr->bars(value);
    updateGL();
}
