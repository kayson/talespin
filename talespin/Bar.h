#ifndef PARTICLECONTAINER_H
#define PARTICLECONTAINER_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Bar
{
public:   
	void timeUpdateParticles();
    void drawParticles(float radius);

private:
    void fillBar();
    Bar(const int numParticles,  const glm::vec4 color);
    ~Bar();
    friend class BarChart;
    
    glm::vec4 _color;

    typedef std::vector<Particle*> ParticleVector;
    ParticleVector _particleVector;
};

#endif
