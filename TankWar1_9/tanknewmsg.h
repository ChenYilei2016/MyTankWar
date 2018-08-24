#ifndef TANKNEWMSG_H
#define TANKNEWMSG_H

#include "Msg.h"
class Tank;
class Msg;


#include "tankclient.h"
#include "tank.h"


#include <QObject>



class TankNewMsg : public Msg
{
public:
    TankNewMsg(Tank *tank); //传入坦克 用于发送构造

    TankNewMsg(TankClient *tc,const QJsonObject& obj ); //传入管家 用于解析改变

    // Msg interface
public:
    void sendMsg(NetClient* client,QString IP, int Port)override;
    void parse() override ;

private:
    int msgType = Msg::TANK_NEW_MSG ; //初始消息 坦克诞生
    int tankID;
    int tankX;
    int tankY;
    int Good;
    Direction dir;

    TankClient * tc;
    QJsonObject obj;

};

#endif // TANKNEWMSG_H
