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
    void drawContainers();
    void clearContainers();
    int numContainers();
    int getMaxSize();

    glm::vec4 getColorIndex(const int i);
    ParticleContainer* getContainer(const int n);
    ParticleContainer* addContainer(const int maxNumParticles, const glm::vec4 color);
    bool removeContainer(const int n);

    void update();

private:
    typedef std::vector<ParticleContainer*> ContainerCtrlVec;
    ContainerCtrlVec _containerVec;
};

#endif
