#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H

#include <QDebug>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QList>
#include <QMediaPlayer>
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include <QToolButton>
#include <QKeyEvent>
#include "playerbullet.h"
#include "enemybullet.h"


//游戏定义类  定义游戏相关属性
class GameDefine
{
    GameDefine();
public:

    static const int PlayerMoveUpdateTime = 20;
    static const int PlaneShootUpdateTime = 500;
    static const int EnemyMoveUpdateTime  = 20;
    static const int BulletMoveUpdateTime  = 10;
    static const int BackgroundUpdateTime  = 50;
    static const int EnemyCreateTime = 2000;

    //屏幕宽高
    static const int ScreenWidth  = 512;
    static const int ScreenHeight  = 768;

};

#endif // GAMEDEFINE_H
