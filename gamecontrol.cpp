#include "gamecontrol.h"
#include "gameobjectpool.h"

GameControl* GameControl::instance = nullptr;

GameControl::GameControl(QWidget* parent)
{
    this->setParent(parent);//此句的作用是：关闭主窗口时会调用该析构函数
}
void GameControl::BGMove()
{
    mBackGround2.moveBy(0,2);
    mBackGround1.moveBy(0,2);//moveby 移动量

    if(mBackGround1.y()>=mBackGround1.pixmap().height())
    {
        mBackGround1.setY(-mBackGround1.pixmap().height());
    }
    else if(mBackGround2.y()>=mBackGround2.pixmap().height())
    {
        mBackGround2.setY(-mBackGround2.pixmap().height());
    }
}

void GameControl::PlaneMove()
{
    for (int keyCode :mKeyList )
    {
        switch(keyCode)
        {
        case Qt::Key_W: mPlane.moveBy(0,-1*mPlane.mMoveSpeed);break;
        case Qt::Key_S: mPlane.moveBy(0,1*mPlane.mMoveSpeed);break;
        case Qt::Key_A: mPlane.moveBy(-1*mPlane.mMoveSpeed,0);break;
        case Qt::Key_D: mPlane.moveBy(1*mPlane.mMoveSpeed,0);break;
        }
    }
    //边界判断
    if(mPlane.x()<0)
    {
        mPlane.setX(0);
    }
    if(mPlane.y()<0)
    {
        mPlane.setY(0);
    }
    if(mPlane.x()>GameDefine::ScreenWidth-mPlane.pixmap().width())
    {
        mPlane.setX(GameDefine::ScreenWidth-mPlane.pixmap().width());
    }
    if(mPlane.y()>GameDefine::ScreenHeight-mPlane.pixmap().height())
    {
        mPlane.setY(GameDefine::ScreenHeight-mPlane.pixmap().height());
    }
}



void GameControl::PlaneBulletShoot()
{
    //创建子弹
//    QPixmap bulletImg(":/Image/bullet.png");
//    //如何修改图片大小？如何根据窗口改变而改变？
//    //bulletImg= bulletImg.scaled(100,100,Qt::KeepAspectRatio);//将pixmap进行缩放
//    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,mPlane.y() );
//    Bullet* bullet1 = new Bullet(pos,bulletImg,Bullet::BT_Player);

    //对象池构建子弹
    QPixmap bulletImg(":/Image/bullet.png");
    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,mPlane.y() );
    GameObject* bullet = GameObjectPool::Instance()->GetGameObject(GameObject::OT_BulletPlayer);
    PlayerBullet* bullet1 = (PlayerBullet*) bullet;//指针类型可以强转，而对象则不可以
    bullet1->Init(pos,bulletImg);
    bullet1->PlaySound();

    //添加到场景
    mGameScene.addItem(bullet1);//场景会释放，则会释放他的孩子，如此例的子弹

    //添加到子弹管理器
    mBulletList.append(bullet1);
}

void GameControl::CreateEnemy()
{
//    QPixmap pixmap(":/Image/enemyPlane.png");
//    int randx = qrand()%(512-pixmap.width());
//   Enemy* enemy = new Enemy(QPoint(randx,-200),pixmap);

    //对象池获取对象
    QPixmap pixmap(":/Image/enemyPlane.png");
    int randx = qrand()%(512-pixmap.width());
    GameObject* obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy);
    Enemy* enemy = (Enemy*)obj;
    enemy->Init(QPoint(randx,-200),pixmap);



    //添加到场景
    mGameScene.addItem(enemy);

    //添加到管理器
    mEnemyList.append(enemy);


}

