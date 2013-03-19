#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#define BARCHART 0
#define CIRCLES 1

class Visualization
{
public:
    Visualization();

    float radius;
    int columns;
    int spacing;

    void draw();
    void timeUpdate();
    void drawBars();
    void clearBars();
    int numBars();

    glm::vec4 getColorIndex(const int i);
    Bar* getContainer(const int n);
    Bar* addContainer(const int maxNumParticles, const glm::vec4 color);
    bool removeContainer(const int n);

    void update();

private:
    typedef std::vector<Bar*> VisualizationCtrVector;
    VisualizationCtrVector _visualizationContainer;
};

#endif // VISUALIZATION_H
