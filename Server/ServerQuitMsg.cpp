#include "ServerQuitMsg.h"
#include <QHostAddress>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


ServerQuitMsg::ServerQuitMsg(QObject *parent) : QObject(parent)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);

    doc.setObject(obj);
    quitbuf = doc.toJson(QJsonDocument::Compact);
}

void ServerQuitMsg::sendMsg(QUdpSocket *socket, udpClient *client)
{
    QString ip = client->IP;
    int port = client->udpPort;
    socket->writeDatagram(this->quitbuf,QHostAddress(ip),port );
}
