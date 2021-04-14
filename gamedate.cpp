#include "gamedate.h"
#include "ui_gamedate.h"
#include"character.h"
#include"QPainter"
#include<QTimer>

gamedate::gamedate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamedate)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
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
    ui->textEdit_3->setTextColor(Qt::white);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_2->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_3->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit_3->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_2->hide();
    ui->textEdit_3->hide();
    myPushButton *returnBtn = new myPushButton(":/image/return0.png");//返回按钮
    returnBtn->setParent(this);
    returnBtn->move(900,510);
    useBtn->setParent(ui->tabWidget);
    useBtn->move(620,435);
    useBtn->hide();
    connect(ui->tabWidget,&QTabWidget::currentChanged,[=](){//切换页面
        useBtn->hide();
        ui->textEdit_2->setText("");
        ui->textEdit_2->hide();
    });
    connect(returnBtn,&QPushButton::clicked,[=](){
        emit this->chooseback();
        int i=0;
        for(QMap<int,iteam>::iterator it=ch->c_iteams.begin();it!=ch->c_iteams.end();it++,i++)
        {
            iteamBtn[i]->hide();
        }
    });
    connect(useBtn,&QPushButton::clicked,[=](){//使用道具按钮
        int i=0;
        for(QMap<int,iteam>::iterator it=ch->c_iteams.begin();it!=ch->c_iteams.end();it++,i++)
        {
            iteamBtn[i]->hide();
        }
        switch(tempiteam.i_id)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            emit chooseBack0();
            this->hide();
            break;
        }
        case 2:
        {
            if(usenum1!=0)
                {
            if(turn==0)
            {
                turn=0;
            }
            else if(1<=turn&&turn<=36)
            {
                turn=1;
            }
            else if(37<=turn&&turn<=48)
            {
                turn=37;
            }
            else if(49<=turn&&turn<=55)
            {
                turn=49;
            }
            else if(56<=turn&&turn<=65)
            {
                turn=56;
            }
            else
            {
            }
            usenum1--;
            if(usenum1<0)
            {
                usenum1=0;
            }
            if(usenum1==0)
            {
                ch->c_iteams[2].i_useable=1;
            }
            if(turn>=66)
            {
                ch->c_iteams[2].i_useable=1;
            }
            }
            break;
        }
        case 3:
        {
            ch->c_HP+=2;
            if(ch->c_HP>12)
                {
                ch->c_HP=12;
            }
            ch->c_iteams.remove(3);
            break;
        }
        case 4:
        {
            ch->c_INT+=10;
            if(ch->c_INT>99)
                {
                ch->c_INT=99;
            }
            ch->c_iteams.remove(4);
            break;
        }
        case 5:
        {
            ch->c_SAN+=10;
            if(ch->c_SAN>ch->c_POW)
                {
                ch->c_SAN=ch->c_POW;
            }
            ch->c_iteams.remove(5);
            break;
        }
        case 6:
        {
            ui->into->setPixmap(QPixmap(":/image/map1_0.png"));
            ui->into->raise();
            ui->into->show();
            QTimer::singleShot(2000,this,[=](){
            ui->into->hide();
            });
            break;
        }
        case 11:
        {
            if(ch->c_iteams[11].i_useable==1)
            {
            turn=11;
            ch->c_iteams[11].i_useable=1;
            }
            break;
        }
        case 12:
        {
            ch->c_APP+=10;
            if(ch->c_APP>99)
                {
                ch->c_APP=99;
            }
            ch->c_iteams.remove(12);
            break;
        }
        case 13:
        {
            ch->c_STR+=10;
            if(ch->c_STR>99)
                {
                ch->c_STR=99;
            }
            ch->c_iteams.remove(13);
            break;
        }
        case 14:
        {
            ch->c_DEX+=10;
            if(ch->c_DEX>99)
                {
                ch->c_DEX=99;
            }
            ch->c_iteams.remove(14);
            break;
        }
        }
        this->personEvent();
    });
}

