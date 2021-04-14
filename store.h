#ifndef STORE_H
#define STORE_H

#include <QMainWindow>
#include"iteam.h"
#include<QMap>
#include"hide.h"

namespace Ui {
class store;
}

class store : public QMainWindow
{
    Q_OBJECT

public:
    explicit store(QWidget *parent = nullptr);
    ~store();
    void paintEvent(QPaintEvent *);
    int sumGold=0;//购买道具总金额
    void reshowEvent();
    int iteamnum=10;//可买道具数量
    QMap<int,iteam> storeIteams;//商店道具
    class hide *h=NULL;
signals:
    void chooseBack();//返回信号

private:
    Ui::store *ui;
};

#endif // STORE_H
