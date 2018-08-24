#include "server.h"
#include <QHostAddress>
#include "qDebug"
#include "ServerQuitMsg.h"

Server::Server(int udp_listen_port)
{
    this->udp_listen_port = udp_listen_port;

    listen_udp_socket = new QUdpSocket(this);

    if(  !listen_udp_socket->bind(udp_listen_port) )//udp绑定失败
    {
        emit udpBindFailed();
    }


    QObject::connect(listen_udp_socket,SIGNAL(readyRead()),this,SLOT(slot_On_UdpHasMSG()) );
}

void Server::incomingConnection(qintptr handle)
{
    qDebug()<<__FUNCTION__;

    //将client的IP地址传入 tcpsocket
    TcpSocket * socket = new TcpSocket();
    socket->setSocketHANDEL(handle);

    //连接的tcp传发 udpClient 进行管理
    QObject::connect(socket,SIGNAL(OneUdpClient(udpClient*)),
                     this,SLOT(slot_On_relpyOneUdpClient(udpClient*)) );

    //当有tcp连接的时候 开辟一个新的线程处理
    QThread * tcpThread = new QThread();
    socket->moveToThread(tcpThread);
    tcpThread->start();

    QObject::connect(socket,SIGNAL(tcpdisconnected()),tcpThread,SLOT(quit()) );
    QObject::connect(socket,SIGNAL(tcpdisconnected()),tcpThread,SLOT(deleteLater()) );

}

void Server::slot_On_relpyOneUdpClient(udpClient *client)
{
    clients.append(client);
}

void Server::SendMsg(QByteArray &buf, udpClient* client)
{
      QString IP = client->IP;
      int Port   = client->udpPort;
      listen_udp_socket->writeDatagram(buf,QHostAddress(IP),Port);
}

void Server::closeALL()
{
    //发送退出消息
    QList<udpClient *>::iterator ite = clients.begin();
    for( ;ite != clients.end() ; ite++ )
    {
        ServerQuitMsg msg;
        msg.sendMsg(this->listen_udp_socket, *ite);
    }

    this->listen_udp_socket->close();
    this->close();

    this->deleteLater();
}

void Server::slot_On_UdpHasMSG()
{
    /**test
     *     QHostAddress a;
           quint16 p ;
    */

    //server端对消息的处理是 转发给所有的客户端 客户端进行过滤

    //UDP先接收所有消息
    QByteArray buf;
    buf.resize( listen_udp_socket->pendingDatagramSize());
    listen_udp_socket->readDatagram(buf.data(),buf.size());

    QJsonDocument doc = QJsonDocument::fromJson(buf);
    QJsonObject obj = doc.object();
    int msg = obj.value("msgtype").toInt();

    //如果是客户端退出消息 将客户端从链表中删除
    if( 100 == msg )
    {
        int id = obj.value("id").toInt();

        QList<udpClient *>::iterator ite = clients.begin();
        for( ;ite != clients.end() ;  )
        {
            if( (*ite)->oneID ==id  )
            {
                delete *ite;
                ite = clients.erase(ite);
            }
            else
            {
                ite++;
            }
        }
    }

    qDebug()<<"resend to all Person MSG:" << buf;
    int id = obj.value("id").toInt();
    //由server 转发至所有 client
    QList<udpClient *>::iterator ite = clients.begin();
    for( ;ite != clients.end() ; ite++ )
    {
       // if(id != (*ite)->oneID )
       // {
            this->SendMsg(buf,*ite);
       // }

    }
}
















