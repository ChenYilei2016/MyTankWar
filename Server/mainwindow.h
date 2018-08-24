#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QTcpServer>
#include "TcpSocket.h"
#include "QCloseEvent"

#include "server.h"

/**
 *
 * 主页面类
 */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Server * server = NULL;
    int tcpPort;
    int udpPort;
public slots:
    void on_btn_listen(); //按钮
    void on_enable_btn_listen_1();//按钮可否使用
    void on_enable_btn_listen_2();//按钮可否使用
    void slot_udpbindFailed();




    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
