#include "TcpSocket.h"
#include <QHostAddress>
#include <QDebug>

// 给客户端的唯一ID 每给一次之后++
int TcpSocket::baseID = 100;
int TcpSocket::GenerateID()
{
    return baseID++;
}

void TcpSocket::setSocketHANDEL(qintptr handle)
{
    this->setSocketDescriptor(handle);

    this->Client_IP = this->peerAddress().toString();
    qDebug()<<"IP:"<<Client_IP<<"Tcpjoin";
}

TcpSocket::TcpSocket()
{
    setParent(0);

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(slot_onReadyRead()) );
    QObject::connect(this,SIGNAL(disconnected()),this,SLOT(slot_onDisconnect()) );
}

void TcpSocket::slot_onReadyRead()
{
    qDebug()<<"one Client useTcp connect";

    //TCP: 1.先接收客户端tcp的udp监听端口号
    QByteArray buf = this->readAll();
    Client_udpPort = buf.toInt();

    //TCP: 2.将服务器端生成的唯一ID发送
    int oneid = GenerateID();
    QByteArray dataID = QString::number(oneid).toLatin1();
    this->write(dataID);

    //UDP: 创建udp的连接并保存以便以后转发 转发至sever端
    udpClient * udpclient = new udpClient(Client_IP,Client_udpPort,oneid);
    emit OneUdpClient(udpclient);

}

void TcpSocket::slot_onDisconnect()
{
    this->deleteLater();
    emit tcpdisconnected();
}
