#ifndef PERSONSCENE_H
#define PERSONSCENE_H

#include <QMainWindow>
#include<QPainter>
#include"persondate.h"
#include"store.h"
#include"saveselect.h"
#include"mapselect.h"


namespace Ui {
class personscene;
}

class personscene : public QMainWindow
{
    Q_OBJECT

public:
    explicit personscene(QWidget *parent = nullptr);
    ~personscene();
    void paintEvent(QPaintEvent *);
    void reshowEvent();
    myPushButton *helpBtn = new myPushButton(":/image/help.png");//帮助按钮
    persondate *personDate=NULL;
    store *sto=NULL;
    mapselect *ms=NULL;
    saveselect *save=NULL;
signals:
    void chooseload();//load信号

private:
    Ui::personscene *ui;
};

#endif // PERSONSCENE_H
