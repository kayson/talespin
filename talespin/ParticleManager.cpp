#include "ParticleManager.h"
#include <algorithm>
#include <iostream>

ParticleManager::ParticleManager()
{
    IDcounter = 0;
    entType = QUANTITY;
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
        if(visType == CLOGO)
            container.logoUpdateParticles();
        else
        container.timeUpdateParticles();
    }
}

void ParticleManager::draw()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        if( container.getNumParticles() == 0 ) continue;
        if(visType != CIRCLES || container.timePosition == timePosition)
            container.drawParticles(radius);
    }
}

void ParticleManager::changeEntity()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        container.fillParticleContainer(entType);
    }
}

void ParticleManager::addContainer(const int timePos, const int maxNumParticles, const int profit, const glm::vec4 color)
{
    ParticleContainer* newContainer = new ParticleContainer(IDcounter, entType, timePos, maxNumParticles, profit, color);
    _containerVec.push_back(newContainer);
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
        if(entType == QUANTITY)
        {
            if(container.getNumParticles() > max)
            {
                max = container.getNumParticles();
            }
        }
        else if(entType == EARNINGS)
        {
            if(container.getProfit()/1000 > max)
            {
                max = container.getProfit()/1000;
            }
        }
        else if(entType == MEAN)
        {
            if( container.getNumParticles() == 0 ) continue;
            else if( (container.getProfit()/container.getNumParticles()) > max)
            {
                max = (container.getProfit()/container.getNumParticles());
            }
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
        //std::cout<<container.ID<<std::endl;
        if(container.ID == id)
        {
            _containerVec.erase(i);
            i--;
        }
    }
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;
        if(container.ID > id)
        container.ID--;
    }

    IDcounter --;
}

