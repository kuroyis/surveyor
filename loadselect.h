#ifndef LOADSELECT_H
#define LOADSELECT_H

#include <QMainWindow>
#include<QPainter>
#include"personscene.h"
#include"mypushbutton.h"

namespace Ui {
class loadselect;
}

class loadselect : public QMainWindow
{
    Q_OBJECT

public:
    explicit loadselect(QWidget *parent = nullptr);
    ~loadselect();
    void paintEvent(QPaintEvent *);
    myPushButton *loadbtn1=new myPushButton(":/image/selectdialog.png");
    myPushButton *loadbtn2=new myPushButton(":/image/selectdialog.png");
    myPushButton *loadbtn3=new myPushButton(":/image/selectdialog.png");
    QString showLoad(QString filePath,QString fileName); //返回存档信息
    void reshowEvent();
    personscene *personScence=NULL;
private:
    Ui::loadselect *ui;
};

#endif // LOADSELECT_H
