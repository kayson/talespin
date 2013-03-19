#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "ParticleContainer.h"
#include <vector>

class ParticleManager
{
public:   
	ParticleManager();
	~ParticleManager();

    glm::vec4 getColorIndex(const int i);
    float radius;
    float num;
    int columns;
    float intervall,max;
    int spacing;

    void updateContainers();
    void drawContainers();

	void clearAllContainers();

    ParticleContainer* getContainer(const int n);

    ParticleContainer* AddParticleContainer(const int maxNumParticles, const glm::vec4 color);
    bool removeContainer(const int n);

    int containerSize();
    void update();

private:
    typedef std::vector<ParticleContainer*> ParticleCtrVector;
    ParticleCtrVector _particleContainer;
};

#endif
