#ifndef TANKDEADMSG_H
#define TANKDEADMSG_H

#include "Msg.h"
#include "tankclient.h"

class Msg;
class TankDeadMsg : public Msg
{
public:
    TankDeadMsg(TankClient *tc , const QJsonObject & obj);
    TankDeadMsg(int id);

private:
    int msgType = Msg::TANK_DEAD_MSG;
    int id;

    TankClient *tc;
    QJsonObject obj;

    // Msg interface
public:
    void sendMsg(NetClient *client, QString IP, int Port);
    void parse();
};

#endif // TANKDEADMSG_H
