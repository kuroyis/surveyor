#ifndef SAVESELECT_H
#define SAVESELECT_H

#include <QMainWindow>
#include<QPainter>
#include"mypushbutton.h"

namespace Ui {
class saveselect;
}

class saveselect : public QMainWindow
{
    Q_OBJECT

public:
    explicit saveselect(QWidget *parent = nullptr);
    ~saveselect();
    void paintEvent(QPaintEvent *);
    myPushButton *loadbtn1=new myPushButton(":/image/selectdialog.png");
    myPushButton *loadbtn2=new myPushButton(":/image/selectdialog.png");
    myPushButton *loadbtn3=new myPushButton(":/image/selectdialog.png");
    QString showLoad(QString filePath,QString fileName); //返回存档信息
    void reshowEvent();
signals:
    void chooseback();
private:
    Ui::saveselect *ui;
};

#endif // SAVESELECT_H
