#include "tankclient.h"
#include "ui_tankclient.h"
#include <QDebug>
#include <QKeyEvent>

#include "runthread.h"


TankClient::TankClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TankClient)
{
    ui->setupUi(this);
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //线程刷新
//    runthread = new RunThread(this);
//    QObject::connect(runthread,SIGNAL(repaintSignals()),this,SLOT(repaint()) );
//    runthread->start();

    //定时器定时刷新
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()) );
    timer->start(40);

       //联网不需要;
//    for(int i=0 ;i<10 ;i++)
//    {
//        Tank *tt = new Tank(50+i*50,100,false,this);
//        tanks.append(tt);
//    }

    mytank = new Tank(15,200,true,this);
    w1 = new Wall(200,200,30,180);
    w2 = new Wall(300,400,250,30);

}

TankClient::~TankClient()
{
    delete ui;
}

void TankClient::paintEvent(QPaintEvent *event)
{


    QPainter paint;

    paint.begin(this);
    paint.fillRect(this->rect(),QColor(Qt::green) );

    paint.drawText(15,15,"missile:"+QString::number(missiles.size()));
    paint.drawText(15,30,"explode:"+QString::number(explodes.size()));
    paint.drawText(15,45,"tanks:"+QString::number(tanks.size()));

    /**
     * 画出所有子弹 并将非法子弹删除
     *
     * 全部坦克打自己客户端的坦克 如果死了就发送坦克死亡消息
     */
    for(int i= 0 ;i<missiles.size() ;i++)
    {
        Missile * mm =  missiles.at(i);
       // mm->hitTanks(tanks);

       if(mm->hitTank(mytank))
       {
            TankDeadMsg msg(this->mytank->getOneTankID());
            this->sendMsg(&msg);

            MissileDeadMsg msg2(mm->getTankID(),mm->getLocalID());
            this->sendMsg(&msg2);
       }
        mm->hitWall(w1);
        mm->hitWall(w2);

        mm->draw(paint);
    }
    QList<Missile*>::iterator ite = missiles.begin();
    for(;ite!= missiles.end() ;)
    {
        if((*ite)->Islive() )
        {
            ite++;
        }
        else
        {
            delete *ite;
            ite = missiles.erase(ite);
        }
    }

     /**
     * 画出所有爆炸 并将非法爆炸删除
     */
    for(int i =0; i<explodes.size();i++)
    {
        Explode * e = explodes.at(i);
        e->draw(paint);
    }
    QList<Explode*>::iterator ite2 = explodes.begin();
    for(;ite2!= explodes.end() ;)
    {
        if((*ite2)->getLive() )
        {
            ite2++;
        }
        else
        {
            delete *ite2;
            ite2 = explodes.erase(ite2);
        }
    }

     /**
     * 画出所有敌军 并将die坦克删除
     */
    for(int i =0; i<tanks.size();i++)
    {
        Tank *t = tanks.at(i);

        t->hitWall(w1);
        t->hitWall(w2);
        t->hitTanks(tanks);

        t->draw(paint);
    }
    QList<Tank*>::iterator ite3 = tanks.begin();
    for(;ite3!= tanks.end() ;)
    {
        if((*ite3)->getLive() )
        {
            ite3++;
        }
        else
        {
            delete *ite3;
            ite3 = tanks.erase(ite3);
        }
    }


    //画出自己的坦克
    if(mytank && mytank->getLive() )
    {
        mytank->draw(paint);
        mytank->hitWall(w1);
        mytank->hitWall(w2);
    }

    w1->draw(paint);
    w2->draw(paint);

    paint.end();
}

