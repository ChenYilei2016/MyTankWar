#include "Wall.h"

Wall::Wall(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Wall::draw(QPainter &paint)
{
    paint.save();

    paint.setBrush(Qt::black);
    paint.drawRect(x,y,w,h);

    paint.restore();
}

QRect Wall::getRect()
{
    return QRect(x,y,w,h);
}

