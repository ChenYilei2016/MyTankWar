#include "udpclient.h"


udpClient::udpClient(QString IP, int port, int oneID, QObject *parent)
{
    this->IP = IP;
    this->udpPort = port;
    this->oneID = oneID;
}
