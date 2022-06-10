#include "playerbullet.h"

PlayerBullet::PlayerBullet(QObject *parent)

{
    mObjectType = GameObject::OT_BulletPlayer;
    mSpeed = 6;
}

void PlayerBullet::PlaySound()
{
    mMedia.setMedia(QUrl(""));//我方子弹声音
    mMedia.play();
}


