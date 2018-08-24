#ifndef WALL_H
#define WALL_H

#include <QObject>
#include "global.h"

class Wall
{
private:
    int x,y,w,h;

public:
    Wall(int x,int y,int w,int h);

    void draw(QPainter & paint);
    QRect getRect();

};

#endif // WALL_H
