#ifndef MSG_H
#define MSG_H

#include <QObject>
#include "NetClient.h"

/**
 * @brief The Msg class
 *
 * 抽象基类
 * 用于各种消息的继承
 * 包含 发送 和 解析 2个虚方法
 *
 */

class Msg
{
    //基类的一些常量 用于表示接收的 数据包的类型
public:
    const static int SERVER_QUIT_MSG = -1; //服务器退出的消息

    const static int TANK_NEW_MSG = 1; //新加入了一个坦克
    const static int TANK_MOVE_MSG = 2;//坦克移动了
    const static int MISSILE_NEW_MSG = 3;//发射出了一个子弹
    const static int TANK_DEAD_MSG = 4; //有坦克死了
    const static int MISSILE_DEAD_MSG = 5;//有子弹死了
    const static int APP_QUIT_MSG = 100;//有客户端退出 将这个客户端的坦克删除



    explicit Msg(){;}

    //每个消息都有2个方法 一个发送 一个解析
    virtual void sendMsg(NetClient* client,QString IP, int Port) = 0;
    virtual void parse() = 0;

signals:

public slots:
};

#endif // MSG_H
