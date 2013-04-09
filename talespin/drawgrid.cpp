#include "drawgrid.h"
#include "QtOpenGL/QGLWidget"
//#include <FTGL/ftgl.h>

float maxsize = 0;
float intervall = 0;
int numContainers = 0;

drawGrid::drawGrid()
{

}

drawGrid* drawGrid::addGrid()
{
    drawGrid* newGrid = new drawGrid();
    return newGrid;
}

void drawGrid::drawBarText(ParticleManager *pMgr)
{
    if(hide)
    {

    maxsize = pMgr->getMaxSize() / pMgr->columns;
    intervall = maxsize/10;

//    FTGLPixmapFont font("/Library/Fonts/Microsoft/Arial.ttf");
//    for(int i=0;i != pMgr->numContainers();i++)
//    {

//        font.FaceSize(15);
//        glColor4fv(&pMgr->getColorIndex(i)[0]);
//        glRasterPos3f(30.0f + (pMgr->columns * i)+(pMgr->spacing *i), maxsize + 5.0f,0.0f);

//        printIntToString = pMgr->getContainer(i)->getNumParticles();
//        char numberstring[(((sizeof printIntToString) * CHAR_BIT) + 2)/3 + 2];
//        sprintf(numberstring, "%d", printIntToString);

//        font.Render(numberstring);

//    }
    }
}

void drawGrid::drawBarGrid(ParticleManager *pMgr)
{
    if(hide)
    {
        //FTGLPixmapFont font("/Library/Fonts/Microsoft/Arial.ttf");

        maxsize = pMgr->getMaxSize() / pMgr->columns;
        intervall = maxsize/10;
        numContainers = pMgr->numContainers();

        // Lines
        glLineWidth(2);
        glColor4f(1.0,1.0,1.0,0.5);
        glBegin(GL_LINES);
        for(int i=1;i < 10;i++)
        {
            glVertex3f(20
                      ,intervall*i
                      ,0);

            glVertex3f(30 + pMgr->columns*numContainers+(pMgr->spacing * (numContainers -1) )
                      ,intervall*i
                      ,0);
        }

        glVertex3f(20,0,0);
        glVertex3f(30 + pMgr->columns*numContainers+(pMgr->spacing * (numContainers -1)),0,0);
        glVertex3f(20,0,0); glVertex3f(20,maxsize,0);
        glEnd();

//        for(int i=1;i < 10;i++)
//        {
//            font.FaceSize(15);
//            glColor4f(1.0,1.0,1.0,0.5);
//            glRasterPos3f(0.0f,intervall*i,0.0f);

//            printIntToString = pMgr->getMaxSize()/10;
//            char numberstring[(((sizeof printIntToString*i) * CHAR_BIT) + 2)/3 + 2];
//            sprintf(numberstring, "%d", printIntToString*i);

//            font.Render(numberstring);
//        }
    }
}