void ParticleManager::update()
{
    if(visType == BARCHART || visType == LINES)
    {
        number = 0;

        for(int timeInterval = 1; timeInterval <= numOftimeInterval; timeInterval++)
        {
            for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
            {
                ParticleContainer& container = **i;
                if( container.getNumParticles() == 0 ) continue;
                if( container.timePosition != timeInterval ) continue;

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

                        particle._targetPosition.at(0) = glm::vec3(30 + c + number*columns + (timeInterval-1)*spacing , r, 0.0f);
                    }
                    number++;
                }
                else if(visType == LINES)
                {
                    int numP2 = 0;

                    for(std::vector<ParticleContainer*>::iterator k = _containerVec.begin(); k != _containerVec.end(); ++k)
                    {
                        ParticleContainer& container2 = **k;
                        if(container2.getNumParticles() == 0 ) continue;
                        if(container2.ID != container.ID || container2.timePosition != container.timePosition+1) continue;
                        if(entType == QUANTITY)
                            numP2 = container2.getNumParticles();
                        else if(entType == EARNINGS)
                            numP2 = container2.getProfit()/1000;
                        else if(entType == MEAN)
                            numP2 = container2.getProfit()/container2.getNumParticles();
                    }
                    int c = 1;
                    int numP = 0;

                    if(entType == QUANTITY)
                        numP = container.getNumParticles();
                    else if(entType == EARNINGS)
                        numP = container.getProfit()/1000;
                    else if(entType == MEAN)                      
                        numP = container.getProfit()/container.getNumParticles();

                    if(numP2 == 0) numP2 = numP;

                    for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j,++c)
                    {
                        Particle& particle = **j;

                        particle._targetPosition.at(0) = glm::vec3((30 + (timeInterval-1)*columns + (timeInterval-1)*spacing) * (numP - c)/numP
                                                                   + (30 + (timeInterval)*columns + (timeInterval)*spacing) * c/numP
                                                                   , numP/columns * (numP - c)/numP
                                                                   + numP2/columns * c/numP
                                                                   , 0.0f);
                    }

                }


            }
        }
    }
    else if(visType == CIRCLES)
    {
        for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
        {
            ParticleContainer& container = **i;
            int numP = container.getNumParticles();
            for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j)
            {
                Particle& particle = **j;
                float rng = ((float) rand() / (RAND_MAX+1.0f));
                float R = numP / 10 * sqrt(((float) rand() / (RAND_MAX+1.0f)));
                float xPos = R * cosf(3.1415926 * 2 * rng);
                float yPos = R * sinf(3.1415926 * 2 * rng);
                particle._targetPosition.at(0) = glm::vec3(container._position.x + xPos
                                                           , container._position.y + yPos
                                                           , 0.0f);
            }
        }
    }
    else if(visType == CLOGO)
    {
        for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
        {
            ParticleContainer& container = **i;

            for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j)
            {
                Particle& particle = **j;
                float rng = ((float) rand() / (RAND_MAX+1.0f));
                float R = 0;
                float xPos = 0;
                float yPos = 0;
                if( container.timePosition == 1 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.1) + 68;
                    xPos = R * cosf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                    yPos = R * sinf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                }
                else if( container.timePosition == 2 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.3) + 44;
                    xPos = R * cosf(3.1415926 * 0.5 * rng + 3.1415926 * 0.25);
                    yPos = R * sinf(3.1415926 * 0.5 * rng + 3.1415926 * 0.25);
                }
                else if( container.timePosition == 3 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 2.2) - 3;
                    xPos = R * cosf(3.1415926 * 0.53 * rng + 3.1415926 * 0.25);
                    yPos = R * sinf(3.1415926 * 0.53 * rng + 3.1415926 * 0.25);
                }
                else if( container.timePosition == 4 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 2.2) + 9;
                    xPos = R * cosf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                    yPos = R * sinf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                }
                else if( container.timePosition == 5 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.01) + 50;
                    xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                    yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                }
                else if( container.timePosition == 6 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.7) + 57;
                    xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                    yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                }
                else if( container.timePosition == 7 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.08) + 68;
                    xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                    yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                }
                else if( container.timePosition == 8 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.2) + 36;
                    xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                    yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                }
                else if( container.timePosition == 9 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.01) + 52;
                    xPos = R * cosf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                    yPos = R * sinf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                }
                else if( container.timePosition == 10 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.7) + 58;
                    xPos = R * cosf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                    yPos = R * sinf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                }
                else if( container.timePosition == 11 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.15) + 68;
                    xPos = R * cosf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                    yPos = R * sinf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                }
                else if( container.timePosition == 12 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.9) + 28;
                    xPos = R * cosf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                    yPos = R * sinf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                }
                else if( container.timePosition == 13 )
                {
                    R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.2) + 48;
                    xPos = R * cosf(3.1415926 * 0.19 * rng + 3.1415926 * 1.7);
                    yPos = R * sinf(3.1415926 * 0.19 * rng + 3.1415926 * 1.7);
                }

                particle._targetPosition.at(0) = glm::vec3(container._position.x + xPos
                                                           , container._position.y + yPos + 150
                                                           , 0.0f);
            }
        }
    }
}

void ParticleManager::cLogo()
{
    addContainer(12,3000,0,glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*114.0f, (1.0f/255.0f)*37.0f, 1.0f));

    addContainer(11,3000,0,glm::vec4((1.0f/255.0f)*205.0f, (1.0f/255.0f)*50.0f, (1.0f/255.0f)*34.0f, 1.0f));

    addContainer(10,3000,0,glm::vec4((1.0f/255.0f)*205.0f, (1.0f/255.0f)*50.0f, (1.0f/255.0f)*34.0f, 1.0f));

    addContainer(9,6000,0,glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*114.0f, (1.0f/255.0f)*37.0f, 1.0f));

    addContainer(8,3000,0,glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*114.0f, (1.0f/255.0f)*37.0f, 1.0f));

    addContainer(2,3000,0,glm::vec4((1.0f/255.0f)*195.0f, (1.0f/255.0f)*7.0f, (1.0f/255.0f)*89.0f, 1.0f));

    addContainer(5,6000,0,glm::vec4((1.0f/255.0f)*12.0f, (1.0f/255.0f)*174.0f, (1.0f/255.0f)*50.0f, 1.0f));

    addContainer(3,3000,0,glm::vec4(0.0f, (1.0f/255.0f)*161.0f, (1.0f/255.0f)*221.0f, 1.0f));

    addContainer(1,6000,0,glm::vec4(0.0f, (1.0f/255.0f)*161.0f, (1.0f/255.0f)*221.0f, 1.0f));

    addContainer(4,3000,0,glm::vec4((1.0f/255.0f)*12.0f, (1.0f/255.0f)*174.0f, (1.0f/255.0f)*50.0f, 1.0f));

    addContainer(6,3000,0,glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*202.0f, (1.0f/255.0f)*54.0f, 1.0f));

    addContainer(7,6000,0,glm::vec4((1.0f/255.0f)*255.0f, (1.0f/255.0f)*202.0f, (1.0f/255.0f)*54.0f, 1.0f));

    addContainer(13,3000,0,glm::vec4((1.0f/255.0f)*70.0f, (1.0f/255.0f)*0.0f, (1.0f/255.0f)*0.0f, 1.0f));
}

