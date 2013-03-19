#ifndef VISUALIZATION_H
#define VISUALIZATION_H

class Visualization
{
public:
    Visualization();

    virtual void draw()=0;
    virtual void timeUpdate()=0;
};

#endif // VISUALIZATION_H
