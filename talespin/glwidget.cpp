#include "glwidget.h"
#include "draw.h"
#if defined __APPLE__
#include "GLUT/glut.h"
#elif defined _WIN32 || defined _WIN64 || __unix__
#include "GL/glut.h"
#endif

#include <QSettings>
#include "BarChart.h"


glwidget::glwidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timer.start(1000/60, this);

    scene_zoom_dx = 0;
    mouse_pan_dx = 0;
    mouse_pan_dy = 0;
    mouse_state = -1;
    camera_friction = 0.92f;

    Bars = new BarChart();
    Bars->columns = 10;
    Bars->radius = 1.0f;
    Bars->spacing = 0;

    Bars->clearBars();
    Bars->addBar(1000, glm::vec4(1.0f,0.5f,1.0f,1.0f));
    Bars->addBar(1250, glm::vec4(1.0f,0.5f,0.0f,1.0f));
    Bars->addBar(1060, glm::vec4(0.0f,1.0f,0.5f,1.0f));
    Bars->update();

    Circs = new Circles();
    Circs->addCircle(100, glm::vec4(0.5f,1.0f,0.5f,0.5f));

    visMgr = new VisualizationManager();
    visMgr->add(Bars);
    visMgr->add(Circs);

    loadSettings();
}

glwidget::~glwidget()
{
    makeCurrent();

    saveSettings();
    //ParticleMgr->clearBars();
}

void glwidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    //ParticleMgr->updateBars();
    visMgr->timeUpdate();
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

//void glwidget::paintGL()
//{
//    scene_pan_x -= mouse_pan_dx / 40.0f;
//    scene_pan_y += mouse_pan_dy / 40.0f;
//    mouse_pan_dx *= camera_friction;
//    mouse_pan_dy *= camera_friction;

//    qreal sc = powf(1.1, scene_zoom_dx);
//    scene_zoom_dx *= camera_friction;
//    scene_zoom /= sc;

//    if( scene_pan_x > -170 * (scene_zoom / -100) ){ scene_pan_x = -170 * (scene_zoom / -100) ; }
//    if( scene_pan_y > -90 * (scene_zoom / -100) ){ scene_pan_y = -90 * (scene_zoom / -100) ; }
//    if( scene_zoom < -300 ){ scene_zoom = -300; }
//    if( scene_zoom > -10 ){ scene_zoom = -10; }

//    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(scene_pan_x, scene_pan_y, scene_zoom);

//    ParticleMgr->drawContainers();

//}

void glwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);

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

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(scene_pan_x, scene_pan_y, scene_zoom);

    visMgr->draw();

    QPainter painter(this);
    Draw *draw;
    draw->drawObject(&painter); //ritar ut objekt
    painter.end();

}

void glwidget::mousePressEvent ( QMouseEvent * event )
{
  mouse_state = event->button();
  mouse_x = event->x();
  mouse_y = event->y();
}

void glwidget::mouseReleaseEvent ( QMouseEvent * event )
{
  Q_UNUSED(event);

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

void glwidget::saveSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    settings.setValue("sceneZoom", scene_zoom);
    settings.setValue("scenePanX", scene_pan_x);
    settings.setValue("scenePanY", scene_pan_y);

}

void glwidget::loadSettings()
{
    QSettings settings("Visualiseringscenter C", "ViC");

    scene_zoom = settings.value("sceneZoom", -100).toFloat();
    scene_pan_x = settings.value("scenePanX", -150).toFloat();
    scene_pan_y = settings.value("scenePanY", -90).toFloat();

}

void glwidget::particleSize(int value)
{
    Bars->radius = value;
    Bars->update();
    updateGL();
}

void glwidget::setNumberOfParticles(int value)
{
    Bars->columns = value;
    Bars->update();
    updateGL();
}

void glwidget::setSpacing(int value)
{
    Bars->spacing = value;
    Bars->update();
    updateGL();
}

void glwidget::clearMgr()
{
    Bars->clearBars();
    updateGL();
}

