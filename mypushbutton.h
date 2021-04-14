#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QPushButton *parent = nullptr);
    myPushButton(QString normalImg,QString pressImg = "");//传入正常和按下图片路径
    QString normalImgPath;
    QString pressImgPath;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
