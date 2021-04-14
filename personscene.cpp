#include "personscene.h"
#include "ui_personscene.h"
#include"mypushbutton.h"
#include"player.h"
#include<QVector>
#include<QDialog>
#include<QDateTime>
#include<QTimer>

personscene::personscene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::personscene)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    ui->lineEdit_2->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->lineEdit_2->setCursor(Qt::ArrowCursor);
    ui->lineEdit_2->setTextColor(Qt::white);
    ui->lineEdit_2->hide();
    myPushButton *rightBtn = new myPushButton(":/image/arrright.png");
    rightBtn->setParent(this);
    rightBtn->setIconSize(QSize(111,81));
    rightBtn->move(910,240);
    myPushButton *leftBtn = new myPushButton(":/image/arrleft.png");
    leftBtn->setParent(this);
    leftBtn->setIconSize(QSize(111,81));
    leftBtn->move(10,240);
    myPushButton *frontBtn = new myPushButton(":/image/arrfront.png",":/image/arrfront2.png");
    frontBtn->setParent(this);
    frontBtn->move(370,480);
    myPushButton *setBtn = new myPushButton(":/image/set.png");
    setBtn->setParent(this);
    setBtn->move(940,25);
    helpBtn->setParent(this);
    helpBtn->move(950,30);
    helpBtn->hide();
    personDate = new persondate();
    sto = new store();
    save = new saveselect();
    //监听返回按钮信号
    connect(personDate,&persondate::chooseBack,[=](){
        int x=personDate->frameGeometry().x();
        int y=personDate->frameGeometry().y();
        personDate->close();
        this->move(x,y);
        this->reshowEvent();
        this->show();//重新显示
    });
    connect(sto,&store::chooseBack,[=](){
        int x=sto->frameGeometry().x();
        int y=sto->frameGeometry().y();
        sto->hide();
        this->move(x,y);
        this->reshowEvent();
        this->show();//重新显示
    });
    connect(save,&saveselect::chooseback,[=](){
        int x=save->frameGeometry().x();
        int y=save->frameGeometry().y();
        save->hide();
        this->move(x,y);
        this->reshowEvent();
        this->show();//重新显示
    });
    connect(helpBtn,&QPushButton::clicked,[=](){//帮助按钮
        QString mes;
        mes="完成一局游戏后记得存档哦!";
        ui->lineEdit_2->setText(mes);
        ui->lineEdit_2->show();
         QTimer::singleShot(5000,this,[=]()
         {
             ui->lineEdit_2->hide();
             helpBtn->hide();
         });
    });
    //左标进入个人信息
    connect(leftBtn,&QPushButton::clicked,[=](){
        this->hide();
        int x=this->frameGeometry().x();
        int y=this->frameGeometry().y();
        personDate->move(x,y);
        personDate->show();
        personDate->reshowEvent();
    });
    //右标进入商店
    connect(rightBtn,&QPushButton::clicked,[=](){
        this->hide();
        int x=this->frameGeometry().x();
        int y=this->frameGeometry().y();
        sto->move(x,y);
        sto->reshowEvent();
        sto->show();
    });
    //前标进入游戏选择
    connect(frontBtn,&QPushButton::clicked,[=]()
    {
        ms = new mapselect();
        this->hide();
        int x=this->frameGeometry().x();
        int y=this->frameGeometry().y();
        ms->move(x,y);
        ms->reshowEvent1();
        ms->show();
        connect(ms,&mapselect::chooseBack,[=](){
            int x=ms->frameGeometry().x();
            int y=ms->frameGeometry().y();
            ms->hide();
            this->move(x,y);
            this->reshowEvent();
            this->show();//重新显示
        });
        connect(ms,&mapselect::chooseBack2,[=](){
            this->move(ms->frameGeometry().x(),ms->newGame->frameGeometry().y());
            this->reshowEvent();
            helpBtn->show();
            ms->newGame->hide();
            this->show();
        });
    });
    connect(setBtn,&QPushButton::clicked,[=](){
        QDialog *setdlg= new QDialog(this);
        setdlg->resize(250,300);
        setdlg->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        setdlg->setStyleSheet("background-image:url(:/image/mesbg.png);");
        myPushButton *saveBtn = new myPushButton(":/image/save0.png",":/image/save2.png");
        saveBtn->setParent(setdlg);
        saveBtn->move(20,40);
        myPushButton *loadBtn = new myPushButton(":/image/load0.png",":/image/load2.png");
        loadBtn->setParent(setdlg);
        loadBtn->move(20,120);
        myPushButton *returnBtn = new myPushButton(":/image/return0.png");
        returnBtn->setParent(setdlg);
        returnBtn->move(100,250);
        connect(saveBtn,&QPushButton::clicked,[=](){
            setdlg->close();
            this->hide();
            save->move(this->frameGeometry().x(),this->frameGeometry().y());
            save->reshowEvent();
            save->show();
        });
        connect(loadBtn,&QPushButton::clicked,[=](){
            setdlg->close();
            this->hide();
            emit chooseload();
        });
        connect(returnBtn,&QPushButton::clicked,[=](){
            setdlg->close();
        });
        setdlg->exec();
    });
    this->reshowEvent();
}

personscene::~personscene()
{
    delete ui;
}

void personscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/mainmenu.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/icon.png");
    painter.drawPixmap(10,50,pix);
}

void personscene::reshowEvent()
{
    ui->levelEdit->setAlignment( Qt::AlignCenter);//居中
    ui->levelEdit->setStyleSheet("background-color:rgba(0,0,0,0);\
                                  font-size: 18pt;\
                                  font-family: 'Copperplate Gothic Bold';\
                                  font-family: '楷体'");
    ui->levelEdit->setText(QString::number(p->level));
    ui->levelline->setValue(p->exp);
    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent;color:white;font-size: 18pt}");
    ui->lineEdit->setText(QString::number(p->gold));
}
