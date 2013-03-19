#include "Visualization.h"
#include <algorithm>
#include <iostream>

Visualization::Visualization()
{
}

Visualization::~Visualization()
{
    for(VisualizationCtrVector::iterator i = _visualizationContainer.begin(); i != _visualizationContainer.end(); ++i)
    {
        Container* const container = *i;
        delete container;
    }
    _barContainer.clear();
}

void BarChart::timeUpdate()
{
    for(BarCtrVector::iterator i = _barContainer.begin(); i != _barContainer.end(); ++i)
    {
        Bar& container = **i;
        container.timeUpdateParticles();
    }
}


void BarChart::draw()
{
    for(BarCtrVector::iterator i = _barContainer.begin(); i != _barContainer.end(); ++i)
    {
        Bar& container = **i;
        container.drawParticles(radius);
    }

    glPointSize(radius);
    glBegin(GL_POINTS);
    for(ParticleVector::iterator i = _particleVector.begin(); i != _particleVector.end(); ++i)
    {
        Particle& particle = **i;
        glColor4fv( &_color[0] );
        glVertex3fv( &particle._position[0] );
    }
    glEnd();
}

Bar* BarChart::addBar(const int maxNumParticles, const glm::vec4 color)
{
    Bar* newContainer = new Bar(maxNumParticles, color);
    _barContainer.push_back(newContainer);
    return newContainer;
}

glm::vec4 BarChart::getColorIndex(const int i)
{
    Bar* container = getBar(i);
    return container->getColor();
}

int BarChart::numBars()
{
    return _barContainer.size();
}

void BarChart::clearBars()
{
    _barContainer.clear();
}

Bar* BarChart::getBar(const int n)
{
    if(_barContainer.size() > n)
        return _barContainer.at(n);
    else
        return false;
}

bool BarChart::removeBar(const int n)
{
    if(_barContainer.size() < n)
        return false;

    _barContainer.erase(_barContainer.begin()+n);
    return true;

}

void BarChart::update()
{
    float n = 0;

    for(BarCtrVector::iterator i = _barContainer.begin(); i != _barContainer.end(); ++i,n++)
    {
        Bar& container = **i;
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
            particle._targetPosition.at(0) = glm::vec3(c + n*columns + n*spacing , r, 0.0f);
        }
    }
}

