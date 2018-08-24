#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include "qDebug"
#include <QTcpSocket>
#include <QThread>
#include "udpclient.h"


/**
 * @brief The TcpSocket class
 * 服务器 从客户端接收的tcpsocket
 *
 */

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket();

    static int baseID;
    static int GenerateID();

    void setSocketHANDEL(qintptr handle); //设置HANDLE接口

protected slots:
    void slot_onReadyRead();
    void slot_onDisconnect(); //tcp断开连接将 此线程关闭删除

private:
    QString Client_IP;
    int Client_udpPort;

    int server_udpPort;

signals :
    void OneUdpClient(udpClient * c);
    void tcpdisconnected();


};

#endif // TCPSOCKET_H
