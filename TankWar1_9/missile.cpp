#include "missile.h"
#include "Explode.h"

int Missile::baseID = 1000;
int Missile::GenerateId()
{
    return baseID++;
}

bool Missile::getGood() const
{
    return good;
}

void Missile::setGood(bool value)
{
    good = value;
}

void Missile::setLive(bool value)
{
    live = value;
}

bool Missile::getLive() const
{
    return live;
}

int Missile::getLocalID() const
{
    return localID;
}

void Missile::setLocalID(int value)
{
    localID = value;
}

int Missile::getTankID() const
{
    return tankID;
}

void Missile::setTankID(int value)
{
    tankID = value;
}

Direction Missile::getDir() const
{
    return dir;
}

void Missile::setDir(const Direction &value)
{
    dir = value;
}

int Missile::getX() const
{
    return x;
}

int Missile::getY() const
{
    return y;
}

Missile::Missile(QObject *parent) : QObject(parent)
{

}

Missile::Missile(int id,int x, int y, Direction d, TankClient *t, QObject *parent)
:QObject(parent)
{
    this->x = x;
    this->y = y;
    dir = d;
    tc = t;
    this->tankID = id;
    this->localID = GenerateId(); //本地子弹的ID
}

void Missile::draw(QPainter &paint)
{
    if(!live) //子弹死亡则返回
    {
        return ;
    }

    QBrush b = paint.brush();
    paint.setBrush(Qt::black);
    paint.drawEllipse(QPoint(x,y),MWIDTH/2,MHEIGHT/2 );
    paint.setBrush(b);

    move();
}

void Missile::move()
{
    switch(dir)
    {
    case L:
        x -= XMSPEED;
        break;
    case LU:
        x-= XMSPEED;
        y-= YMSPEED;
        break;
    case U:
        y-= YMSPEED;
        break;
    case RU:
        x+= XMSPEED;
        y-= YMSPEED;
        break;
    case R:
        x+= XMSPEED;
        break;
    case RD:
        x+= XMSPEED;
        y+= YMSPEED;
        break;
    case D:
        y+= YMSPEED;
        break;
    case LD:
        x-= XMSPEED;
        y+= YMSPEED;
        break;
    }

    if(x<0 || y<0 ||x> GAME_WIDTH || y>GAME_HEIGHT)
    {
        live = false;
    }

}

bool Missile::hitTank(Tank *tank)
{
    if( this->getGood()!=tank->getGood()&&this->getRect().intersects(tank->getRect()) &&Islive() && tank->getLive())
    {
        this->live = false;
        tank->setLive(false);

        Explode * e = new Explode(x,y,tc);
        tc->explodes.append(e);

        return true;
    }
    return false;
}

bool Missile::hitTanks(QList<Tank *> & list_tank)
{
    QList<Tank *>::iterator ite = list_tank.begin();
    for(ite ;ite!= list_tank.end() ;ite++)
    {
        if( this->hitTank( (*ite) ) )
        {
            return true;
        }
    }
    return false;
}

bool Missile::hitWall(Wall *wall)
{
    if(!live) return false;

    if(this->getRect().intersects(wall->getRect()) )
    {
        this->setLive(false);
        return true;
    }
    return false;

}



QRect Missile::getRect()
{
    return QRect(x-MWIDTH/2,y-MHEIGHT,MWIDTH,MHEIGHT);
}
