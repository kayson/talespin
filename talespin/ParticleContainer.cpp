#include "ParticleContainer.h"
#include "QtOpenGL/QGLWidget"

ParticleContainer::ParticleContainer(const int numParticles, const glm::vec4 color)
    : _color(color)
{
    for(int i = 0; i <numParticles;i++)
    {
        _particleVec.push_back(new Particle());
    }
    fillParticleContainer();
}

ParticleContainer::~ParticleContainer()
{
    _particleVec.clear();
}

void ParticleContainer::fillParticleContainer()
{
    for(ParticleCtrVec::iterator i = _particleVec.begin(); i != _particleVec.end(); ++i)
    {
        Particle& particle = **i;
        float rng = 100;
        particle._position = glm::vec3(rng * (float) rand() / (RAND_MAX+1.0f)- rng * (float) rand() / (RAND_MAX+1.0f), rng * (float) rand() / (RAND_MAX+1.0f)- rng * (float) rand() / (RAND_MAX+1.0f),0.0f);
        particle._targetPosition.push_back(glm::vec3((float) rand() / (RAND_MAX+1.0f)-(float) rand() / (RAND_MAX+1.0f),(float) rand() / (RAND_MAX+1.0f)-(float) rand() / (RAND_MAX+1.0f),0.0f));
    }
}

void ParticleContainer::timeUpdateParticles()
{
    for(ParticleCtrVec::iterator i = _particleVec.begin(); i != _particleVec.end(); ++i)
    {
        Particle& particle = **i;
        
        particle._position +=  particle._velocity;
        if( glm::distance( particle._targetPosition.at(0),  particle._position ) > 0.1f)
        {
             particle._velocity += ( ( particle._targetPosition.at(0) -  particle._position) * 0.3f) / glm::distance( particle._targetPosition.at(0),  particle._position);
             particle._velocity *= 0.8f;
        }
        else
            particle._velocity *= 0.1f;
    }   
}

void ParticleContainer::drawParticles(float radius)
{	
    glPointSize(radius);
    glBegin(GL_POINTS);
    for(ParticleCtrVec::iterator i = _particleVec.begin(); i != _particleVec.end(); ++i)
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

