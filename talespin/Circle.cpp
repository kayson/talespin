#include "Circle.h"

Circle::Circle(const int numParticles, const glm::vec4 color)
    : color(color)
{
    radius = (float)numParticles;
}
