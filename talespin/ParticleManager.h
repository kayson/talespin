#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "ParticleContainer.h"
#include <vector>

class ParticleManager
{
public:   
	ParticleManager();
	~ParticleManager();

	int getContainerIndex(const glm::vec4 col);
    void updateContainers();
    void drawContainers();

	void clearAllContainers();

    ParticleContainer* getContainer(const int n);

    ParticleContainer* AddParticleContainer(const int maxNumParticles, const float radius, const glm::vec3& position, const glm::vec4 color);
    bool removeContainer(const int n);

	void bars(const int columns);

private:
    typedef std::vector<ParticleContainer*> ParticleCtrVector;
    ParticleCtrVector _particleContainer;
};

#endif