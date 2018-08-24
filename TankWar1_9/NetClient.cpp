#include "NetClient.h"
#include <QMessageBox>
#include <QHostAddress>

NetClient::NetClient()
{
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(slot_onReadyRead()) );
    QObject::connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(testerror(QAbstractSocket::SocketError)) );
}

void NetClient::slot_onReadyRead()
{
    QByteArray buf = this->readAll();

    qDebug()<<"netclientID:"<<buf.toInt();
    tankID = buf.toInt();
}

void NetClient::udpHasMsgFromServer()
{
    //转发给tankclient
    QByteArray buf;
    int length =udpsocket->pendingDatagramSize();
    buf.resize(length);

    udpsocket->readDatagram(buf.data(),length);
    emit HasMsgFromServer(buf);
}

void NetClient::testerror(QAbstractSocket::SocketError e)
{
    qDebug()<<this->errorString();
}

int NetClient::getTankID() const
{
    return tankID;
}

void NetClient::setTankID(int value)
{
    tankID = value;
}

bool NetClient::udpListen()
{
    qDebug()<<__FUNCTION__;

    udpsocket = new QUdpSocket();

    //TODO:安全
    if(! udpsocket->bind(listen_udp_Port) )
    {

        qDebug()<<"udp bind failed!";
        QMessageBox::warning(NULL,"error","连接失败,请检查Udp监听Port输入是否正确!");
        udpsocket->deleteLater();
        udpsocket = NULL;
        return false ;
    }
    qDebug()<<"udpsocket bind successful!";

    QObject::connect(udpsocket,SIGNAL(readyRead()),this,SLOT(udpHasMsgFromServer()) );
    return true;
}

void NetClient::sendMsg(QByteArray buf,QString IP, int Port)
{
    qDebug()<<__FUNCTION__<<":"<<buf;
    udpsocket->writeDatagram(buf,QHostAddress(IP),Port ); //发送到之前保存过的服务器的ip 和 udp端口号
}

void NetClient::closeALL()
{
    if(this->udpsocket != NULL)
    {
        this->udpsocket->close();
    }

    this->close();
    this->deleteLater();
}

int NetClient::getListen_udp_Port() const
{
    return listen_udp_Port;
}

void NetClient::setListen_udp_Port(int value)
{
    listen_udp_Port = value;
}
