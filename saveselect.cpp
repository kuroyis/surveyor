#include "saveselect.h"
#include "ui_saveselect.h"
#include"mypushbutton.h"
#include"player.h"
#include<QFile>

saveselect::saveselect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::saveselect)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    loadbtn1->setParent(this);
    loadbtn1->setIconSize(QSize(800,150));
    loadbtn1->move(90,40);
    loadbtn2->setParent(this);
    loadbtn2->setIconSize(QSize(800,150));
    loadbtn2->move(90,220);
    loadbtn3->setParent(this);
    loadbtn3->setIconSize(QSize(800,150));
    loadbtn3->move(90,400);
    this->reshowEvent();
}

saveselect::~saveselect()
{
    delete ui;
}

void saveselect::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/saveselect.png");
    painter.drawPixmap(0,20,this->width(),this->height()-20,pix);
    QPen pen(QColor(255,255,255));
    pen.setStyle(Qt::PenStyle::CustomDashLine);
    painter.setPen(pen);
    painter.drawText(QRect(50,50,20,100),"选\n择\n存\n档");
}

QString saveselect::showLoad(QString filePath,QString fileName)
{
    QString str=NULL;
    player *pl=new player();
    if(pl->checkFile(filePath,fileName))
    {
    pl->loadDate(filePath,fileName);
    str="等级:";
    str+=QString::number(pl->level);
    str+="\n";
    str+="金币:";
    str+=QString::number(pl->gold);
    str+="\n";
    str+="日期:";
    str+=pl->changeDate;
    }
    return str;
}

void saveselect::reshowEvent()
{
    QCursor cursor(Qt::PointingHandCursor);
    loadbtn1->setCursor(cursor);
    loadbtn2->setCursor(cursor);
    loadbtn3->setCursor(cursor);
    connect(loadbtn1,&QPushButton::clicked,[=](){
        this->hide();
        p->saveDate("D:\\Qt\\surveyor\\save","save1.txt");
        emit chooseback();
    });
    connect(loadbtn2,&QPushButton::clicked,[=](){
        this->hide();
        p->saveDate("D:\\Qt\\surveyor\\save","save2.txt");
        emit chooseback();
    });
    connect(loadbtn3,&QPushButton::clicked,[=](){
        this->hide();
        p->saveDate("D:\\Qt\\surveyor\\save","save3.txt");
        emit chooseback();
    });
    //设置文本编辑窗体透明
    ui->textEdit1->setStyleSheet("background-color:rgba(0,0,0,0);\
                                  font-size: 18pt;\
                                  font-family: 'Copperplate Gothic Bold';\
                                  font-family: '楷体'");
    ui->textEdit1->setTextColor(Qt::white);
    ui->textEdit2->setStyleSheet("background-color:rgba(0,0,0,0);\
                                  font-size: 18pt;\
                                  font-family: 'Copperplate Gothic Bold';\
                                  font-family: '楷体'");
    ui->textEdit2->setTextColor(Qt::white);
    ui->textEdit3->setStyleSheet("background-color:rgba(0,0,0,0);\
                                  font-size: 18pt;\
                                  font-family: 'Copperplate Gothic Bold';\
                                  font-family: '楷体'");
    ui->textEdit3->setTextColor(Qt::white);
    //输出文本信息
    QString str;
    str=showLoad("D:\\Qt\\surveyor\\save","save1.txt");
    ui->textEdit1->setText(str);
    str=showLoad("D:\\Qt\\surveyor\\save","save2.txt");
    ui->textEdit2->setText(str);
    str=showLoad("D:\\Qt\\surveyor\\save","save3.txt");
    ui->textEdit3->setText(str);
}
