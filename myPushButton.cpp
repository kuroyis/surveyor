#include "mypushbutton.h"
#include<QDebug>

myPushButton::myPushButton(QPushButton *parent) : QPushButton  (parent)
{

}

myPushButton::myPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    QCursor cursor(Qt::PointingHandCursor);
    this->setCursor(cursor);

}

void myPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        //不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类
    return QPushButton::mousePressEvent(e);
}

void myPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        //不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类
    return QPushButton::mouseReleaseEvent(e);
}
