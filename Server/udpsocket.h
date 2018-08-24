#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

class UdpSocket : public QUdpSocket
{
public:
    UdpSocket(int udpPort);

private:
    //发送到client的端口处
    int udpPort;

};

#endif // UDPSOCKET_H
