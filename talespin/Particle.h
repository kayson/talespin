#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

class Particle
{
public:
	Particle(){};
	~Particle(){};
    glm::vec3 _targetPosition;
private: 

    glm::vec3 _position;
	glm::vec3 _velocity;
    
    friend class ParticleContainer;
};

#endif
