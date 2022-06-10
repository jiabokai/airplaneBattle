#include "bullet.h"

Bullet::Bullet()

{
    mObjectType = GameObject::OT_BulletPlayer;
}

Bullet::Bullet(QPoint _pos, QPixmap _pixmap, int _type)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->mBulletType = _type;
    this->mSpeed = 6;

    //子弹微调整
    this->setScale(0.5);//缩放
    this->setX(this->x() - this->scale()*pixmap().width()/2);

    PlaySound();


}

void Bullet::BulletMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
}

void Bullet::PlaySound()
{
    if(mBulletType == BT_Player){
        mMedia.setMedia(QUrl(""));//我方子弹声音
    }
    else if(mBulletType == BT_Enemy)
    {
         mMedia.setMedia(QUrl(""));//敌机子弹声音
    }

//    mMedia.play();在派生类中调用，此处就不用了

}

void Bullet::Init(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);

    //子弹微调整
    this->setScale(0.5);//缩放
    this->setX(this->x() - this->scale()*pixmap().width()/2);

    PlaySound();
}
