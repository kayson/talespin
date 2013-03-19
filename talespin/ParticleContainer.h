#ifndef PARTICLECONTAINER_H
#define PARTICLECONTAINER_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <algorithm>

class ParticleContainer
{
public:   
	void timeUpdateParticles();
    void drawParticles(float radius);

    glm::vec4 getColor();

private:
    void fillParticleContainer();
    ParticleContainer(const int numParticles,  const glm::vec4 color);
    ~ParticleContainer();
    friend class ParticleManager;
    
    glm::vec4 _color;

    typedef std::vector<Particle*> ParticleCtrVec;
    ParticleCtrVec _particleVec;
};

#endif
