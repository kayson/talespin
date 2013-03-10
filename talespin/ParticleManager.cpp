#include "ParticleManager.h"
#include <algorithm>
#include <iostream>

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
    for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i)
    {
        ParticleContainer* const container = *i;
        delete container;
    }
    _particleContainer.clear();
}

void ParticleManager::updateContainers()
{
    for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i)
    {
        ParticleContainer& container = **i;
        container.timeUpdateParticles();
    }
}

void ParticleManager::drawContainers()
{
    for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i)
    {
        ParticleContainer& container = **i;
        container.drawParticles(radius);
    }
}

ParticleContainer* ParticleManager::AddParticleContainer(const int maxNumParticles, const glm::vec4 color)
{
    ParticleContainer* newContainer = new ParticleContainer(maxNumParticles, color);
    _particleContainer.push_back(newContainer);
    return newContainer;
}

int ParticleManager::getContainerIndex(const glm::vec4 color)
{
	int n = 0;
	for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i)
    {
        ParticleContainer* container = *i;
		if(container->colorCheck(color))
		{
			return n;
		}
		n++;
    }

	return -1;
}

void ParticleManager::clearAllContainers()
{
	_particleContainer.clear();
}

ParticleContainer* ParticleManager::getContainer(const int n)
{
    if(_particleContainer.size() > n)
		return _particleContainer.at(n);
	else
		return false;
}

bool ParticleManager::removeContainer(const int n)
{
	if(_particleContainer.size() < n)
		return false;

    _particleContainer.erase(_particleContainer.begin()+n);
	return true;

}

void ParticleManager::update()
{
    float n = 0;

    for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i,n++)
    {
        ParticleContainer& container = **i;
		int c = 1;
        int r = 1;

		for(std::vector<Particle*>::iterator j = container._particleVector.begin(); j != container._particleVector.end(); ++j,++c)
		{
			if(c > columns) 
			{
				c = 1;
				r++;
			}
			Particle& particle = **j;
            particle._targetPosition = glm::vec3(c + n*columns + n*spacing + 15, r, 0.0f);
		}
    }
}

