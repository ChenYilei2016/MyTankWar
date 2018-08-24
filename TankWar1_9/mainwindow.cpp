#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include "global.h"
#include <windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    this->setWindowTitle("TankWar-按Q连接服务器-按W发射子弹!↑↓←→移动");

    //测试 背景音乐关闭
    Global * g= new Global();
   // g->tankDead->play();

    //创建坦克游戏widget
    tankclient = new TankClient();

    QObject::connect(this,SIGNAL(keypressSignal(QKeyEvent*)),tankclient,SLOT(slot_keypress(QKeyEvent*)) );
    QObject::connect(this,SIGNAL(keyreleaseSignal(QKeyEvent*)),tankclient,SLOT(slot_keyrelease(QKeyEvent*)) );


    QObject::connect(this,SIGNAL(closeAccept()),tankclient,SLOT(MainWindow_CloseAccept()));

    this->setCentralWidget(tankclient);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    emit keypressSignal(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    emit keyreleaseSignal(e);
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("是否真的要关闭窗口?");
    msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes)
    {
        emit closeAccept();

        Sleep(25);
        event->accept();
    }
    else
    {
        event->ignore();
    }


}
