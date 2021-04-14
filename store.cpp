#include "store.h"
#include "ui_store.h"
#include<QPainter>
#include"iteampushbutton.h"
#include"mypushbutton.h"
#include"iteam.h"
#include"player.h"

store::store(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::store)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    //点击退出，退出程序
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //载人商品
    storeIteams.insert(3,iteam(3));
    storeIteams.insert(4,iteam(4));
    storeIteams.insert(5,iteam(5));
    storeIteams.insert(7,iteam(7));
    storeIteams.insert(8,iteam(8));
    storeIteams.insert(9,iteam(9));
    storeIteams.insert(11,iteam(11));
    storeIteams.insert(12,iteam(12));
    storeIteams.insert(13,iteam(13));
    storeIteams.insert(14,iteam(14));
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }\
                                  QTabBar::tab{background-color:rgb(220,200,180);color:rgb(0,0,0);font:10pt '新宋体'}\
                                  QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(0,255,0);font:10pt '新宋体'}");
    ui->textEdit_2->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit_2->setTextColor(Qt::red);
    ui->textEdit_2->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_2->hide();
    ui->textEdit->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit->hide();
    ui->textEdit_3->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit_3->viewport()->setCursor(Qt::ArrowCursor);
    myPushButton *buyBtn = new myPushButton(":/image/queren0.png",":/image/queren2.png");
    buyBtn->setParent(ui->tabWidget);
    buyBtn->move(620,435);
    buyBtn->hide();
    ui->hideButton->hide();
    h = new class hide();
    connect(ui->hideButton,&QPushButton::clicked,[=](){
        h->move(this->frameGeometry().x(),this->frameGeometry().y());
        this->hide();
        h->show();
    });
    connect(h,&hide::chooseBack,[=](){
        this->move(h->frameGeometry().x(),h->frameGeometry().y());
        h->close();
        this->reshowEvent();
        this->show();
    });
    iteamPushButton *iteamBtn[27];
    int i=0;
    for(QMap<int,iteam>::iterator it=storeIteams.begin();it!=storeIteams.end();it++,i++)
    {
        iteamBtn[i]=new iteamPushButton(*it);
        iteamBtn[i]->setParent(ui->tab_2);
        iteamBtn[i]->move(0+(100*i)%600,100*((100*i)/600));
        connect(iteamBtn[i],&QPushButton::clicked,[=]()//显示道具信息
        {
            if(iteamBtn[i]->status==0)//选中状态
            {
                iteamBtn[i]->setStyleSheet("background:rgb(0,255,0)");
                ui->textEdit_2->show();
                buyBtn->show();
                ui->textEdit->show();
                QString mes;
                mes+=iteamBtn[i]->tempIteam.i_name;
                mes+="\n\n";
                mes+=iteamBtn[i]->tempIteam.i_mes;
                mes+="\n\n   价格:";
                mes+=QString::number(iteamBtn[i]->tempIteam.i_gold);
                ui->textEdit_2->setText(mes);
                sumGold+=iteamBtn[i]->tempIteam.i_gold;
                mes="总价格:";
                mes+=QString::number(sumGold);
                ui->textEdit->setText(mes);
                iteamBtn[i]->status=1;
            }
            else
            {
                iteamBtn[i]->setStyleSheet("QPushButton{border:0px}");
                ui->textEdit_2->hide();
                sumGold-=iteamBtn[i]->tempIteam.i_gold;
                QString mes="总价格:";
                mes+=QString::number(sumGold);
                ui->textEdit->setText(mes);
                iteamBtn[i]->status=0;
            }
        });
    }
    connect(buyBtn,&QPushButton::clicked,[=](){
        if(p->gold>=sumGold){
        p->gold-=sumGold;
        ui->textEdit_3->setText(QString::number(p->gold));
        for(int i=0;i<iteamnum;i++)
        {
            if(iteamBtn[i]->status==1)
            {
                QMap<int,iteam>::iterator pos=p->iteams.find(iteamBtn[i]->tempIteam.i_id);
                if(pos!=p->iteams.end())
                {
                    pos->i_num++;
                }
                else
                {
                p->iteams.insert(iteamBtn[i]->tempIteam.i_id,iteamBtn[i]->tempIteam);
                }
            }
        }
        }
        else
        {

        }
    });
    myPushButton *returnBtn = new myPushButton(":/image/return0.png");//返回按钮
    returnBtn->setParent(this);
    returnBtn->setIconSize(QSize(111,81));
    returnBtn->move(900,510);
    connect(returnBtn,&QPushButton::clicked,[=](){
        emit this->chooseBack();
    });
    this->reshowEvent();
}

store::~store()
{
    delete ui;
}

void store::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/store.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void store::reshowEvent()
{
    int i=generateRandomNumber(1,4);
    if(i==2)
    {
        ui->hideButton->show();
    }
    ui->textEdit_3->setText(QString::number(p->gold));
}
