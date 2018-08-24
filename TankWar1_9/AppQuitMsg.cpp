#include "AppQuitMsg.h"

AppQuitMsg::AppQuitMsg(int id)
{
    this->id = id;
}

AppQuitMsg::AppQuitMsg(TankClient *tc, QJsonObject &obj)
{
    this->obj = obj;
    this->tc = tc;
}

void AppQuitMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);
    obj.insert("id",this->id);
    doc.setObject(obj);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    client->sendMsg(buf,IP,Port);
}

void AppQuitMsg::parse()
{
    int id = obj.value("id").toInt();
    for(int i= 0;i<tc->tanks.size() ;i++ )
    {
        Tank * t = tc->tanks.at(i);
        if(id == t->getOneTankID() )
        {
            t->setLive(false);
            break;
        }
    }
}
