#include "drawgrid.h"
#include "QtOpenGL/QGLWidget"
#include <FTGL/ftgl.h>

float maxsize = 0;
float intervall = 0;
int numContainers = 0;

drawGrid::drawGrid()
{
    numberOfGrids = 10;
}

drawGrid* drawGrid::addGrid()
{
    drawGrid* newGrid = new drawGrid();
    return newGrid;
}

void drawGrid::drawBarText(ParticleManager *pMgr)
{
    if(visible)
    {
        maxsize = pMgr->getMaxSize() / pMgr->columns;
        intervall = maxsize/10;

//        if(pMgr->IDcounter>0)
//       {
//           std::cout<< 12*pMgr->IDcounter<<std::endl;
//       }

        FTGLPixmapFont font("C:/WINDOWS/Fonts/Arial.ttf");
        if(!font.Error())
        {
            for(int i=0; i != pMgr->numContainers(); i++)
            {
                font.FaceSize(15);
                glColor4fv(&pMgr->getColorIndex(i)[0]);
                glRasterPos3f(30.0f + (pMgr->columns * pMgr->IDcounter * i)+(pMgr->spacing *i),pMgr->getContainer(i)->getNumParticles()/pMgr->columns + 10.0f,0.0f);

//                std::cout<<i<<" "<<12*(pMgr->IDcounter-1)<<std::endl;
                if(i > 12*(pMgr->IDcounter-1)&& pMgr->IDcounter>1)
                {
                    std::cout<<"hej"<<std::endl;
                    glRasterPos3f(-370.0f + (pMgr->columns * pMgr->IDcounter * i)+(pMgr->spacing *i),pMgr->getContainer(i)->getNumParticles()/pMgr->columns + 10.0f,0.0f);
                }

                //glRasterPos3f(30.0f,pMgr->getContainer(i)->getNumParticles()/pMgr->columns + 10.0f,0.0f);
                printIntToString = pMgr->getContainer(i)->getNumParticles();
                char numberstring[(((sizeof printIntToString) * CHAR_BIT) + 2)/3 + 2];
                sprintf_s(numberstring, "%d", printIntToString);

                font.Render(numberstring);
            }

            QStringList month;
            month<<"Jan"<<"Feb"<<"Mar"<<"Apr"<<"May"<<"Jun"<<"Jul"<<"Aug"<<"Sep"<<"Okt"<<"Nov"<<"Dec";

            for(int i = 0; i < month.size(); ++i)
            {
                glColor4f(1.0f,1.0f,1.0f,0.7f);
                glRasterPos3f(30.0f + (pMgr->columns * pMgr->IDcounter * i)+(pMgr->spacing *i),-10.0f,0.0f);
                QByteArray ba = month.at(i).toLocal8Bit();
                const char *c_str = ba.data();
                font.Render(c_str);
            }
         }
    }
}

void drawGrid::drawBarGrid(ParticleManager *pMgr)
{
    if(visible && pMgr->visType==BARCHART)
    {
        FTGLPixmapFont font("C:/WINDOWS/Fonts/Arial.ttf");

        maxsize = pMgr->getMaxSize() / pMgr->columns;
        intervall = maxsize/numberOfGrids;
        if(pMgr->IDcounter>0)
            numContainers = pMgr->numContainers()/pMgr->IDcounter;

        // Lines
        glLineWidth(2);
        glColor4f(1.0f,1.0f,1.0f,0.2f);
        glBegin(GL_LINES);
        for(int i=1;i < numberOfGrids+1;i++)
        {
//            if(pMgr->IDcounter>0)
//            {
//                std::cout<<pMgr->IDcounter*pMgr->columns*numContainers<<" "<<(pMgr->spacing * (numContainers -1) )<<std::endl;
//            }

            glVertex3f(20
                      ,intervall*i
                      ,0);

            glVertex3f(30 + (pMgr->IDcounter*pMgr->columns*numContainers)+(pMgr->spacing * (numContainers -1) ) //ändra
                      ,intervall*i
                      ,0);
        }
        glVertex3f(20,0,0);
        glVertex3f(30 + pMgr->IDcounter*pMgr->columns*numContainers+pMgr->spacing * (numContainers -1) ,0,0);


        glVertex3f(20,0,0);
        glVertex3f(20,maxsize,0);
        glEnd();

        for(int i=1;i < numberOfGrids + 1;i++)
        {
            font.FaceSize(15);
            glColor4f(1.0,1.0,1.0,0.5);
            glRasterPos3f(10.0f,intervall*i,0.0f);

            printIntToString = i*pMgr->getMaxSize()/numberOfGrids;

            char numberstring[(((sizeof printIntToString) * CHAR_BIT) + 2)/3 + 2];
            sprintf_s(numberstring, "%d", printIntToString);

            font.Render(numberstring);
        }
    }

    if(visible && pMgr->visType==LINES)
    {
        FTGLPixmapFont font("C:/WINDOWS/Fonts/Arial.ttf");

        maxsize = pMgr->getMaxSize() / pMgr->columns;
        intervall = maxsize/numberOfGrids;
        if(pMgr->IDcounter>0)
            numContainers = pMgr->numContainers()/pMgr->IDcounter;

        // Lines
        glLineWidth(2);
        glColor4f(1.0f,1.0f,1.0f,0.2f);
        glBegin(GL_LINES);
        for(int i=1;i < numberOfGrids+1;i++)
        {
//            if(pMgr->IDcounter>0)
//            {
//                std::cout<<pMgr->IDcounter*pMgr->columns*numContainers<<" "<<(pMgr->spacing * (numContainers -1) )<<std::endl;
//            }

            glVertex3f(20
                      ,intervall*i
                      ,0);

            glVertex3f(30 + (pMgr->columns*numContainers)+(pMgr->spacing * (numContainers -1) ) //ändra
                      ,intervall*i
                      ,0);
        }
        glVertex3f(20,0,0);
        glVertex3f(30 + pMgr->columns*numContainers+pMgr->spacing * (numContainers -1) ,0,0);


        glVertex3f(20,0,0);
        glVertex3f(20,maxsize,0);
        glEnd();

    }
}
