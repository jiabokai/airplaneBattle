#ifndef PLANE_H
#define PLANE_H

#include "gameobject.h"

class Plane : public GameObject
{

public:
    explicit Plane(QObject *parent = nullptr);

protected:
    float mMoveSpeed;
    int mShootSpeed;
};

#endif // PLANE_H
