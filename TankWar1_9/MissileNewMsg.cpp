#include "MissileNewMsg.h"



MissileNewMsg::MissileNewMsg(TankClient *tc, const QJsonObject &obj)
{
    this->tc = tc;
    this->obj = obj;
}

MissileNewMsg::MissileNewMsg(Missile *m)
{
    this->mm = m;
}

void MissileNewMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    QJsonDocument doc;
    QJsonObject obj;

    obj.insert("msgtype",this->msgType);
    obj.insert("id",mm->getTankID());
    obj.insert("localid",mm->getLocalID());
    obj.insert("x",mm->getX());
    obj.insert("y",mm->getY());
    obj.insert("dir",(int)mm->getDir());
    obj.insert("good",(int)mm->getGood());
    doc.setObject(obj);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);

    client->sendMsg(buf,IP,Port);
}

void MissileNewMsg::parse()
{
    int id = obj.value("id").toInt();
    if(tc->mytank->getOneTankID() ==id )
    {
        return ;
    }

    int localid = obj.value("localid").toInt();
    int x =obj.value("x").toInt();
    int y =obj.value("y").toInt();
    Direction dir = (Direction)obj.value("dir").toInt();
    int good = obj.value("good").toInt();

    Missile * missile = new Missile(id,x,y,dir,tc);
    missile->setGood(good);
    missile->setLocalID(localid);

    tc->missiles.append(missile);

}
