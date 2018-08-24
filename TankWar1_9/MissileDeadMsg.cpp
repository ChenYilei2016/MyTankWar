#include "MissileDeadMsg.h"

MissileDeadMsg::MissileDeadMsg(TankClient *tc, const QJsonObject &obj)
{
    this->tc = tc;
    this->obj = obj;
}

MissileDeadMsg::MissileDeadMsg(int id, int localid)
{
    this->id = id;
    this->localid = localid;
}

void MissileDeadMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);
    obj.insert("id",this->id);
    obj.insert("localid",this->localid);
    doc.setObject(obj);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);

    client->sendMsg(buf,IP,Port);
}

void MissileDeadMsg::parse()
{
    int id = obj.value("id").toInt();
    for(int i = 0;i<tc->missiles.size() ;i++ )
    {
        Missile * temp = tc->missiles.at(i);
        if(id == temp->getTankID())
        {
            int localid = obj.value("localid").toInt();
            if(localid == temp->getLocalID())
            {
                temp->setLive(false);
                return ;
            }
        }
    }
}
