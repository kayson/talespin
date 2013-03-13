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
    painter->save();

//    painter->fillRect(10,10,50,50,QColor(255,128,255,255));
//    painter->drawText(10, 10, 50, 50, NULL, QString("1000"));

//    painter->fillRect(10,80,50,50,QColor(255,128,0,255));
//    painter->drawText(10, 80, 50, 50, NULL, QString("1250"));

//    painter->fillRect(10,150,50,50,QColor(0,255,128,255));
//    painter->drawText(10, 150, 50, 50, NULL, QString("1060"));

//    painter->setPen(QColor(255,255,255,255));
//    painter->drawLine(0,50,1337,50);

    painter->restore();
}
