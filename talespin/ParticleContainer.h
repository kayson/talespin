#ifndef PARTICLECONTAINER_H
#define PARTICLECONTAINER_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <algorithm>

enum VisualizationType { BARCHART, CIRCLES, LINES };
enum EntityType { QUANTITY, EARNINGS, MEAN };

class ParticleContainer
{
public:   
	void timeUpdateParticles();
    void drawParticles(float radius);

    int timePosition;

    EntityType entity;

    int ID;
    glm::vec4 getColor();
    int getNumParticles();

private:
    void fillParticleContainer();
    ParticleContainer(const int newID, EntityType entity, const int timePos, const int numParticles,  const glm::vec4 color);
    ~ParticleContainer();
    friend class ParticleManager;

    glm::vec4 _color;
    glm::vec3 _position;
    int _numParticles;
    int _profit;



    typedef std::vector<Particle*> ParticleCtrVec;
    ParticleCtrVec _particleVec;
};

#endif
