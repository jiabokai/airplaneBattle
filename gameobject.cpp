#include "gameobject.h"
#include <QGraphicsScene>
#include "gameobjectpool.h"

int GameObject::createCount = 0;

GameObject::GameObject(QObject *parent)

{
    createCount++;
    qDebug()<<"当前创建"+QString::number(createCount)+"个对象";
}

void GameObject::GameObjectDelete(QGraphicsScene* _scene)
{
    _scene->removeItem(this);//场景移除
    GameObjectPool::Instance()->RecoveryGameObject(this);//回收对象

}
