#ifndef MISSILENEWMSG_H
#define MISSILENEWMSG_H

#include <QObject>

#include "Msg.h"
#include "tankclient.h"
#include "missile.h"

#include "global.h"
/**
 * @brief The MissileNewMsg class
 * 产生一发子弹的消息
 */
class Missile;
class MissileNewMsg : public Msg
{
public:
    MissileNewMsg(TankClient *tc ,const QJsonObject & obj);
    MissileNewMsg(Missile * m);

private:
    int msgType = Msg::MISSILE_NEW_MSG;


    Missile *mm = NULL;
    TankClient *tc;
    QJsonObject obj;


    // Msg interface
public:
    void sendMsg(NetClient *client, QString IP, int Port);
    void parse();

};

#endif // MISSILENEWMSG_H
