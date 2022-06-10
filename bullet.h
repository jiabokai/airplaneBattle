#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"


class Bullet : public GameObject
{
public:
   enum BulletType
   {
       BT_Player,//我方
       BT_Enemy//敌方
   };

public:
    Bullet();
    Bullet(QPoint _pos,QPixmap _pixmap,int _type);

    //初始化函数
    void Init(QPoint _pos,QPixmap _pixmap);


    //移动函数
    void BulletMove(QPoint _dir = QPoint(0,-1));//默认方向向上
    void PlaySound();

    ~Bullet()
    {
        qDebug()<<"子弹被释放";
    }
protected:

    int mBulletType;
    int mSpeed;

    QMediaPlayer mMedia;






};

#endif // BULLET_H
