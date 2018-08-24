#include "tanknewmsg.h"
#include "tank.h"

TankNewMsg::TankNewMsg(Tank *tank)
{

    //传入一辆坦克 保存它的信息
    this->tankID = tank->getOneTankID();
    this->tankX  = tank->getX();
    this->tankY  = tank->getY();
    this->dir    = tank->getDir();
    this->Good   = tank->getGood();

}

TankNewMsg::TankNewMsg(TankClient *tc,const QJsonObject& obj)
{
    this->tc = tc;
    this->obj = obj;
}

/**
 * @brief TankNewMsg::sendMsg
 * @param IP
 * @param Port
 * 包装成QJson 发送出去  别的客户端也利用QJson 解析
 */
void TankNewMsg::sendMsg(NetClient *client, QString IP, int Port)
{
    //将坦克的信息打包成json 易于发送
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("msgtype",this->msgType);
    obj.insert("id",this->tankID);
    obj.insert("x",this->tankX);
    obj.insert("y",this->tankY);
    obj.insert("dir",(int)this->dir);
    obj.insert("good",this->Good);
    doc.setObject(obj);

    QByteArray buf = doc.toJson(QJsonDocument::Compact);

    //发送消息！
    client->sendMsg(buf,IP,Port);

}

void TankNewMsg::parse()
{
    int id = obj.value("id").toInt();

    //不接收自己的消息了~~
    if( id == tc->mytank->getOneTankID() )
    {
        return ;
    }

    //先寻找在不在客户端中 不在的话加入 并且将自己的再发出去 让互相看见
    bool exist = false;
    for(int i = 0 ;i<tc->tanks.size() ;i++)
    {
        Tank * getT = tc->tanks.at(i);
        if(getT->getOneTankID() == id )
        {
            exist = true;
            break;
        }
    }

    if(! exist  )
    {
        int x = obj.value("x").toInt();
        int y = obj.value("y").toInt();
        int dir = obj.value("dir").toInt();
        bool good = obj.value("good").toInt();
        Tank * t = new Tank(x,y,good);
        t->setDir( (Direction)dir );
        t->setOneTankID(id);
        tc->tanks.append(t);

        if(tc->mytank->getLive())
        {
              TankNewMsg tanknewmsg( tc->mytank);
              tc->sendMsg(&tanknewmsg);
        }


    }


}
