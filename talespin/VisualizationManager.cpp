#include "VisualizationManager.h"

VisualizationManager::VisualizationManager()
{
}

void VisualizationManager::draw()
{
    for(VisualizationCtrVector::iterator i = _visualizationContainer.begin(); i != _visualizationContainer.end(); ++i)
    {
        Visualization& container = **i;
        container.draw();
    }
}

void VisualizationManager::timeUpdate()
{
    for(VisualizationCtrVector::iterator i = _visualizationContainer.begin(); i != _visualizationContainer.end(); ++i)
    {
        Visualization& container = **i;
        container.timeUpdate();
    }
}

void VisualizationManager::add(Visualization* newVis)
{
    _visualizationContainer.push_back(newVis);
}
