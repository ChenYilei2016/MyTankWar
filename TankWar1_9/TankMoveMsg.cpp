#include "TankMoveMsg.h"
#include <QList>
TankMoveMsg::TankMoveMsg(int id, Direction dir, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->dir = dir;
}

TankMoveMsg::TankMoveMsg(TankClient *tc, const QJsonObject &obj)
{
    this->tc = tc;
    this->obj = obj;
}

void TankMoveMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);
    obj.insert("id",this->id);
    obj.insert("x",this->x);
    obj.insert("y",this->y);
    obj.insert("dir",this->dir);
    doc.setObject(obj);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);

    client->sendMsg(buf,IP,Port);
}

void TankMoveMsg::parse()
{
    int id = obj.value("id").toInt();

    if( id == tc->mytank->getOneTankID())
    {
        return ;
    }
    else
    {
        bool exist =false;
        for(int i= 0 ;  i<tc->tanks.size();i++)
        {
            Tank * t = tc->tanks.at(i);
            if(id == t->getOneTankID() )
            {
                Direction dir = (Direction)obj.value("dir").toInt();
                int x = obj.value("x").toInt();
                int y = obj.value("y").toInt();
                t->setX(x);
                t->setY(y);
                t->setDir(dir);
                exist = true;
                break;
            }
        }

    }
}
