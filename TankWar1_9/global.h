//包含大多数常量
#ifndef GLOBAL_H
#define GLOBAL_H

//游戏中的场量 和公用的工具头文件

//游戏场景宽高
extern  const int GAME_WIDTH;
extern  const int GAME_HEIGHT;

//坦克的移动速度
extern  const int XSPEED ;
extern  const int YSPEED ;

//子弹的移动速度
extern const int XMSPEED ;
extern const int YMSPEED ;

//坦克宽度
extern const int TANK_WIDTH ;
extern const int TANK_HEIGHT ;

//子弹宽高
extern const int MWIDTH;
extern const int MHEIGHT;


//坦克方向 用了一个 枚举表示 8个方向
enum Direction{L,LU,U,RU,R,RD,D,LD,STOP};

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPoint>
#include <QKeyEvent>
#include <QList>
#include <QRect>
#include <QRectF>
#include <time.h>
#include "connect_dialog.h"
#include <QHostAddress>
#include <QMessageBox>


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QSound>
#include <QMediaPlayer>


class Global
{
public:
    Global();

public:
    //背景音乐 暂时关了。
    QMediaPlayer *tankDead;

};

#endif // GLOBAL_H
