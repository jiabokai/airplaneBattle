#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QMediaPlayer>
class GameObject : public QGraphicsPixmapItem
{

public:
    enum ObjectType
    {
        OT_BulletPlayer,
        OT_Enemy,
        OT_Player,
        OT_EnemyBullet
    };

    explicit GameObject(QObject *parent = nullptr);

    int GetType()
    {
        return mObjectType;
    }

    //对象回收
    void GameObjectDelete(QGraphicsScene* _scene);

    //统计对象构造和析构
    static int createCount;

    ~GameObject()
    {

        qDebug()<<"当前释放"+QString::number(createCount--)+"个对象";
    }

protected:
    int mObjectType;
};

#endif // GAMEOBJECT_H
