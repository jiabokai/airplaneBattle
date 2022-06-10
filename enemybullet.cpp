#include "enemybullet.h"

EnemyBullet::EnemyBullet(QObject *parent)

{
    mObjectType = GameObject::OT_EnemyBullet;
}

void EnemyBullet::PlaySound()
{
    mMedia.setMedia(QUrl(""));//敌机子弹声音
    mMedia.play();
}
