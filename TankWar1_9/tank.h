#ifndef TANK_H
#define TANK_H

//坦克对象

//每一个坦克都是一个对象

#include <QObject>
#include "global.h"
#include "tankclient.h"
#include "pt.h"
#include "Wall/Wall.h"

class TankClient;
class Pt;
class Tank : public QObject
{
    Q_OBJECT
private:
    //持有客户端的引用 可以对客户端进行一些操作
    TankClient * tc;//持有客户端的引用 可以对客户端进行一些操作

public:
    //坦克的位置 好坏属性
    explicit Tank(int x,int y,bool GOOD,QObject *parent = 0);


    void draw( QPainter & paint);//画出一辆坦克

    //键盘消息
    void keypress(QKeyEvent * e);//键盘消息
    void keyrelease(QKeyEvent *e);

    //移动
    void move();//移动
    void stay();//停止(返回上一步)

    //发射炮弹
    void fire(); //发射炮弹

    QRect getRect();

    bool getLive() const;
    void setLive(bool value);

    bool getGood() const;
    void setGood(bool value);

    bool hitWall(Wall * wall);
    bool hitTanks(QList<Tank*>tanks );

    int getOneTankID() const;
    void setOneTankID(int value);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    Direction getDir() const;
    void setDir(const Direction &value);

signals:

public slots:

private:
    void LocalDecided();

private:
    int step = 0 ;
    int x,y;
    int oldX,oldY;
    Direction oldDir;
    bool good;
    bool live = true;
    Pt * pt;//炮筒
    int oneTankID = 0;


    bool bL =false , bU = false,bD =false, bR = false;//斜的4个方向
    Direction dir = STOP;//坦克朝向
};

#endif // TANK_H
