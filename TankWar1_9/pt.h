#ifndef PT_H
#define PT_H

#include <QObject>
#include "global.h"
#include "tank.h"

/**
 * @brief The Pt class
 * 炮筒类
 */

 //画坦克上的炮筒的 意义不大

class Pt : public QObject
{
    Q_OBJECT
private:
    int x,y;
    Direction dir = D;//默认初始化 炮筒朝下

public:
    explicit Pt(int x,int y,QObject *parent = 0);

    Direction getDir() const;
    void setDir(const Direction &value);

    void draw(QPainter & paint);
    void move(int xx,int yy,Direction d);

signals:

public slots:
};

#endif // PT_H
