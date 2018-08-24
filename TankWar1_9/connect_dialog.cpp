#include "connect_dialog.h"
#include "ui_connect_dialog.h"

#include <QRegExp>

Connect_Dialog::Connect_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect_Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QRegExp reg("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    QRegExp reg2("[0-9]{1,5}");
    ui->line_ip->setValidator(new QRegExpValidator(reg)  );
    ui->line_port->setValidator(new QRegExpValidator(reg2)  );
    ui->line_server_udp_port->setValidator(new QRegExpValidator(reg2));
    ui->client_udp_listen_port->setValidator( new QRegExpValidator(reg2) );

    QObject::connect(ui->btn_ok,SIGNAL(clicked(bool)),this,SLOT(myAccept()) );
}

Connect_Dialog::~Connect_Dialog()
{
    delete ui;
}

QString Connect_Dialog::getServerIP() const
{
    return serverIP;
}

void Connect_Dialog::setServerIP(const QString &value)
{
    serverIP = value;
}

int Connect_Dialog::getServerPort() const
{
    return serverTcpPort;
}

void Connect_Dialog::setServerPort(int value)
{
    serverTcpPort = value;
}

void Connect_Dialog::myAccept()
{
    serverIP = ui->line_ip->text();
    serverTcpPort = ui->line_port->text().toInt();
    serverUdpPort = ui->line_server_udp_port->text().toInt();
    clientUdp_listen_Port = ui->client_udp_listen_port->text().toInt();
    this->accept();
}

int Connect_Dialog::getServerUdpPort() const
{
    return serverUdpPort;
}

void Connect_Dialog::setServerUdpPort(int value)
{
    serverUdpPort = value;
}

int Connect_Dialog::getClientUdp_listen_Port() const
{
    return clientUdp_listen_Port;
}

void Connect_Dialog::setClientUdp_listen_Port(int value)
{
    clientUdp_listen_Port = value;
}
