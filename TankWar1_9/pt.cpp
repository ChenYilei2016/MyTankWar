#include "pt.h"


Direction Pt::getDir() const
{
    return dir;
}

void Pt::setDir(const Direction &value)
{
    dir = value;
}

void Pt::draw(QPainter &paint)
{
    QPen p = paint.pen();
    paint.setPen(QColor(Qt::black));

    switch(dir)
    {
    case L:
        paint.drawLine(x, y, x-TANK_WIDTH/2, y);
        break;
    case LU:
        paint.drawLine(x, y, x-TANK_WIDTH/2, y-TANK_HEIGHT/2);
        break;
    case U:
        paint.drawLine(x, y, x, y-TANK_HEIGHT/2);
        break;
    case RU:
        paint.drawLine(x, y, x+TANK_WIDTH/2, y-TANK_HEIGHT/2);
        break;
    case R:
        paint.drawLine(x, y, x+TANK_WIDTH/2, y);
        break;
    case RD:
        paint.drawLine(x, y, x+TANK_WIDTH/2, y+TANK_HEIGHT/2);
        break;
    case D:
        paint.drawLine(x, y, x, y+TANK_HEIGHT/2);
        break;
    case LD:
        paint.drawLine(x, y, x-TANK_WIDTH/2, y+TANK_HEIGHT/2);
        break;
    }

    paint.setPen(p);

}

void Pt::move(int xx, int yy, Direction d)
{
    x = xx;
    y = yy;
    if(d != STOP)
    dir = d;
}

Pt::Pt(int x, int y, QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y;
}
