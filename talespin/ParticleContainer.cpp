#include "ParticleContainer.h"
#include "QtOpenGL/QGLWidget"

ParticleContainer::ParticleContainer(const int newID, EntityType inEntity, const int timePos, const int numParticles, const glm::vec4 color)
    : ID(newID)
    , entity(inEntity)
    , timePosition(timePos)
    , _color(color)
    , _numParticles(numParticles)
{
    _position = glm::vec3( 150.0f, 150.0f,0.0f);
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

        float d = glm::distance( particle._targetPosition.at(0),  particle._position );
        if( d > 20.0f)
        {
             particle._velocity += ( ( particle._targetPosition.at(0) -  particle._position) * 0.9f) / d;
             particle._velocity *= 0.9f;
        }
        else if( d > 5.0f)
        {
             particle._velocity += ( ( particle._targetPosition.at(0) -  particle._position) * 0.3f) / d;
             particle._velocity *= 0.7f;
        }
        else if( d > 0.05f)
        {
            particle._velocity += ( ( particle._targetPosition.at(0) -  particle._position) * 0.1f) / d;
            particle._velocity *= 0.5f;
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

int ParticleContainer::getNumParticles()
{
    return _numParticles;
}

