#ifndef TANKCLIENT_H
#define TANKCLIENT_H

#include <QWidget>
#include <QPainter>
#include <QTimer>


#include "runthread.h"
#include "tank.h"
#include "missile.h"
#include "Explode.h"
#include "Wall/Wall.h"

#include "NetClient.h"

#include "Msg.h"

#include "tanknewmsg.h"
#include "TankMoveMsg.h"
#include "MissileNewMsg.h"
#include "TankDeadMsg.h"
#include "MissileDeadMsg.h"
#include "AppQuitMsg.h"

#include "global.h"

class RunThread;
namespace Ui {
class TankClient;
}

/**
 *
 * 客户端的核心
 * 所有的东西 都往这里面加 在这里面储存 然后画出来
 *
 */


class Missile;
class Explode;
class TankClient : public QWidget
{
    Q_OBJECT

    //private 容器存储 游戏东西
public:
    friend class Missile;
    friend class Explode;
    friend class Tank;
    QList<Missile*>missiles; //子弹链表
    QList<Explode*>explodes;//爆炸效果的链表
    QList<Tank*>   tanks;//坦克的链表  --> 别的客户端的坦克

    //2堵墙
    Wall * w1 =NULL ;
    Wall * w2 =NULL ;

    //每个客户端自己的坦克
    Tank * mytank =NULL;
private:
    NetClient * netclient =NULL; //客户端的socket -->用来连接服务器的 也是进行消息接收的


public:
    explicit TankClient(QWidget *parent = 0);
    ~TankClient();

    void sendMsg(Msg * msg);

private:
    Ui::TankClient *ui;
    //RunThread * runthread =NULL ;

//接收 服务器的信息 发送消息的时候  可以发送给服务器
     QString serverIP ;
     int serverTcpPort   ;
     int serverUdpPort;

protected:
    void paintEvent(QPaintEvent *event); //画画面（核心）
    void NetClient_KeyPress(QKeyEvent *event);

    void MsgToServerDisconnected();

protected slots:
    void slot_keypress(QKeyEvent * event);
    void slot_keyrelease(QKeyEvent *event);
    void udpHasMsgFromServer(QByteArray buf);

    //窗口即将关闭 发送退出消息
    void MainWindow_CloseAccept();


    // QWidget interface
protected:
    QTimer * timer =NULL;
    int client_udp_listen_port;
    int tankID;



};

#endif // TANKCLIENT_H
