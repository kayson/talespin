#ifndef BARCHART_H
#define BARCHART_H

#include "Visualization.h"
#include "Bar.h"
#include <vector>

class BarChart: public Visualization
{
public:   
    BarChart();
    ~BarChart();

    float radius;
    int columns;
    int spacing;

    void draw();
    void timeUpdate();
    void drawBars();
    void clearBars();
    int numBars();

    glm::vec4 getColorIndex(const int i);
    Bar* getBar(const int n);
    Bar* addBar(const int maxNumParticles, const glm::vec4 color);
    bool removeBar(const int n);

    void update();

private:
    typedef std::vector<Bar*> BarCtrVector;
    BarCtrVector _barContainer;
};

#endif
