#include "ParticleManager.h"
#include <algorithm>
#include <iostream>

ParticleManager::ParticleManager()
{
    IDcounter = 0;
}

ParticleManager::~ParticleManager()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer* const container = *i;
        delete container;
    }
    _containerVec.clear();
}

void ParticleManager::timeUpdate()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        container.timeUpdateParticles();
    }
}


void ParticleManager::draw()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
            container.drawParticles(radius, visType);
    }
}

ParticleContainer* ParticleManager::addContainer(const int timePos, const int maxNumParticles, const glm::vec4 color)
{
    ParticleContainer* newContainer = new ParticleContainer(IDcounter,timePos, maxNumParticles, color);
    _containerVec.push_back(newContainer);
    return newContainer;
}

glm::vec4 ParticleManager::getColorIndex(const int i)
{
    ParticleContainer* container = getContainer(i);
    return container->getColor();
}

int ParticleManager::numContainers()
{
    return _containerVec.size();
}

int ParticleManager::getMaxSize()
{
    float max = 0;

    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        if(container.getNumParticles() > max)
        {
            max = container.getNumParticles();
        }
    }
    return max;
}

void ParticleManager::clearContainers()
{
    _containerVec.clear();
}

ParticleContainer* ParticleManager::getContainer(const int n)
{
    if(_containerVec.size() > n)
        return _containerVec.at(n);
	else
		return false;
}

bool ParticleManager::removeContainer(const int n)
{
    if(_containerVec.size() < n)
		return false;

    _containerVec.erase(_containerVec.begin()+n);
	return true;

}

void ParticleManager::update()
{
    float n = 0;

    for(int month = 1; month <= 12; month++)
    {
        for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
        {
            ParticleContainer& container = **i;

            if(container.timePosition != month) continue;

            if(visType == BARCHART)
            {
                int c = 1;
                int r = 1;

                for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j,++c)
                {
                    if(c > columns)
                    {
                        c = 1;
                        r++;
                    }
                    Particle& particle = **j;

                    particle._targetPosition.at(0) = glm::vec3(30 + c + n*columns + (month-1)*spacing , r, 0.0f);
                }
                n++;
            }
//            else if(visType == LINES)
//            {
//                for(std::vector<ParticleContainer*>::iterator k = _containerVec.begin(); k != _containerVec.end(); ++k)
//                {
//                    ParticleContainer& container2 = **k;

//                    if(container2.ID != container.ID && container2.timePosition != month+1) continue;

//                    int c = 1;
//                    int numP = container.getNumParticles();
//                    int numP2 = container2.getNumParticles();
//                    for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j,++c)
//                    {
//                        Particle& particle = **j;

//                        particle._targetPosition.at(0) = glm::vec3((30 + (month-1)*10 + (month-1)*spacing)*(numP - c)/numP
//                                                                   + (30 + (month)*10 + (month)*spacing)*c/numP
//                                                                   , numP/10*(numP - c)/numP
//                                                                   + numP2/10*c/numP
//                                                                   , 0.0f);
//                    }
//                    n++;
//                }
//            }

        }
    }
}
