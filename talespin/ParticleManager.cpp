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
    int max = 0;

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

void ParticleManager::removeContainers(const int id)
{

    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        if(container.ID == id)
        {

            _containerVec.erase(i);
            i--;
        }
    }


    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
            container.ID--;
    }
    IDcounter --;
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
            else if(visType == LINES)
            {
                int numP2 = 0;
                for(std::vector<ParticleContainer*>::iterator k = _containerVec.begin(); k != _containerVec.end(); ++k)
                {
                    ParticleContainer& container2 = **k;

                    if(container2.ID != container.ID || container2.timePosition != container.timePosition+1) continue;
                    numP2 = container2.getNumParticles();
                }
                int c = 1;
                int numP = container.getNumParticles();
                if(numP2 == 0) numP2 = numP;
                for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j,++c)
                {
                    Particle& particle = **j;

                    particle._targetPosition.at(0) = glm::vec3((30 + (month-1)*columns + (month-1)*spacing) * (numP - c)/numP
                                                               + (30 + (month)*columns + (month)*spacing) * c/numP
                                                               , numP/columns * (numP - c)/numP
                                                               + numP2/columns * c/numP
                                                               , 0.0f);
                }

            }

        }
    }
}

