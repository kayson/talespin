#ifndef VISUALIZATIONNANAGER_H
#define VISUALIZATIONNANAGER_H

#include "Visualization.h"
#include <vector>

class VisualizationManager
{
public:
    VisualizationManager();
    void draw();
    void timeUpdate();

    void add(Visualization* newVis);

private:
    typedef std::vector<Visualization*> VisualizationCtrVector;
    VisualizationCtrVector _visualizationContainer;
};

#endif // VISUALIZATIONNANAGER_H
