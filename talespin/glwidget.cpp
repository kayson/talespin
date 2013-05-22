#include "glwidget.h"

#include <FTGL/ftgl.h>

#if defined __APPLE__
#include "GLUT/glut.h"
#elif defined _WIN32 || defined _WIN64 || __unix__
#include "GL/glut.h"
#endif

#include <QSettings>
#include "ParticleManager.h"
#include "drawgrid.h"

glwidget::glwidget(QWidget *parent)
    : QGLWidget(parent)
{
    timer.start(1000/60, this);

    scene_zoom_dx = 0;
    mouse_pan_dx = 0;
    mouse_pan_dy = 0;
    mouse_state = -1;
    camera_friction = 0.92f;

    _autoZoom = true;

    ParticleMgr = new ParticleManager();
    ParticleMgr->visType = CLOGO;
    ParticleMgr->cLogo();

    _drawGrid = new drawGrid();

    loadSettings();
}

glwidget::~glwidget()
{
    makeCurrent();

    saveSettings();
    ParticleMgr->clearContainers();
}

void glwidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    ParticleMgr->timeUpdate();
    update();
}

void glwidget::initializeGL()
{
    glClearColor( (1.0f/255.0f)*60.0f, (1.0f/255.0f)*60.0f, (1.0f/255.0f)*59.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_POINT_SMOOTH );
    glDisable(GL_DEPTH_TEST);

}

void glwidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(75.f, // FOV
                    (GLfloat) width / (GLfloat) height, // Aspect Ratio
                    1.0f, // Z-Clipping Near
                    10000.0f); // Z-Clipping Far
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void glwidget::paintGL()
{
    scene_pan_x -= mouse_pan_dx / 40.0f;
    scene_pan_y += mouse_pan_dy / 40.0f;
    mouse_pan_dx *= camera_friction;
    mouse_pan_dy *= camera_friction;

    qreal sc = powf(1.1, scene_zoom_dx);
    scene_zoom_dx *= camera_friction;
    scene_zoom /= sc;

    zoomChanged(scene_zoom);

    if(ParticleMgr->visType == CLOGO)
        ParticleMgr->radius = 1;
    else
        ParticleMgr->radius = -300 / scene_zoom;

    if(_autoZoom)
        fixCam();

    if( scene_zoom < -3000 ){ scene_zoom = -3000; }
    if( scene_zoom > -10 ){ scene_zoom = -10; }

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(scene_pan_x, scene_pan_y, scene_zoom);
    _drawGrid->drawBarGrid(ParticleMgr);
    ParticleMgr->draw();
    _drawGrid->drawBarText(ParticleMgr);

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

void glwidget::zoom(int value)
{
    scene_zoom = value;
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

void glwidget::fixCam()
{
    float maxX = 0;
    if(ParticleMgr->visType == BARCHART)
        maxX = -( (ParticleMgr->columns * ParticleMgr->numContainers()) + ParticleMgr->spacing * (ParticleMgr->numOftimeInterval - 1) );
    else if(ParticleMgr->visType == LINES)
        maxX = -( (ParticleMgr->columns * ParticleMgr->numOftimeInterval) + ParticleMgr->spacing * ParticleMgr->numOftimeInterval );

    float maxY = -( ParticleMgr->getMaxSize() / ParticleMgr->columns );

    scene_pan_x = maxX * 0.5;
    scene_pan_y = maxY * 0.5;

    float scaleX = 0;
    float scaleY = 0;

    if(ParticleMgr->entType == QUANTITY)
    {
        scaleX = 0.5;
        scaleY = 0.8;
    }
    else
    {
        scaleX = 0.3;
        scaleY = 0.8;
    }

    if((maxX/maxY) >= 1.5)
        scene_zoom = maxX * scaleX;
    else
        scene_zoom = maxY * scaleY;

}

void glwidget::showGrid(bool hide)
{
    //std::cout << hide <<std::endl;
    _drawGrid->hideGrid = hide;
}

void glwidget::showNumbers(bool hide)
{
    _drawGrid->hideNumbers = hide;
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

void glwidget::timePositionChanged(int value)
{
    ParticleMgr->timePosition = value;
    ParticleMgr->update();
    updateGL();
}

void glwidget::autoZoom(bool zoom)
{
    if(zoom)
    {
        _autoZoom = true;
        fixCam();
    }
    else
        _autoZoom = false;
}

void glwidget::clearMgr()
{
    ParticleMgr->clearContainers();
    updateGL();
}





