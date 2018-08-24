#ifndef TANKMOVEMSG_H
#define TANKMOVEMSG_H

#include "Msg.h"
#include "tankclient.h"

/**
 * @brief The TankMoveMsg class
 *
 * 坦克移动、转动方向是发送消息
 */

class Msg;
class TankMoveMsg : public Msg
{
public:
    TankMoveMsg(int id, Direction dir,int x,int y);
    TankMoveMsg(TankClient * tc , const QJsonObject & obj);

private:
    int msgType = Msg::TANK_MOVE_MSG;
    int id;
    int x;
    int y;
    Direction dir;

    TankClient * tc;
    QJsonObject obj;

    // Msg interface
public:
    void sendMsg(NetClient *client, QString IP, int Port);
    void parse();


};

#endif // TANKMOVEMSG_H
