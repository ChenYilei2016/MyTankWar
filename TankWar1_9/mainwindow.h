#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tankclient.h"

/**
 *主窗口
 *这里的窗口 全是用代码画的。
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

protected:


private:
    Ui::MainWindow *ui;
    TankClient * tankclient;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * e);

signals:
    void keypressSignal(QKeyEvent * event);
    void keyreleaseSignal(QKeyEvent *event);

    void closeAccept();

protected:

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
