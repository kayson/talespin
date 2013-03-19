#include "glwidget.h"
#include "draw.h"
#include <FTGL/ftgl.h>

#if defined __APPLE__
#include "GLUT/glut.h"
#elif defined _WIN32 || defined _WIN64 || __unix__
#include "GL/glut.h"
#endif

glwidget::glwidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timer.start(1000/60, this);

    scene_zoom = -100;
    scene_zoom_dx = 0;
    scene_pan_x = -150;
    scene_pan_y = -90;
    mouse_pan_dx = 0;
    mouse_pan_dy = 0;
    mouse_state = -1;
    camera_friction = 0.92f;

    ParticleMgr = new ParticleManager();
    ParticleMgr->radius = 1.0f;
    ParticleMgr->columns = 10;
    ParticleMgr->spacing = 0;

    ParticleMgr->clearAllContainers();
    ParticleMgr->AddParticleContainer(1200, glm::vec4(1.0f,0.5f,1.0f,1.0f));
    ParticleMgr->AddParticleContainer(1450, glm::vec4(1.0f,0.5f,0.0f,1.0f));
    ParticleMgr->AddParticleContainer(1000, glm::vec4(0.0f,1.0f,0.5f,1.0f));
    ParticleMgr->update();
}


glwidget::~glwidget()
{
    makeCurrent();
    ParticleMgr->clearAllContainers();
}

void glwidget::timerEvent(QTimerEvent *event)
{
    ParticleMgr->updateContainers();
    update();
}

void glwidget::initializeGL()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
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
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_POINT_SMOOTH );

    scene_pan_x -= mouse_pan_dx / 40.0f;
    scene_pan_y += mouse_pan_dy / 40.0f;
    mouse_pan_dx *= camera_friction;
    mouse_pan_dy *= camera_friction;

    qreal sc = powf(1.1, scene_zoom_dx);
    scene_zoom_dx *= camera_friction;
    scene_zoom /= sc;

    if( scene_pan_x > -170 * (scene_zoom / -100) ){ scene_pan_x = -170 * (scene_zoom / -100) ; }
    if( scene_pan_y > -90 * (scene_zoom / -100) ){ scene_pan_y = -90 * (scene_zoom / -100) ; }
    if( scene_zoom < -300 ){ scene_zoom = -300; }
    if( scene_zoom > -10 ){ scene_zoom = -10; }

    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(scene_pan_x, scene_pan_y, scene_zoom);
    drawBarText();
    drawGrid();
    ParticleMgr->drawContainers();

//     QPainter painter(this);
//     Draw *draw;
//     draw->drawObject(&painter); //ritar ut objekt
//     painter.end();

    updateGL();

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

    scene_zoom_dx += numSteps * 0.08f;

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

void glwidget::clearMgr()
{
    ParticleMgr->clearAllContainers();
    updateGL();
}

void glwidget::drawBarText()
{
    FTGLPixmapFont font("/Library/Fonts/Microsoft/Arial.ttf");
    for(int i=0;i != ParticleMgr->containerSize();i++)
    {
        font.FaceSize(15);

        glColor4f(ParticleMgr->getColorIndex(i)[0],ParticleMgr->getColorIndex(i)[1],ParticleMgr->getColorIndex(i)[2],ParticleMgr->getColorIndex(i)[3]);
        glRasterPos3f(30.0f + (ParticleMgr->columns * i)+(ParticleMgr->spacing *i),ParticleMgr->max +5.0f,0.0f);
        font.Render("1000");
    }
}

void glwidget::drawGrid()
{
    FTGLPixmapFont font("/Library/Fonts/Microsoft/Arial.ttf");

    // Lines
    glLineWidth(2);
    glColor4f(1.0,1.0,1.0,0.5);
    glBegin(GL_LINES);
    for(int i=1;i < 10;i++)
    {
        glVertex3f(20
                  ,ParticleMgr->intervall*i
                  ,0);

        glVertex3f(30 + ParticleMgr->columns*ParticleMgr->containerSize()+(ParticleMgr->spacing * (ParticleMgr->containerSize() -1) )
                  ,ParticleMgr->intervall*i
                  ,0);
    }

    glVertex3f(20,0,0); glVertex3f(30 + ParticleMgr->columns*ParticleMgr->containerSize()+(ParticleMgr->spacing * (ParticleMgr->containerSize() -1)),0,0);
    glVertex3f(20,0,0); glVertex3f(20,ParticleMgr->max,0);
    glEnd();

    for(int i=1;i < 10;i++)
    {
        font.FaceSize(15);
        glColor4f(1.0,1.0,1.0,0.5);
        glRasterPos3f(0.0f,ParticleMgr->intervall*i,0.0f);

        char numberstring[(((sizeof i*100) * CHAR_BIT) + 2)/3 + 2];
        sprintf(numberstring, "%d", i*100);

        font.Render(numberstring);
    }
}



