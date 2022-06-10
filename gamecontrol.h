#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "gamedefine.h"
#include "widget.h"


class GameControl : public QObject
{
    //单例
    GameControl(QWidget* parent = nullptr);
    static GameControl* instance;
public:
    //获取单例
    static GameControl* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new GameControl(Widget::widget);
        }
        return instance;
    }
    //析构
    ~GameControl()
    {
//        if(instance !=nullptr)
//        {
//            delete instance;

//        }
//        instance = nullptr;
    }

    //游戏初始化
    void GameInit();
    void LoadStartScene();//加载开始场景
    void LoadGameScene();//加载游戏场景

    //游戏逻辑定时器开始
    void GameStart();

    //游戏逻辑定时器关闭
    void GameOver();

    //背景移动
    void BGMove();
    //飞机移动函数
    void PlaneMove();

    //我机子弹生成函数
    void PlaneBulletShoot();
    //敌机生成
    void CreateEnemy();
    //碰撞检测
    void Collision();

    //huoqu按键
    QList<int> mKeyList;//按键组合（将按键加入
protected:
    QGraphicsView mGameView;//游戏视图
    QGraphicsScene mGameScene;//游戏场景
    QGraphicsScene mStartScene;//开始场景


    QGraphicsPixmapItem mBackGround1;//背景元素
    QGraphicsPixmapItem mBackGround2;//

    Player mPlane;

    //定时器
    QTimer* mBGMoveTimer;//背景移动
    QTimer* mPlaneMoveTimer;//飞机移动
    QTimer* mPlaneShootTimer;//飞机发射定时器
    QTimer* mBulletMoveTimer;//子弹移动定时器
    QTimer* mEnemyCreateTimer;//敌机创建定时器
    QTimer* mEnemyMoveTimer;//敌机移动定时器


    //容器）

    QList<Bullet*> mBulletList;//子弹容器
    QList<Enemy*> mEnemyList;//敌机容器

    //背景音乐
    QMediaPlayer mMediaBG;

};

#endif // GAMECONTROL_H
