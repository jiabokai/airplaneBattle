#include "widget.h"
#include "ui_widget.h"
#include "gamecontrol.h"


Widget* Widget::widget = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(512,768);

    widget = this;
    //


}

Widget::~Widget()
{
    delete ui;
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W: //mPlane.moveBy(0,-5);break;
        case Qt::Key_S: //mPlane.moveBy(0,5);break;
        case Qt::Key_A://mPlane.moveBy(-5,0);break;
        case Qt::Key_D: //mPlane.moveBy(5,0);break;
        GameControl::Instance()->mKeyList.append(event->key());
        break;


    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除对应按键组合
    if(GameControl::Instance()->mKeyList.contains(event->key()))
    {
       GameControl::Instance()->mKeyList.removeOne(event->key());
    }
}



















