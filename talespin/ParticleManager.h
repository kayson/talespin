#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "ParticleContainer.h"
#include <vector>

class ParticleManager
{
public:   
    ParticleManager();
    ~ParticleManager();

    float radius;
    int columns;
    int spacing;

    void draw();
    void timeUpdate();
    void drawBars();
    void clearBars();
    int numBars();

    glm::vec4 getColorIndex(const int i);
    ParticleContainer* getBar(const int n);
    ParticleContainer* addBar(const int maxNumParticles, const glm::vec4 color);
    bool removeBar(const int n);

    void update();

private:
    typedef std::vector<ParticleContainer*> ContainerCtrlVec;
    ContainerCtrlVec _containerVec;
};

#endif
