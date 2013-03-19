#include "Circles.h"
#include "QtOpenGL/QGLWidget"

Circles::Circles()
{
}

void Circles::draw()
{
    glBegin(GL_QUADS);
    for(CircleCtrVector::iterator i = _circleContainer.begin(); i != _circleContainer.end(); ++i)
    {
        Circle& container = **i;
        glColor4fv( &container.color[0] );

        glVertex3f(30.0f, 30.0f, 0.0f);
        glVertex3f(30.0f + container.radius, 30.0f, 0.0f);
        glVertex3f(30.0f + container.radius, 30.0f + container.radius, 0.0f);
        glVertex3f(30.0f, 30.0f + container.radius, 0.0f);

    }
     glEnd();
}

void Circles::timeUpdate()
{

}

Circle* Circles::addCircle(const int maxNumParticles, const glm::vec4 color)
{
    Circle* newContainer = new Circle(maxNumParticles, color);
    _circleContainer.push_back(newContainer);
    return newContainer;
}
