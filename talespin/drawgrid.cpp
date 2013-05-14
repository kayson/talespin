#include "drawgrid.h"
#include "QtOpenGL/QGLWidget"
#include <FTGL/ftgl.h>

float maxsize = 0;
float intervall = 0;

const int fontSize = 15;

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
    if(hideNumbers)
    {
        FTGLPixmapFont font("C:/WINDOWS/Fonts/Arial.ttf");
        if(!font.Error())
        {
            for(int i=0; i != pMgr->numContainers(); i++)
            {
                if(pMgr->getContainer(i)->getNumParticles() == 0 ) continue;
                font.FaceSize(fontSize);
                glColor4fv(&pMgr->getColorIndex(i)[0]);

                if(pMgr->entType == QUANTITY)
                    printIntToString = pMgr->getContainer(i)->getNumParticles();
                else if(pMgr->entType == EARNINGS)
                    printIntToString = pMgr->getContainer(i)->getProfit()/1000;
                else if(pMgr->entType == MEAN)
                    printIntToString = pMgr->getContainer(i)->getProfit()/pMgr->getContainer(i)->getNumParticles();

                if(pMgr->visType == BARCHART)
                    glRasterPos3f(32.0f + (pMgr->columns * (pMgr->getContainer(i)->timePosition-1) * pMgr->IDcounter )
                                  + (pMgr->spacing * (pMgr->getContainer(i)->timePosition-1) )
                                  + (pMgr->columns * pMgr->getContainer(i)->ID)
                                  ,printIntToString/pMgr->columns + 5.0f
                                  ,0.0f);
                else if(pMgr->visType == LINES)
                    glRasterPos3f(30.0f + (pMgr->columns * (pMgr->getContainer(i)->timePosition-1) )
                                  + (pMgr->spacing * (pMgr->getContainer(i)->timePosition-1) )
                                  ,printIntToString/pMgr->columns + 10.0f
                                  ,0.0f);



                char numberstring[(((sizeof printIntToString) * CHAR_BIT) + 2)/3 + 2];
                sprintf_s(numberstring, "%d", printIntToString);

                font.Render(numberstring);
            }
         }
    }
}

void drawGrid::drawBarGrid(ParticleManager *pMgr)
{
    if(hideGrid && (pMgr->visType==BARCHART || pMgr->visType==LINES))
    {
        FTGLPixmapFont font("C:/WINDOWS/Fonts/Arial.ttf");

        maxsize = pMgr->getMaxSize();
        if(maxsize >= 2000)
        {
            maxsize /= 1000;
            maxsize = floor(maxsize + 0.5) * 1000;
            intervall = 1000;
        }
        else if(maxsize >= 200)
        {
            maxsize /= 100;
            maxsize = floor(maxsize + 0.5) * 100;
            intervall = 100;
        }
        else if(maxsize >= 20)
        {
            maxsize /= 10;
            maxsize = floor(maxsize + 0.5) * 10;
            intervall = 10;
        }
        else
            intervall = 1;

        // Lines
        glLineWidth(2);
        glColor4f(1.0f,1.0f,1.0f,0.2f);
        glBegin(GL_LINES);
        for(int i=intervall;i <= maxsize;i+=intervall)
        {
            glVertex3f(20
                      ,(float)i / (float)pMgr->columns
                      ,0);
            if(pMgr->visType == BARCHART)
                glVertex3f(40 + (pMgr->columns*pMgr->numContainers()) + pMgr->spacing * (pMgr->numOftimeInterval - 1)
                      ,(float)i / (float)pMgr->columns
                      ,0);
            else if(pMgr->visType == LINES)
                glVertex3f(40 + (pMgr->columns*pMgr->numOftimeInterval) + pMgr->spacing * pMgr->numOftimeInterval
                      ,(float)i / (float)pMgr->columns
                      ,0);

        }
        glVertex3f(20,0,0);
        if(pMgr->visType == BARCHART)
            glVertex3f(40 + pMgr->columns*pMgr->numContainers() + pMgr->spacing * (pMgr->numOftimeInterval - 1) ,0,0);
         else if(pMgr->visType == LINES)
            glVertex3f(40 + pMgr->columns*pMgr->numOftimeInterval + pMgr->spacing * pMgr->numOftimeInterval ,0,0);

        glVertex3f(20,0,0);
        glVertex3f(20,maxsize / pMgr->columns,0);
        glEnd();

        for(int i=intervall;i <= maxsize;i+=intervall)
        {
            font.FaceSize(fontSize);

            glColor4f(1.0,1.0,1.0,0.5);

            glRasterPos3f(10.0f,i / pMgr->columns,0.0f);

            printIntToString = i;

            char numberstring[(((sizeof printIntToString) * CHAR_BIT) + 2)/3 + 2];
            sprintf_s(numberstring, "%d", printIntToString);
            font.Render(numberstring);
        }

        QStringList intervals;
        if(pMgr->numOftimeInterval == 12)
            intervals<<"Jan"<<"Feb"<<"Mar"<<"Apr"<<"May"<<"Jun"<<"Jul"<<"Aug"<<"Sep"<<"Okt"<<"Nov"<<"Dec";
        if(pMgr->numOftimeInterval == 4)
            intervals<<"Vår"<<"Sommar"<<"Höst"<<"Vinter";
        if(pMgr->numOftimeInterval == 31)
        {
            for(int d = 1; d <= 31; d++)
            {
                intervals<<QString::number(d);
            }
        }

        for(int i = 0; i < intervals.size(); ++i)
        {
            glColor4f(1.0f,1.0f,1.0f,0.7f);
            if(pMgr->visType == BARCHART)
                glRasterPos3f(30.0f + (pMgr->columns * pMgr->IDcounter * i)+(pMgr->spacing *i),-10.0f,0.0f);
            else if(pMgr->visType == LINES)
                glRasterPos3f(30.0f + (pMgr->columns * i)+(pMgr->spacing *i),-10.0f,0.0f);
            QByteArray ba = intervals.at(i).toLocal8Bit();
            const char *c_str = ba.data();
            font.Render(c_str);
        }

    }
}
