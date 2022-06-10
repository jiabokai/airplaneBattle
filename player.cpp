#include "player.h"

Player::Player()

{
    QPixmap airPlanePixmap = QPixmap(":/Image/airplane.jpg");
    //如何修改图片大小？如何根据窗口改变而改变？
    airPlanePixmap= airPlanePixmap.scaled(100,100,Qt::KeepAspectRatio);//将pixmap进行缩放
    this->setPixmap(QPixmap(airPlanePixmap));


    this->setPos(256,500);
    mMoveSpeed = 5;
    mShootSpeed = 200;
}
