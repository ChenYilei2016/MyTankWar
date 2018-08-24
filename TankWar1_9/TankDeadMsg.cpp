#include "TankDeadMsg.h"

TankDeadMsg::TankDeadMsg(TankClient *tc, const QJsonObject &obj)
{
    this->tc = tc;
    this->obj = obj;
}

TankDeadMsg::TankDeadMsg(int id)
{
    this->id = id;
}

void TankDeadMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    QJsonDocument doc ;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);
    obj.insert("id",this->id);
    doc.setObject(obj);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);

    client->sendMsg(buf,IP,Port);
}

void TankDeadMsg::parse()
{
    int id = obj.value("id").toInt();
    for(int i= 0;i< tc->tanks.size() ; i++)
    {
        Tank * t = tc->tanks.at(i);
        if(id == t->getOneTankID())
        {
            t->setLive(false);
            Explode * e = new Explode(t->getX(),t->getY());//加入爆炸
            tc->explodes.append(e);

            break;
        }
    }
}
