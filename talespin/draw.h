#ifndef DRAW_H
#define DRAW_H

#include <QPainter>

class Draw
{
public:
    Draw(const QPointF &position);
    static void drawObject(QPainter *painter);
    void updateBrush();

private:
    QBrush brush;
    QPointF position;
};

#endif // DRAW_H


