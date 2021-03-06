#ifndef DRAWGRID_H
#define DRAWGRID_H

#include "ParticleManager.h"

class drawGrid
{
public:
    drawGrid();
    void drawBarText();
    void drawBarGrid(ParticleManager *pMgr);
    void drawBarText(ParticleManager *pMgr);
    drawGrid* addGrid();

    ParticleManager* ParticleMgr;
    bool hideGrid, hideNumbers ;

private:
    friend class ParticleManager;
    int printIntToString;

};

#endif // DRAWGRID_H