void TankClient::NetClient_KeyPress(QKeyEvent * event)
{
    //如果按键Q 则跳出对话框来创建 网络连接
    if(netclient == NULL )
    {
        int key = event->key();
        if(key == Qt::Key_Q ) //按键为Q弹出连接的 对话框
        {
            Connect_Dialog * dlg = new Connect_Dialog(this);
            int check  = dlg->exec();

            if(QDialog::Accepted == check)
            {
                //获得 对话框中输入的消息
                serverIP = dlg->getServerIP();
                serverTcpPort   = dlg->getServerPort();
                serverUdpPort  = dlg->getServerUdpPort();
                int client_udp_listen_port = dlg->getClientUdp_listen_Port();
                this->client_udp_listen_port = client_udp_listen_port;

                qDebug()<<"will connect:"<<serverIP<<"-"<<serverTcpPort;

                //从对话框中取得了ip 和port 创建连接
                netclient = new NetClient();
                netclient->connectToHost(QHostAddress(serverIP),serverTcpPort); //tcp连接到服务器

                if( !netclient->waitForConnected(300) ) //等待300ms 连接失败
                {
                    qDebug()<<"connect failed!";
                    QMessageBox::warning(this,"error","连接失败,请检查IP和Port输入是否正确!");

                    netclient->deleteLater();
                    netclient = NULL;
                    return ;
                }
                else//连接成功
                {
                    qDebug()<<"connect successful!";

                    //先向它发出我们监听的udp端口号
                    QByteArray buf = QString::number(client_udp_listen_port).toLatin1();
                    netclient->write(buf);

                    if(netclient->waitForReadyRead(1000))
                    {
                        //客户端建立监听的udp
                        netclient->setListen_udp_Port(client_udp_listen_port);

                        //tcp连接已经没用断开 tcp只用于发出自身信息
                        netclient->disconnectFromHost();
                        //udp端口重叠绑定失败
                        if( !netclient->udpListen() ) //自己创建的udpsocket监听消息
                        {

                            netclient->deleteLater();
                            netclient =NULL;
                            return ;
                        }

                        //对客户端的坦克 分配ID good
                        this->tankID = netclient->getTankID();
                        qDebug()<<"client tankID:"<<tankID;
                        mytank->setOneTankID(tankID);

                        if( 0 ==this->tankID %2 )
                            mytank->setGood(true);
                        else
                            mytank->setGood(false);

                        QObject::connect(netclient,SIGNAL(HasMsgFromServer(QByteArray))
                        ,this,SLOT(udpHasMsgFromServer(QByteArray)) );

                        //当客户端第一次连接上服务器的时候  将自己客户端的坦克的 各种情况发送给服务器
                        //将初始自己的坦克的信息发送
                        TankNewMsg msg(mytank);
                        this->sendMsg(&msg);
                    }

                }


            }

        }
    }
}

//特意发送到默认 IP 端口号的接口
void TankClient::sendMsg(Msg * msg)
{

    msg->sendMsg(this->netclient,serverIP,serverUdpPort); //默认服务器的IP与端口号
}

void TankClient::slot_keypress(QKeyEvent *event)
{
    mytank->keypress(event);

    //如果按键Q 则跳出对话框来创建 网络连接
    NetClient_KeyPress(event);
}

void TankClient::slot_keyrelease(QKeyEvent *event)
{
    mytank->keyrelease(event);
}


/** Important
 * @brief TankClient::udpHasMsgFromServer
 * @param buf
 *
 * udp监听端口 接收到了 server的消息 进行解析!!!
 */
void TankClient::udpHasMsgFromServer(QByteArray buf)
{
    qDebug()<<"udpHasMsgFromServer:"<<buf;
    QJsonDocument doc = QJsonDocument::fromJson(buf);
    QJsonObject obj = doc.object();
    int msgType = obj.value("msgtype").toInt();

    Msg * msg = NULL;
    switch(msgType)
    {
    case Msg::SERVER_QUIT_MSG: //服务器退出 客户端应该初始化~~
        MsgToServerDisconnected();
        break;
    case Msg::TANK_NEW_MSG:
        msg = new TankNewMsg(this,obj);
        msg->parse();
        break;
    case Msg::TANK_MOVE_MSG:
        msg = new TankMoveMsg(this,obj);
        msg->parse();
        break;
    case Msg::MISSILE_NEW_MSG:
        msg = new MissileNewMsg(this,obj);
        msg->parse();
        break;
    case Msg::TANK_DEAD_MSG:
        msg = new TankDeadMsg(this,obj);
        msg->parse();
        break;
    case Msg::MISSILE_DEAD_MSG:
        msg = new MissileDeadMsg(this,obj);
        msg->parse();
        break;
    case Msg::APP_QUIT_MSG:
        msg = new AppQuitMsg(this,obj);
        msg->parse();
        break;

    default:
        break;
    }

    delete msg;

}

void TankClient::MainWindow_CloseAccept()
{
    qDebug()<<__FUNCTION__;

    if(netclient!= NULL && netclient->IsConnected())
    {
        AppQuitMsg msg(this->mytank->getOneTankID());
        msg.sendMsg(netclient,serverIP,serverUdpPort);
    }
    return ;
}


//清空所有 坦克 爆炸 子弹 将自己的坦克初始化位置
//将netclient 初始化
void TankClient::MsgToServerDisconnected()
{
    QList<Missile*>::iterator ite = missiles.begin();
    for(;ite!= missiles.end() ;)
    {
        delete *ite;
        ite = missiles.erase(ite);
    }

    QList<Explode*>::iterator ite2 = explodes.begin();
    for(;ite2!= explodes.end() ;)
    {
        delete *ite2;
        ite2 = explodes.erase(ite2);
    }

    QList<Tank*>::iterator ite3 = tanks.begin();
    for(;ite3!= tanks.end() ;)
    {
        delete *ite3;
        ite3 = tanks.erase(ite3);

    }

    mytank->setLive(true);
    mytank->setX(15);
    mytank->setY(200);
    mytank->setOneTankID(0);

    netclient->closeALL();
    netclient =NULL;

    QMessageBox::information(this,"error","服务器已经失去连接!");
}