gamedate::~gamedate()
{
    delete ui;
}

void gamedate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/saveselect.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void gamedate::personEvent()
{
    int i=0;
    for(QMap<int,iteam>::iterator it=ch->c_iteams.begin();it!=ch->c_iteams.end();it++,i++)//道具按钮
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
            if(iteamBtn[i]->tempIteam.i_useable==0)
            {
                ui->textEdit_3->setText("当前可使用");
            }
            else if(iteamBtn[i]->tempIteam.i_useable==1)
            {
                ui->textEdit_3->setText("当前不可使用");
            }
            ui->textEdit_3->show();
            useBtn->show();
            tempiteam=(*it);
        });
    }
    QString mes;
    mes="角色:";
    mes+=ch->c_mes;
    mes+="\n\n属性:";
    mes+="\n  力量:";
    mes+=QString::number(ch->c_STR);
    mes+="          体质:";
    mes+=QString::number(ch->c_CON);
    mes+="\n  体型:";
    mes+=QString::number(ch->c_SIZ);
    mes+="          敏捷:";
    mes+=QString::number(ch->c_DEX);
    mes+="\n  外貌:";
    mes+=QString::number(ch->c_APP);
    mes+="          智力:";
    mes+=QString::number(ch->c_INT);
    mes+="\n  意志:";
    mes+=QString::number(ch->c_POW);
    mes+="          教育:";
    mes+=QString::number(ch->c_EDU);
    mes+="\n  体力:";
    mes+=QString::number(ch->c_HP);
    mes+="          理智:";
    mes+=QString::number(ch->c_SAN);
    mes+="\n  幸运:";
    mes+=QString::number(ch->c_LUCK);
    mes+="          格斗:";
    mes+=QString::number(ch->c_gd);
    mes+="\n  操纵:";
    mes+=QString::number(ch->c_cz);
    mes+="          交涉:";
    mes+=QString::number(ch->c_js);
    mes+="\n  聆听:";
    mes+=QString::number(ch->c_lt);
    mes+="          侦察:";
    mes+=QString::number(ch->c_zc);
    mes+="\n  潜行:";
    mes+=QString::number(ch->c_qx);
    mes+="          闪避:";
    mes+=QString::number(ch->c_sb);
    mes+="\n  心理学:";
    mes+=QString::number(ch->c_xlx);
    mes+="        生存:";
    mes+=QString::number(ch->c_sc);
    mes+="\n  急救:";
    mes+=QString::number(ch->c_jj);
    mes+="\n状态:";
    if(ch->c_status==0)
    {
        mes+="正常";
    }
    mes+="\nTime:";
    mes+=QString::number(time);
    ui->textEdit->setText(mes);
    ui->label_3->setPixmap(QPixmap(ch->c_img));
}

void gamedate::listEvent(int num)
{
    switch (num) {
    case 1:
    {
        ui->listWidget->addItem("(1)附近城镇在最近出现人员在森林失踪情况");
        break;
    }
    case 2:
    {
        ui->listWidget->addItem("(2)森林深处有个古堡");
        break;
    }
    case 3:
    {
        ui->listWidget->addItem("(3)森林深处的村庄");
        break;
    }
    case 4:
    {
        ui->listWidget->addItem("(4)奇怪的原始村庄,村子里的人都很奇怪，好像隐藏着什么");
        break;
    }
    case 5:
    {
        ui->listWidget->addItem("(5)古堡内的神秘仪式");
        break;
    }
    case 6:
    {
        ui->listWidget->addItem("(6)血祭仪式与人口失踪事件");
        break;
    }
    case 7:
    {
        ui->listWidget->addItem("(7)神秘怪物");
        break;
    }
    case 8:
    {
        ui->listWidget->addItem("(8)人口失踪与邪教徒的血祭仪式");
        break;
    }
    case 9:
    {
        ui->listWidget->addItem("(9)十字架封印与女孩");
        break;
    }
    }
}
