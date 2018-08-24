#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "global.h"
#include <QUdpSocket>
/**
 * @brief The NetClient class
 * 客户端
 */

//继承于 tcpsocket
class NetClient : public QTcpSocket
{
    Q_OBJECT
public:
    NetClient();

    int getListen_udp_Port() const;
    void setListen_udp_Port(int value);

    int getTankID() const;
    void setTankID(int value);

    //接口udp的监听
    bool udpListen();


    void sendMsg(QByteArray buf, QString IP, int Port);//发送消息

    //已经连接上了
    bool IsConnected(){if(udpsocket ==NULL){return false;}return true;}

    void closeALL();

protected slots:
    void slot_onReadyRead();
    void udpHasMsgFromServer();

    void testerror(QAbstractSocket::SocketError e);
signals:
    void HasMsgFromServer(QByteArray buf);

private:
    QUdpSocket * udpsocket =NULL;
    int listen_udp_Port;
    int tankID;
};

#endif // NETCLIENT_H
