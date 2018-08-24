#include "global.h"
/**
 * @brief GAME_WIDTH
 * global类
 */

extern  const int GAME_WIDTH = 800;
extern  const int GAME_HEIGHT = 600;

extern  const int XSPEED = 5;
extern  const int YSPEED = 5;

//子弹的移动速度
extern const int XMSPEED = 10;
extern const int YMSPEED = 10;

extern const int TANK_WIDTH = 30;
extern const int TANK_HEIGHT = 30;

extern const int MWIDTH = 10;
extern const int MHEIGHT = 10;

Global::Global()
{
    tankDead = new QMediaPlayer();
    tankDead->setVolume(75);
    tankDead->setMedia(QUrl("qrc:/sound/sounds/back.mp3") );

}
