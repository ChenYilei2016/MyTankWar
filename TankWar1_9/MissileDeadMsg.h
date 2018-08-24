#ifndef MISSILEDEADMSG_H
#define MISSILEDEADMSG_H

#include "Msg.h"
#include "tankclient.h"

/**
 *
 *
 */
class Msg;
class MissileDeadMsg : public Msg
{
public:
    MissileDeadMsg(TankClient *tc, const QJsonObject &obj);
    MissileDeadMsg(int id,int localid);


private:
    int msgType = Msg::MISSILE_DEAD_MSG;
    int id; //哪个坦克发射的
    int localid ;//子弹的本地ID

    TankClient *tc;
    QJsonObject obj;

    // Msg interface
public:
    void sendMsg(NetClient *client, QString IP, int Port);
    void parse();
};

#endif // MISSILEDEADMSG_H
