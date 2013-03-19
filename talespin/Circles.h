#ifndef CIRCLES_H
#define CIRCLES_H

#include "Visualization.h"
#include "Circle.h"
#include <vector>

class Circles: public Visualization
{
public:
    Circles();

    void draw();
    void timeUpdate();

    Circle* addCircle(const int maxNumParticles, const glm::vec4 color);

private:
    typedef std::vector<Circle*> CircleCtrVector;
    CircleCtrVector _circleContainer;
};

#endif // CIRCLES_H
