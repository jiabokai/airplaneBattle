#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include <QObject>
#include "gamedefine.h"
#include "widget.h"
/*
当对象被频繁创建或删除时，大量使用new和delete关键字
处理堆内存  如果该对象比较大，则对计算机的消耗就越大，很有
可能在创建大量对象时出现卡顿情况，频繁的创建和删除对计算机消耗
比较大

对象缓存池：对象缓存池  预先缓存一定数量的对象，对象需要被使用时
直接从对象池中获取对象 能有效的解决在创建时导致的卡顿问题。
在对象需要被销毁时，不销毁对象将其会受到对象缓存池中，循环利用从而解决对
计算机的消耗。

(简单来说就是 游戏对象的循环利用）
*/

class GameObjectPool : public QObject
{
    //单例模式
    GameObjectPool(QObject *parent = nullptr);
    static GameObjectPool* instance;//要在cpp文件中进行初始化
public:
    static GameObjectPool* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new GameObjectPool(Widget::widget);
        }
        return instance;
    }

    //对象池初始化 缓存对象
    void Init();

    //获取对象
    GameObject* GetGameObject(int _objectType);

    //对象回收
    void RecoveryGameObject(GameObject* _object);

    //内存清除
    void Clear();

    ~GameObjectPool();



//    Bullet* CreateBullet();
//    Enemy* CreateEnemy();

protected:
    //玩家子弹对象池容器
    QList<PlayerBullet*> mBulletPool;

    //敌机对象池容器
    QList<Enemy*> mEnemyPool;



};

#endif // GAMEOBJECTPOOL_H
