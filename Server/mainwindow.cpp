#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include "qDebug"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QTcpSocket>
#include <QRegExp>
#include <QThread>


/**
 * 默认接收 tcp端口:8888
 * 默认接收 udp端口:6666
 */

 //3_2 建立自己的UDP 用来准备发送到client端口


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size() );

    this->setWindowTitle("TCP服务器");

    QRegExp tcp_regexp("\\d{4,5}");
    ui->tcp_listen_port->setValidator(new QRegExpValidator(tcp_regexp,this) );
    ui->udp_listen_port->setValidator(new QRegExpValidator(tcp_regexp,this) );
    ui->tcp_listen_port->setText("8888");
    ui->udp_listen_port->setText("6666");

    //监听按钮
    QObject::connect(ui->btn_listen,SIGNAL(clicked(bool)),this,SLOT(on_btn_listen()) );
    QObject::connect(ui->udp_listen_port,SIGNAL(textChanged(QString)),this,SLOT(on_enable_btn_listen_1()) );
    QObject::connect(ui->tcp_listen_port,SIGNAL(textChanged(QString)),this,SLOT(on_enable_btn_listen_2()) );

//    QJsonDocument doc;
//    QJsonObject obj;
//    obj.insert("udpport","2017");
//    doc.setObject(obj);
//    QString temp = doc.toJson(QJsonDocument::Compact);
//    qDebug()<<QThread::currentThreadId();


}

MainWindow::~MainWindow()
{
    delete ui;
}

//监听按钮的处理
void MainWindow::on_btn_listen()
{
    //保存 监听的tcp udp 端口
    tcpPort = ui->tcp_listen_port->text().toInt();
    udpPort = ui->udp_listen_port->text().toInt();

    if(ui->btn_listen->text() == "监听")
    {
        //创建一个server端
        server = new Server(ui->udp_listen_port->text().toInt() );
        QObject::connect(server,SIGNAL(udpBindFailed()),this,SLOT(slot_udpbindFailed()) );

        //server端监听
        if(! server->listen(QHostAddress::AnyIPv4, tcpPort) )
        {
            QMessageBox::warning(this,"error","tcp端口号:"+QString::number(tcpPort)+"已被占用!");
            return ;
        }

        ui->btn_listen->setText("取消监听");
    }
    else
    {
        //将服务器关闭
        server->closeALL();
        server = NULL;

        ui->btn_listen->setText("监听");
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //关闭的时候发送 退出消息
    if( NULL !=server )
    server->closeALL();
    else
    event->accept();
}

void MainWindow::on_enable_btn_listen_1()
{
    if(ui->udp_listen_port->text().isEmpty() || ui->tcp_listen_port->text().isEmpty())
    {
        ui->btn_listen->setEnabled(false);
    }
    else
    {
        ui->btn_listen->setEnabled(true);
    }
}

void MainWindow::on_enable_btn_listen_2()
{
    if(ui->udp_listen_port->text().isEmpty() || ui->tcp_listen_port->text().isEmpty())
    {
        ui->btn_listen->setEnabled(false);
    }
    else
    {
        ui->btn_listen->setEnabled(true);
    }
}

//udp绑定本地的port 失败的 处理
//因为是在同一台电脑运行多个客户端 所以udpport要变的。。。-->一个客户端有一个监听的udpsocket 来监听消息
void MainWindow::slot_udpbindFailed()
{
    QMessageBox::warning(this,"error","udp端口号:"+QString::number(udpPort)+"已被占用!");
    server->deleteLater();
    server = NULL;
}




