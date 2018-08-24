#include "Explode.h"

//爆炸产生的半径 从小到大 从大到小 然后消失
int Explode::diameter[10] ={4,7,12,18,26,32,49,30,14,6};

Explode::Explode(int x, int y, TankClient *t)
{
    this->x = x;
    this->y = y;
    tc = t;
}

void Explode::draw(QPainter &paint)
{
    if(!live) return;

    QBrush b = paint.brush();
    paint.setBrush(QColor(Qt::yellow ) );
    paint.drawEllipse(QPoint(x,y),diameter[step]/2,diameter[step]/2 );
    step++;

    if(step ==  sizeof(diameter)/sizeof(int) )
    {
        step= 0;
        this->live =false;
    }

    paint.setBrush(b);
}

bool Explode::getLive() const
{
    return live;
}

void Explode::setLive(bool value)
{
    live = value;
}
