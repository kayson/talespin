#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm.hpp>

class Circle
{
public:
    Circle(const int numParticles, const glm::vec4 color);
    void timeUpdateParticles();
    void drawParticles(float radius);

    float radius;
    glm::vec4 color;
};

#endif // CIRCLE_H
