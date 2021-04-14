#include "persondate.h"
#include "ui_persondate.h"
#include"iteampushbutton.h"
#include"mypushbutton.h"
#include"player.h"
#include<QPainter>
#include<QMap>

persondate::persondate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::persondate)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //透明化
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }\
                                  QTabBar::tab{background-color:rgb(220,200,180);color:rgb(0,0,0);font:10pt '新宋体'}\
                                  QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(0,255,0);font:10pt '新宋体'}");
    ui->textEdit->setStyleSheet("background-color:rgba(0,0,0,0);\
                                  font-size: 18pt;\
                                  font-family: 'Copperplate Gothic Bold';\
                                  font-family: '楷体'");
    ui->textEdit_2->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit->setTextColor(Qt::white);
    ui->textEdit_2->setTextColor(Qt::white);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_2->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_2->hide();
    connect(ui->tabWidget,&QTabWidget::currentChanged,[=](){//切换页面
        ui->textEdit_2->setText("");
        ui->textEdit_2->hide();
    });
    myPushButton *returnBtn = new myPushButton(":/image/return0.png");//返回按钮
    returnBtn->setParent(this);
    returnBtn->setIconSize(QSize(111,81));
    returnBtn->move(900,510);
    connect(returnBtn,&QPushButton::clicked,[=](){
        emit this->chooseBack();
        int i=0;
        for(QMap<int,iteam>::iterator it=p->iteams.begin();it!=p->iteams.end();it++,i++)//道具按钮
        {
            iteamBtn[i]->hide();
        }
    });
    this->reshowEvent();
}


persondate::~persondate()
{
    delete ui;
}

void persondate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/saveselect.png");
    painter.drawPixmap(0,20,this->width(),this->height()-20,pix);
}

void persondate::reshowEvent()
{
    int i=0;
    QString str;
    str="等级:";
    str+=QString::number(p->level);
    str+="\n\n";
    str+="经验:";
    str+=QString::number(p->exp);
    str+="/20";
    str+="\n\n";
    str+="金币:";
    str+=QString::number(p->gold);
    str+="\n\n";
    str+="日期:";
    str+=p->changeDate;
    str+="\n\n";
    str+="个人描述:";
    if(p->level<10){
        str+="你还是个新手调查员，感觉去进行旅途强化自身吧！";
    }
    else if(10<=p->level&&p->level<50)
    {
        str+="你已经拥有了初步的经验，试着去还原异常的全貌吧！";
    }
    else if(50<=p->level&&p->level<100)
    {
        str+="你已经拥有了相对强健的灵魂,试着去挑战难度更高的异常吧！";
    }
    else if(100<=p->level&&p->level<300)
    {
        str+="异常在你面前已经平平无奇，在你高超的思维和正确的行动下，邪恶无所遁形，这样下去你说不定会成为神！";
    }
    else{
        str+="神";
    }
    ui->textEdit->setText(str);
    for(QMap<int,iteam>::iterator it=p->iteams.begin();it!=p->iteams.end();it++,i++)//道具按钮
    {
        iteamBtn[i]=new iteamPushButton(*it);
        iteamBtn[i]->setParent(ui->tab_2);
        iteamBtn[i]->move(0+(100*i)%600,100*((100*i)/600));
        iteamBtn[i]->show();
        connect(iteamBtn[i],&QPushButton::clicked,[=]()//显示道具信息
        {
            ui->textEdit_2->show();
            QString mes;
            mes+=(*it).i_name;
            mes+="\n             X";
            mes+=QString::number((*it).i_num);
            mes+="\n\n";
            mes+=(*it).i_mes;
            ui->textEdit_2->setText(mes);
        });
    }
}
