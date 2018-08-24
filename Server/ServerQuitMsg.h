#ifndef SERVERQUITMSG_H
#define SERVERQUITMSG_H

#include <QObject>
#include <QUdpSocket>
#include <udpclient.h>
#include <QJsonObject>

/**
 * @brief The ServerQuitMsg class
 * 服务器关闭 所有 客户端 初始化消息
 */

class ServerQuitMsg : public QObject
{
    Q_OBJECT
public:
    explicit ServerQuitMsg(QObject *parent = 0);

    void sendMsg(QUdpSocket * socket, udpClient * client);

private:
    int msgType = -1;
    QByteArray quitbuf;

signals:

public slots:
};

#endif // SERVERQUITMSG_H
