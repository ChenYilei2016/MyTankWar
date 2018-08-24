#ifndef MISSILE_H
#define MISSILE_H

class Tank;

#include <QObject>
#include "global.h"
#include "tankclient.h"
#include "tank.h"
#include <Wall/Wall.h>

//子弹对象
class TankClient;
class Missile : public QObject
{
    Q_OBJECT
private:
    //子弹的位置 发射方向 谁发出来的子弹
    int x,y;
    Direction dir = D;

    //tankclient
    TankClient * tc;

    bool live = true;
    bool good ;
    int tankID;
    int localID;


public:
    explicit Missile(QObject *parent = 0);
    explicit Missile(int id, int x, int y, Direction d , TankClient * t, QObject *parent = 0);

    static int baseID;
    static int GenerateId();



    void draw(QPainter & paint);
    void move();
    bool Islive(){return live;}

    bool hitTank(Tank * tank);
    bool hitTanks(QList<Tank*> &list_tank);

    bool hitWall(Wall * wall );

    QRect getRect();

    bool getGood() const;
    void setGood(bool value);

    void setLive(bool value);

    bool getLive() const;

    int getLocalID() const;
    void setLocalID(int value);

    int getTankID() const;
    void setTankID(int value);

    Direction getDir() const;
    void setDir(const Direction &value);

    int getX() const;

    int getY() const;

signals:

public slots:
};

#endif // MISSILE_H