void GameControl::Collision()
{
    //遍历子弹
    for(int i = 0;i<mBulletList.size();i++)
    {
        //遍历敌机
        for(int j=0;j<mEnemyList.size();j++)
        {
            if(mBulletList[i]->collidesWithItem(mEnemyList[j]))
            {
//                //移除场景   实际的对象并没有被删除
//                mGameScene.removeItem(mBulletList[i]);
//                mGameScene.removeItem(mEnemyList[j]);

                //移除场景并回收到对象池
                mBulletList[i]->GameObjectDelete(&mGameScene);
                mEnemyList[j]->GameObjectDelete(&mGameScene);



                //移除管理器
                mBulletList.removeOne(mBulletList[i]);
                mEnemyList.removeOne(mEnemyList[j]);
            }
        }
    }
}
void GameControl::GameInit()
{
    //对象池初始化
    GameObjectPool::Instance()->Init();




    //mGameView.setSceneRect(QRect(0,0,512,768));

    //设置视图的parent为窗口
    mGameView.setParent(Widget::widget);


    LoadStartScene();//开始场景

    //定时器初始化
     mBGMoveTimer = new QTimer(this);
     mPlaneMoveTimer = new QTimer(this);
     mPlaneShootTimer = new QTimer(this);
     mBulletMoveTimer = new QTimer(this);
     mEnemyCreateTimer = new QTimer(this);
     mEnemyMoveTimer = new QTimer(this);


     //绑定定时器处理函数
     connect(mBGMoveTimer,&QTimer::timeout,this,&GameControl::BGMove);
     connect(mPlaneMoveTimer,&QTimer::timeout,this,&GameControl::PlaneMove);
     connect(mPlaneShootTimer,&QTimer::timeout,this,&GameControl::PlaneBulletShoot);
     connect(mBulletMoveTimer,&QTimer::timeout,[this](){
         //子弹移动
             for(auto bullet:mBulletList)
             {
                 bullet->BulletMove();

                 //判断越界回收对象
                 if(bullet->y()<-200)
                 {
//                     //移除场景
//                     mGameScene.removeItem(bullet);


//                     //移除容器
//                     mBulletList.removeOne(bullet);

//                     //对象池回收对象
//                     GameObjectPool::Instance()->RecoveryGameObject(bullet);

                     //移除场景   对象池回收对象
                     bullet->GameObjectDelete(&mGameScene);
                     //移除容器
                     mBulletList.removeOne(bullet);

                 }
             }
             //碰撞检测
             Collision();
         });
    connect(mEnemyCreateTimer,&QTimer::timeout,this,&GameControl::CreateEnemy);
    connect(mEnemyMoveTimer,&QTimer::timeout,[this](){
        //敌机移动
            for(auto enemy:mEnemyList)
            {
                enemy->EnemyMove();

                if(enemy->y()>GameDefine::ScreenHeight+enemy->pixmap().height())
                {
//                    //移除场景
//                    mGameScene.removeItem(enemy);


//                    //移除容器
//                    mEnemyList.removeOne(enemy);

//                    //对象池回收对象
//                    GameObjectPool::Instance()->RecoveryGameObject(enemy);

                    //移除场景   对象池回收对象
                    enemy->GameObjectDelete(&mGameScene);
                    //移除容器
                    mEnemyList.removeOne(enemy);

                }

            }
        });


}

void GameControl::LoadStartScene()
{
    mStartScene.setSceneRect(QRect(0,0,512,768));//游戏开始场景大小

    //开始场景初始化
    QPixmap startScene = QPixmap(":/Image/startscene.png");
    startScene= startScene.scaled(512,768,Qt::KeepAspectRatio);//将pixmap进行缩放
    mStartScene.addPixmap(startScene);

    auto startBtn = new QToolButton();
//    startBtn->resize(171,45);//有个问题，当resize调用后，需设置widget的边缘空白部分为0
    QPixmap startBtnIcon = QPixmap(":/Image/startGameBtn.png");
    startBtnIcon= startBtnIcon.scaled(171,45,Qt::KeepAspectRatio);//将pixmap进行缩放
    startBtn->setIcon(QIcon(startBtnIcon));
    startBtn->setIconSize(QSize(171,45));
    startBtn->move(256-171/2,384);
    startBtn->setAutoRaise(true);
    //开始游戏
    connect(startBtn,&QToolButton::clicked,[this](){

        //加载游戏场景
        this->LoadGameScene();

        //开始游戏
        this->GameStart();


    });


    mStartScene.addWidget(startBtn);
    //图片的大小需要与场景的大小一致，显示的时候才能充满窗口

    //设置当前场景为 开始场景
    mGameView.setScene(&mStartScene);
    mGameView.show();

}

void GameControl::LoadGameScene()
{
    mGameScene.setSceneRect(QRect(0,0,512,768));//游戏进行场景大小

    mBackGround1.setPixmap(QPixmap(":/Image/background.jpg"));
    mBackGround2.setPixmap(QPixmap(":/Image/background.jpg"));

    QPixmap airPlanePixmap = QPixmap(":/Image/airplane.jpg");
    //如何修改图片大小？如何根据窗口改变而改变？
    airPlanePixmap= airPlanePixmap.scaled(100,100,Qt::KeepAspectRatio);//将pixmap进行缩放
    mPlane.setPixmap(airPlanePixmap);
    mPlane.setPos(100,100);
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());

    //图片元素添加到场景
    mGameScene.addItem(&mBackGround1);
    mGameScene.addItem(&mBackGround2);


    mGameScene.addItem(&mPlane);




    //设置当前场景为游戏场景
    mGameView.setScene(&mGameScene);
    mGameView.show();

    // 注意 qurl路径对象 字符串格式“qrc:/+前缀名+/路径”
    this->mMediaBG.setMedia(QUrl("qrc:/audio/chanxin.mp3"));
   // this->mMediaBG.play();

}

void GameControl::GameStart()
{
    //开启定时器
    mBGMoveTimer->start(GameDefine::BackgroundUpdateTime);
    mPlaneMoveTimer ->start(GameDefine::BulletMoveUpdateTime);
    mPlaneShootTimer ->start(GameDefine::PlaneShootUpdateTime);
    mBulletMoveTimer ->start(GameDefine::BulletMoveUpdateTime);
    mEnemyCreateTimer ->start(GameDefine::EnemyCreateTime);
    mEnemyMoveTimer ->start(GameDefine::EnemyMoveUpdateTime);

}

void GameControl::GameOver()
{
    //结束逻辑

}
