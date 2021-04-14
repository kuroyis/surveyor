#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypushbutton.h"
#include<QTimer>
#include<QFile>
#include<QDir>
#include<QDebug>
#include"player.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    //点击退出，退出程序
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //开始按钮
    myPushButton *startBtn = new myPushButton(":/image/startbtn0.png",":/image/startbtn2.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.5);
    //实例化个人界面
    connect(startBtn,&QPushButton::clicked,[=](){
        //延时
        QTimer::singleShot(500,this,[=](){
            personScene = new personscene;
            int x=this->frameGeometry().x();
            int y=this->frameGeometry().y();           
            p->level=1;
            p->exp=0;
            p->gold=100;
            p->changeDate=QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
            p->iteams.insert(iteam(1).i_id,iteam(1));
            p->saveDate("D:\\Qt\\surveyor\\save","save1.txt");
            p->saveDate("D:\\Qt\\surveyor\\save","savetemp.txt");
            personScene->move(x,y);
            this->close();
            personScene->show();
        });
    });
    //继续按钮
    if(p->checkFile("D:\\Qt\\surveyor\\save","save1.txt")){
    myPushButton *continueBtn = new myPushButton(":/image/continuebtn0.png",":/image/continuebtn2.png");
    continueBtn->setParent(this);
    continueBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.65);
    //实例化存档选择界面 
    connect(continueBtn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            int x=this->frameGeometry().x();
            int y=this->frameGeometry().y();
            this->hide();
            loadSelect = new loadselect;
            loadSelect->move(x,y);
            loadSelect->show();
        });
    });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/mainmenu.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/icon.png");
    painter.drawPixmap(10,50,pix);
}

