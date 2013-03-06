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
	void drawParticles();

	bool colorCheck(glm::vec4 col);
	void targeted();
	void untarget();

private:
    void fillContainer();
    ParticleContainer(const int numParticles, const float radius, const glm::vec3& position, const glm::vec4 color);
    ~ParticleContainer();
    friend class ParticleManager;
    
    float _radius;
    glm::vec3 _position;
    glm::vec4 _color;

    typedef std::vector<Particle*> ParticleVector;
    ParticleVector _particleVector;
};

#endif
