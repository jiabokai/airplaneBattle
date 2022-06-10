#include "enemy.h"


Enemy::Enemy(QPoint _pos, QPixmap _pixmap)
{
    this->mMoveSpeed = 3;
    this->mShootSpeed = 1000;
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->setScale(0.5);//图片缩放
}

void Enemy::EnemyMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mMoveSpeed,_dir.y()*mMoveSpeed);
}

void Enemy::Init(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->setScale(0.5);//图片缩放

    this->mMoveSpeed = 3;
    this->mShootSpeed = 1000;
}
