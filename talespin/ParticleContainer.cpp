#include "ParticleContainer.h"
#include "QtOpenGL/QGLWidget"

ParticleContainer::ParticleContainer(const int numParticles, const glm::vec4 color)
    : _color(color)
{
    for(int i = 0; i <numParticles;i++)
    {
        _particleVector.push_back(new Particle());
    }
    fillContainer();
}

ParticleContainer::~ParticleContainer()
{
    _particleVector.clear();
}

void ParticleContainer::fillContainer()
{
    for(ParticleVector::iterator i = _particleVector.begin(); i != _particleVector.end(); ++i)
    {
        Particle& particle = **i;
        float rng = 100;
        particle._position = glm::vec3(rng * (float) rand() / (RAND_MAX+1.0f)- rng * (float) rand() / (RAND_MAX+1.0f), rng * (float) rand() / (RAND_MAX+1.0f)- rng * (float) rand() / (RAND_MAX+1.0f),0.0f);
        particle._targetPosition = glm::vec3((float) rand() / (RAND_MAX+1.0f)-(float) rand() / (RAND_MAX+1.0f),(float) rand() / (RAND_MAX+1.0f)-(float) rand() / (RAND_MAX+1.0f),0.0f);
    }
}

void ParticleContainer::timeUpdateParticles()
{
    for(ParticleVector::iterator i = _particleVector.begin(); i != _particleVector.end(); ++i)
    {
        Particle& particle = **i;
        
        particle._position +=  particle._velocity;
        if( glm::distance( particle._targetPosition,  particle._position) > 0.1f)
        {
             particle._velocity += ( ( particle._targetPosition -  particle._position) * 0.1f) / glm::distance( particle._targetPosition,  particle._position);
        }
        particle._velocity *= 0.9f;
    }   
}

void ParticleContainer::drawParticles(float radius)
{	
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

glm::vec4 ParticleContainer::getColor()
{
    return _color;
}
