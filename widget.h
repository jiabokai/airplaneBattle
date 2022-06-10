#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QGraphicsPixmapItem>//图形元素
//#include <QGraphicsView>//视图
//#include <QGraphicsScene>//场景
//#include <QList>
//#include "player.h"
//#include "bullet.h"
//#include "enemy.h"
//#include <QMediaPlayer>//媒体播放器


//元素组成-->场景-->视图-->窗口

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //背景移动函数
    void BGMove();

    //按键事件
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    static Widget* widget;
private:
    Ui::Widget *ui;



};
#endif // WIDGET_H
