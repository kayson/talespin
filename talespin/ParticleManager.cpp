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

glm::vec4 ParticleManager::getColorIndex(const int i)
{
       ParticleContainer* container = getContainer(i);
        return container->getColor();
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

int ParticleManager::containerSize()
{
    return _particleContainer.size();
}

void ParticleManager::update()
{
    num = 0;
    max = 0;
    intervall = 0;

    for(ParticleCtrVector::iterator i = _particleContainer.begin(); i != _particleContainer.end(); ++i,num++)
    {
        ParticleContainer& container = **i;
		int c = 1;
        int rows = 1;
		for(std::vector<Particle*>::iterator j = container._particleVector.begin(); j != container._particleVector.end(); ++j,++c)
		{
            if(c > columns)
			{
				c = 1;
                rows++;
			}

			Particle& particle = **j;
            particle._targetPosition = glm::vec3(30 + c + num*columns + num*spacing , rows, 0.0f);
		}
        if(container._particleVector.size()/columns>max)
        max=container._particleVector.size()/columns;
        intervall = max/10.0f;
    }
}

