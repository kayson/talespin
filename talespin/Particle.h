#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm.hpp>
#include <vector>

class Particle
{
public:

    std::vector<glm::vec3> _targetPosition;
private: 

    glm::vec3 _position;
	glm::vec3 _velocity;
    
    friend class ParticleContainer;
};

#endif
