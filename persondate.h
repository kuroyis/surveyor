#ifndef PERSONDATE_H
#define PERSONDATE_H

#include <QMainWindow>
#include"iteampushbutton.h"

namespace Ui {
class persondate;
}

class persondate : public QMainWindow
{
    Q_OBJECT

public:
    explicit persondate(QWidget *parent = nullptr);
    ~persondate();
    void paintEvent(QPaintEvent *);
    void reshowEvent();
    iteamPushButton *iteamBtn[30];
signals:
    void chooseBack();//自定义返回信号


private:
    Ui::persondate *ui;
};

#endif // PERSONDATE_H
