#ifndef CONNECT_DIALOG_H
#define CONNECT_DIALOG_H

#include <QDialog>

namespace Ui {
class Connect_Dialog;
}

class Connect_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Connect_Dialog(QWidget *parent = 0);
    ~Connect_Dialog();

    QString getServerIP() const;
    void setServerIP(const QString &value);

    int getServerPort() const;
    void setServerPort(int value);

    int getClientUdp_listen_Port() const;
    void setClientUdp_listen_Port(int value);

    int getServerUdpPort() const;
    void setServerUdpPort(int value);

protected slots:
    void myAccept();

private:
    Ui::Connect_Dialog *ui;
    QString serverIP;
    int serverTcpPort;
    int serverUdpPort;
    int clientUdp_listen_Port;
};

#endif // CONNECT_DIALOG_H
