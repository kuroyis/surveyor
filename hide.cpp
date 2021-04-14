#include "hide.h"
#include "ui_hide.h"
#include"player.h"
#include<QPainter>

hide::hide(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hide)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    ui->textEdit->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    ui->lineEdit->hide();
    ui->label_5->hide();
    ui->pushButton_5->hide();
    ui->textEdit->hide();
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString mes;
        mes="你选择了享用伏特加，生命之水可不是闹着玩的";
        ui->textEdit->setText(mes);
        ui->label_5->show();
        ui->textEdit->show();
        ui->pushButton_5->show();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        QString mes;
        mes="你选择了享用果酒，香甜的口感让人沉醉";
        ui->textEdit->setText(mes);
        ui->label_5->show();
        ui->textEdit->show();
        ui->pushButton_5->show();
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        QString mes;
        mes="你选择了享用清酒，清香的气味让人神怡";
        ui->textEdit->setText(mes);
        ui->label_5->show();
        ui->textEdit->show();
        ui->pushButton_5->show();
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        QString mes;
        mes="你选择了红茶，不知不觉陷入了沉睡\n苏醒后你想起了一切，你就是世界的主宰(输入暗号获取权力)";
        ui->textEdit->setText(mes);
        ui->label_5->show();
        ui->textEdit->show();
        ui->lineEdit->show();
        ui->pushButton_5->show();
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=](){
        if(ui->lineEdit->text()=="114514")
        {
            p->level=100;
            p->gold=1000;
        }
        emit chooseBack();
    });
}

hide::~hide()
{
    delete ui;
}

void hide::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/store.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
