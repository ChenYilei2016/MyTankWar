#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "TcpSocket.h"
#include "udpclient.h"
#include <QThread>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(int udp_listen_port );


    void SendMsg(QByteArray &buf,udpClient *client);//转发消息

    //关闭服务器
    void closeALL();

    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
signals:
    void udpBindFailed();

protected slots:
    //有udpclient 接收 加入保存管理
    void slot_On_relpyOneUdpClient(udpClient * client);
    void slot_On_UdpHasMSG();

private:
    int udp_listen_port; //udp监听号

    //监听客户端消息
    QUdpSocket * listen_udp_socket;
    QList<udpClient *> clients;

};

#endif // SERVER_H