void ParticleManager::removecLogo()
{
    for(std::vector<ParticleContainer*>::iterator i = _containerVec.begin(); i != _containerVec.end(); ++i)
    {
        ParticleContainer& container = **i;

        for(std::vector<Particle*>::iterator j = container._particleVec.begin(); j != container._particleVec.end(); ++j)
        {
            Particle& particle = **j;
            float rng = ((float) rand() / (RAND_MAX+1.0f));
            float R = 0;
            float xPos = 0;
            float yPos = 0;
            if( container.timePosition == 1 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.1) + 68;
                xPos = R * cosf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                yPos = R * sinf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
            }
            else if( container.timePosition == 2 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.3) + 44;
                xPos = R * cosf(3.1415926 * 0.5 * rng + 3.1415926 * 0.25);
                yPos = R * sinf(3.1415926 * 0.5 * rng + 3.1415926 * 0.25);
            }
            else if( container.timePosition == 3 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 2.2) - 3;
                xPos = R * cosf(3.1415926 * 0.53 * rng + 3.1415926 * 0.25);
                yPos = R * sinf(3.1415926 * 0.53 * rng + 3.1415926 * 0.25);
            }
            else if( container.timePosition == 4 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 2.2) + 9;
                xPos = R * cosf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
                yPos = R * sinf(3.1415926 * 0.3 * rng + 3.1415926 * 0.47);
            }
            else if( container.timePosition == 5 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.01) + 50;
                xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
            }
            else if( container.timePosition == 6 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.7) + 57;
                xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
                yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 0.77);
            }
            else if( container.timePosition == 7 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.08) + 68;
                xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
            }
            else if( container.timePosition == 8 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.2) + 36;
                xPos = R * cosf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
                yPos = R * sinf(3.1415926 * 0.23 * rng + 3.1415926 * 1.003);
            }
            else if( container.timePosition == 9 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.01) + 52;
                xPos = R * cosf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                yPos = R * sinf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
            }
            else if( container.timePosition == 10 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.7) + 58;
                xPos = R * cosf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
                yPos = R * sinf(3.1415926 * 0.22 * rng + 3.1415926 * 1.23);
            }
            else if( container.timePosition == 11 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.15) + 68;
                xPos = R * cosf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                yPos = R * sinf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
            }
            else if( container.timePosition == 12 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.9) + 28;
                xPos = R * cosf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
                yPos = R * sinf(3.1415926 * 0.25 * rng + 3.1415926 * 1.45);
            }
            else if( container.timePosition == 13 )
            {
                R = 40 * sqrt(((float) rand() / (RAND_MAX+1.0f)) + 0.2) + 48;
                xPos = R * cosf(3.1415926 * 0.19 * rng + 3.1415926 * 1.7);
                yPos = R * sinf(3.1415926 * 0.19 * rng + 3.1415926 * 1.7);
            }

            particle._targetPosition.at(0) = glm::vec3(container._position.x + xPos
                                                       , container._position.y + yPos + 150
                                                       , 1000.0f);
        }

    }
}

