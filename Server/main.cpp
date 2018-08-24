#include "mainwindow.h"
#include <QApplication>

//规划

//TCP 连接  UDP 传输
//1.9.1 修改Dir 去掉敌人坦克

//1.9.2 建立server  建立client
//用tcp连接然后断开
//server 储存udplist
//独一无二ID

//1.9.4 多个人 发送坦克诞生 序列化坦克消息 发送消息

//1.9.4.2  服务端转发packet  udp客户端起线程接受

//1.9.5 坦克移动消息 （方向改变发消息） 多态封装

//1.9.6 修正TankNewmsg 让后加入的可以看见全部坦克

//1.9.7 自动生成唯一UDP端口

//1.9.8 子弹NEW

//1.9.9 根据ID 决定好坏  打自己
//坦克死掉的消息

//1.99.1 子弹死亡的消息

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
