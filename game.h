#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include"mypushbutton.h"
#include"iteampushbutton.h"
#include"iteam.h"
#include"gamedate.h"

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
    void paintEvent(QPaintEvent *);
    myPushButton *personBtn = new myPushButton(":/image/person.png");//个人按钮
    myPushButton *helpBtn = new myPushButton(":/image/help.png");//帮助按钮950 10
    myPushButton *diaBtn = new myPushButton(":/image/arrright.png");//对话框按钮
    myPushButton *qrBtn = new myPushButton(":/image/queren0.png",":/image/queren2.png");//确认按钮
    int picnum=2;//第n个图片
    int getgold=0;//获得奖励
    int helpnum=1;//n帮助
    void joinEvent();//过场gif
    void reshowEvent();
    void showEnd();//结算界面
    int QBnum=0;//情报个数
    int point;//骰子点数
    int KLnum=0;//狂乱回合数 3-2-1-0
    int jjnum=1;//急救次数 1-0
    int check(int xx);//事件检测xx 0大成功 1成功 2失败 3大失败
    int end=0;//0为死亡 1为事件解决 2为true end 3为隐藏（死里逃生）
    gamedate *gdate = NULL;
signals:
    void chooseBack1();//返回信号


private:
    Ui::game *ui;
};

#endif // GAME_H
