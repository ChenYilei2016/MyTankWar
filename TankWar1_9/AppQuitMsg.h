#ifndef APPQUITMSG_H
#define APPQUITMSG_H

#include "Msg.h"
#include "tankclient.h"

/**
 * 玩家坦克程序退出的消息
 * 当有玩家退出、断开连接时 将它的坦克从游戏中删除
 */

class Msg;
class AppQuitMsg : public Msg
{
public:
    AppQuitMsg(int id);
    AppQuitMsg(TankClient *tc, QJsonObject & obj);

private:
    int msgType = Msg::APP_QUIT_MSG;
    int id;

    TankClient *tc;
    QJsonObject obj;
    // Msg interface
public:
    void sendMsg(NetClient *client, QString IP, int Port);
    void parse();
};

#endif // APPQUITMSG_H
