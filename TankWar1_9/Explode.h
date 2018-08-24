#ifndef EXPLODE_H
#define EXPLODE_H

#include <QObject>
#include "global.h"
#include "tankclient.h"
/**
 * @brief The explode class
 * 爆炸类
 */

class Explode : public QObject
{
    Q_OBJECT
public:
    explicit Explode(int x,int y,TankClient *parent = 0);
    void draw(QPainter & paint);
    bool getLive() const;
    void setLive(bool value);

protected:
    static int diameter[]; //爆炸的圆心


signals:

public slots:

private:
    int x,y;
    int step =0;
    bool live = true;
    TankClient *tc;

};

#endif // EXPLODE_H
