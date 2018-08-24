#include "tank.h"

Tank::Tank(int x, int y, bool GOOD, QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y;
    oldX = x;
    oldY = y;
    this->good = GOOD;
    tc = static_cast<TankClient *>(parent);
    pt = new Pt(x,y,this);
    pt->setDir(D);
    srand(time(0));
}

void Tank::draw( QPainter &paint) //坦克的画法
{
    if(!live)
        return ;

    if( 0 ==this->oneTankID %2)
    {
        paint.setBrush(QBrush(QColor(255,0,0)));
    }
    else
    {
        paint.setBrush(QBrush(QColor(0,0,255)));
    }

    //服务器给的唯一ID
    paint.drawText(this->x-TANK_WIDTH/2,this->y-TANK_HEIGHT/2-1,"id:"+QString::number(oneTankID) );

    //当前的x，y然后画个椭圆
    paint.drawEllipse(QPoint(x,y),15,15);
    pt->draw(paint);
    move();

}

void Tank::keypress(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return ;
    const int key = event->key();
    if( key== Qt::Key_Up)
    {
        bU = true;
        LocalDecided();
    }
    else if(key == Qt::Key_Down)
    {
        bD = true;
        LocalDecided();
    }
    else if(key == Qt::Key_Left)
    {
        bL = true;
        LocalDecided();
    }
    else if(key == Qt::Key_Right)
    {
        bR = true;
        LocalDecided();
    }

    //if(bU || bD || bL || bR) IsPress = true;


}

void Tank::keyrelease(QKeyEvent *e)
{
    if(e->isAutoRepeat())
        return ;

    const int key = e->key();
    switch(key)
    {
        case Qt::Key_Up:
            bU = false;
            LocalDecided();
            break;
        case Qt::Key_Down:
            bD = false;
            LocalDecided();
            break;
        case Qt::Key_Left:
            bL = false;
            LocalDecided();
            break;
        case Qt::Key_Right:
            bR = false;
            LocalDecided();
            break;
        case Qt::Key_W: //w 发射炮弹
            fire();
            break;
        default:
            break;
    }

    //if(!bU &&!bD &&!bL && !bR) IsPress = false;

}

void Tank::move()
{
    oldX = x;
    oldY = y;

    switch(dir)
    {
    case L:
        x -=XSPEED;
        break;
    case LU:
        x-= XSPEED;
        y-= YSPEED;
        break;
    case U:
        y-= YSPEED;
        break;
    case RU:
        x+= XSPEED;
        y-= YSPEED;
        break;
    case R:
        x+= XSPEED;
        break;
    case RD:
        x+= XSPEED;
        y+= YSPEED;
        break;
    case D:
        y+= YSPEED;
        break;
    case LD:
        x-= XSPEED;
        y+= YSPEED;
        break;
    case STOP:
        break;
    }

//    if(!good)
//    {
//        if(0 == step)
//        {
//            dir = Direction(rand()%8);
//            step =  rand()%15+3;
//        }

//        if( 0 ==step % 10)
//        {
//            this->fire();
//        }

//        step--;
//    }

    //移动炮筒
    pt->move(x,y,dir);

    if(x<15)x=15;
    if(y<15)y=15;
    if(x+TANK_WIDTH/2>GAME_WIDTH) x = GAME_WIDTH-TANK_WIDTH/2;
    if(y+TANK_HEIGHT/2>GAME_HEIGHT) y = GAME_HEIGHT-TANK_HEIGHT/2;

}

void Tank::stay()
{
    this->x = oldX;
    this->y = oldY;
}

void Tank::fire()
{
    if(!this->getLive())
        return ;

    Missile * m = new Missile(this->getOneTankID(),x,y,pt->getDir(),tc,this);
    m->setGood(this->good);
    tc->missiles.push_back(m);

    if(tc->netclient != NULL && tc->netclient->IsConnected() )
    {
        MissileNewMsg msg(m); //发送一个子弹产生的消息
        tc->sendMsg(&msg);
    }


    return ;
}

QRect Tank::getRect()
{
    return QRect(x-TANK_WIDTH/2,y-TANK_HEIGHT/2,TANK_WIDTH,TANK_HEIGHT);
}

void Tank::LocalDecided()
{
        oldDir = this->getDir();

        if(bL && !bU && ! bR && !bD)
        {
            dir = L;
        }
        else if(bL && bU && ! bR && !bD)
        {
            dir = LU;
        }
        else if(!bL && bU && ! bR && !bD)
        {
            dir = U;
        }
        else if(!bL && bU && bR && !bD)
        {
            dir = RU;
        }
        else if(!bL && !bU &&  bR && !bD)
        {
            dir = R;
        }
        else if(!bL && !bU &&  bR && bD)
        {
            dir = RD;
        }
        else if(!bL && !bU && ! bR && bD)
        {
            dir = D;
        }
        else if( bL && !bU && ! bR && bD)
        {
            dir = LD;
        }
        else if(!bL && !bU && ! bR && !bD)
        {
            dir = STOP;
        }

        //改变方向的时候 发送一个消息
        if(tc->netclient != NULL)
        {
            if(oldDir != this->dir)
            {
                if(tc->netclient->IsConnected()&& this->getLive())
                {
                    TankMoveMsg msg(this->oneTankID,this->dir,this->x,this->y);
                    tc->sendMsg(&msg);

                }
            }

        }


}

Direction Tank::getDir() const
{
    return dir;
}

void Tank::setDir(const Direction &value)
{
    dir = value;
}

int Tank::getY() const
{
    return y;
}

void Tank::setY(int value)
{
    y = value;
}

int Tank::getX() const
{
    return x;
}

void Tank::setX(int value)
{
    x = value;
}

int Tank::getOneTankID() const
{
    return oneTankID;
}

void Tank::setOneTankID(int value)
{
    oneTankID = value;
}

bool Tank::getGood() const
{
    return good;
}

void Tank::setGood(bool value)
{
    good = value;
}

bool Tank::hitWall(Wall *wall)
{
    if(!this->live)return false;

    if(wall->getRect().intersects(this->getRect()) )
    {
        this->stay();
        //this->dir =(Direction)(rand()%8);
        return true;
    }
    return false;
}

bool Tank::hitTanks(QList<Tank *> tanks)
{
    QList<Tank*>::iterator ite = tanks.begin();

    for(auto & ite : tanks )
    {
        Tank * t=  ite;
        if(t->getRect().intersects(this->getRect()) && t!= this)
        {
            t->stay();
            this->stay();
            return true;
        }
    }

    return false;
}

bool Tank::getLive() const
{
    return live;
}

void Tank::setLive(bool value)
{
    live = value;
}


