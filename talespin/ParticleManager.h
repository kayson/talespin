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
    int number;
    int spacing;
    int timePosition;
    int numOftimeInterval;
    int IDcounter;

    VisualizationType visType;
    EntityType entType;

    void draw();
    void timeUpdate();
    void changeEntity();
    void clearContainers();
    void cLogo();
    void removecLogo();
    int numContainers();
    int getMaxSize();

    glm::vec4 getColorIndex(const int i);
    ParticleContainer* getContainer(const int n);
    void addContainer(const int timePos, const int maxNumParticles, const int profit, const glm::vec4 color);
    void removeContainers(const int id);

    void update();

private:
    typedef std::vector<ParticleContainer*> ContainerCtrlVec;
    ContainerCtrlVec _containerVec;
};

#endif
