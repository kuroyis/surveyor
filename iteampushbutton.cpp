#include "iteampushbutton.h"
#include<QDebug>
#include"QPixmapCache"

iteamPushButton::iteamPushButton()
{
    this->hide();
}

iteamPushButton::iteamPushButton(iteam tempiteam)
{
    this->tempIteam=tempiteam;
    QPixmap pix;
    bool ret = pix.load(tempIteam.i_img);
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
