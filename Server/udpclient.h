#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>

class udpClient : public QObject
{
    Q_OBJECT
public:
    explicit udpClient(QString IP,int port,int oneID,QObject *parent = 0);
public:

    QString IP;
    int udpPort;

    //唯一ID
    int oneID;

signals:

public slots:
};

#endif // UDPCLIENT_H
