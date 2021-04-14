#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <QMainWindow>
#include"map.h"
#include<QMap>
#include"mypushbutton.h"
#include"character.h"
#include"game.h"

namespace Ui {
class mapselect;
}

class mapselect : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapselect(QWidget *parent = nullptr);
    ~mapselect();
    void paintEvent(QPaintEvent *);
    QMap<int,map> maps;//地图
    QMap<int,character> characters;//人物
    void reshowEvent1();//地图选择
    void reshowEvent2();//人物选择
    void reshowEvent3();//道具选择
    myPushButton *rightBtn = new myPushButton(":/image/arrright.png");//右标
    myPushButton *leftBtn = new myPushButton(":/image/arrleft.png");//左标
    myPushButton *easyBtn = new myPushButton(":/image/easybtn0.png",":/image/easybtn2.png");//简单按钮
    myPushButton *normalBtn = new myPushButton(":/image/normalbtn0.png",":/image/normalbtn2.png");//普通按钮
    myPushButton *returnBtn = new myPushButton(":/image/return0.png");//返回按钮
    myPushButton *helpBtn = new myPushButton(":/image/help.png");//帮助按钮950 10
    myPushButton *mapBtn[10];//地图按钮
    myPushButton *characterBtn[10];//人物按钮
    myPushButton *qrBtn = new myPushButton(":/image/queren0.png",":/image/queren2.png");//确认按钮
    int status=1;//窗口状态 1选地图 2选人 3选物品
    int levelnum=0;//关卡难度
    int mapnum=1;//地图序号
    int characternum=1;//人物序号
    int iteamnum=1;//道具数量
    game *newGame=NULL;
signals:
    void chooseBack();//返回信号
    void chooseBack2();

private:
    Ui::mapselect *ui;
};

#endif // MAPSELECT_H
