#ifndef GAMEDATE_H
#define GAMEDATE_H

#include <QMainWindow>
#include"iteampushbutton.h"
#include"mypushbutton.h"

namespace Ui {
class gamedate;
}

class gamedate : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamedate(QWidget *parent = nullptr);
    ~gamedate();
    void paintEvent(QPaintEvent *);
    void personEvent();
    myPushButton *useBtn = new myPushButton(":/image/use.png");//使用按钮
    iteamPushButton *iteamBtn[30];
    int time=0;//时间
    int turn=0;//当前轮数
    int usenum1=3;//iteam1使用次数 3-2-1
    iteam tempiteam;//选中iteam
    void listEvent(int num);
signals:
    void chooseBack0();//返回信号
    void chooseback();

private:
    Ui::gamedate *ui;
};

#endif // GAMEDATE_H
