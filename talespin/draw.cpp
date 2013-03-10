#include "draw.h"

Draw::Draw(const QPointF &position) : position(position)
{
    //updateBrush();
}


void Draw::updateBrush()
{
    //brush = QBrush(Qt::white, Qt::SolidPattern);
}

void Draw::drawObject(QPainter *painter)
{
    QString text = "Tjenare Mannen!";

    painter->save();
    painter->translate(position.x(), position.y());
    //painter->setBrush(brush);
    painter->fillRect(QRect(0, 0, 150, 50),QColor(0, 0, 0, 50));
    painter->setPen(Qt::white);
    painter->drawText(0, 0, 255, 255, NULL, text);
    painter->restore();
}
