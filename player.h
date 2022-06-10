#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem
{

public:
    explicit Player();
    float mMoveSpeed;
    int mShootSpeed;

};

#endif // PLAYER_H
