#include "game.h"
#include "ui_game.h"
#include<QMovie>
#include<QTimer>
#include<QPainter>
#include"character.h"
#include"player.h"
#include"iteampushbutton.h"

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    this->setWindowIcon(QPixmap(":/image/mainmenu.png"));
    this->setWindowTitle("surveyor trip");
    //点击退出，退出程序
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });

    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent;color:white;font-size: 18pt}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color:transparent;color:white;font-size: 18pt}");
    ui->textEdit_4->setStyleSheet("background-color:rgba(0,0,0,0);\
                                                                  font-size: 18pt;\
                                                                  font-family: 'Copperplate Gothic Bold';\
                                                                  font-family: '楷体'");
    ui->textEdit_4->viewport()->setCursor(Qt::ArrowCursor);
    ui->textEdit_5->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->textEdit_5->viewport()->setCursor(Qt::ArrowCursor);
    ui->lineEdit_3->setStyleSheet("background-color:rgba(0,0,0,0);\
                                   font-size: 18pt;\
                                   font-family: 'Copperplate Gothic Bold';\
                                   font-family: '楷体'");
    ui->lineEdit_3->setCursor(Qt::ArrowCursor);
    ui->lineEdit_3->setTextColor(Qt::white);
    ui->lineEdit_3->hide();
    ui->sz->hide();
    personBtn->setParent(this);
    personBtn->move(20,30);
    helpBtn->setParent(this);
    helpBtn->move(950,30);
    diaBtn->setParent(this);
    diaBtn->move(840,420);
    qrBtn->setParent(this);
    qrBtn->move(620,435);
    gdate = new gamedate();
    connect(gdate,&gamedate::chooseBack0,[=](){
        emit chooseBack1();
        for(QMap<int,iteam>::iterator it=ch->c_iteams.begin();it!=ch->c_iteams.end();it++)
        {
            if((*it).i_status==0)
            {
                QMap<int,iteam>::iterator pos=p->iteams.find((*it).i_id);
                if(pos!=p->iteams.end())
                {
                    p->iteams[(*it).i_id].i_num++;
                }
                else
                {
                    p->iteams.insert((*it).i_id,(*it));
                }
            }
        }
        this->hide();
    });
    connect(qrBtn,&QPushButton::clicked,[=](){
        if(getgold>=0)
        {
        p->gold+=getgold;
        p->exp=(p->exp+(getgold/10))%20;
        p->level+=(p->exp+(getgold/10))/20;
        }
        for(QMap<int,iteam>::iterator it=ch->c_iteams.begin();it!=ch->c_iteams.end();it++)
        {
            if((*it).i_status==0)
            {
                QMap<int,iteam>::iterator pos=p->iteams.find((*it).i_id);
                if(pos!=p->iteams.end())
                {
                    p->iteams[(*it).i_id].i_num++;
                }
                else
                {
                    p->iteams.insert((*it).i_id,(*it));
                }
            }
        }
       emit chooseBack1();
    });
    connect(helpBtn,&QPushButton::clicked,[=](){
        QString mes;
        if(helpnum==1)
        {
            mes="注意:血量低于4时会进入濒死状态，理智低于20会陷入狂乱";
        }
        else if(helpnum==2)
        {
            mes="濒死状态时check难度乘二，血量回复时解除";
        }
        else if(helpnum==3)
        {
            mes="狂乱状态时选择支受限，理智回复时解除";
        }
        ui->lineEdit_3->setText(mes);
        ui->lineEdit_3->show();
         QTimer::singleShot(5000,this,[=]()
         {
             ui->lineEdit_3->hide();
             helpBtn->hide();
         });
    });
    connect(personBtn,&QPushButton::clicked,[=](){
        this->hide();
        gdate->move(this->frameGeometry().x(),this->frameGeometry().y());
        gdate->show();
        gdate->personEvent();
    });
    connect(gdate,&gamedate::chooseback,[=](){
        gdate->hide();
        this->move(gdate->frameGeometry().x(),gdate->frameGeometry().y());
        this->show();
        this->reshowEvent();
    });
    connect(diaBtn,&QPushButton::clicked,[=](){//下一步
        switch(gdate->turn)
        {
        case 0:
        {
          ui->pushButton_2->setText("直接进入森林调查");
          ui->pushButton_3->setText("先在城镇调查，休息一晚");
          ui->pushButton_2->show();
          ui->pushButton_3->show();
          if(ch->c_status==2)
          {
              ui->pushButton_3->hide();
              KLnum--;
              if(KLnum==0)
              {
                 ch->c_status=0;
              }
          }
          diaBtn->hide();
        break;
        }
        case 1:
        {
            ui->pushButton_2->setText("观察四周(check侦察)");
            ui->pushButton_3->setText("侧耳倾听(check聆听)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 2:
        {
            gdate->turn=10;
            this->reshowEvent();
            break;
        }
        case 3:
        {
            gdate->turn=10;
            this->reshowEvent();
            break;
        }
        case 4:
        {
            gdate->turn=23;
            this->reshowEvent();
            break;
        }
        case 5:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 6:
        {
            gdate->listEvent(1);
            QBnum++;
            gdate->turn=24;
            this->reshowEvent();
            break;
        }
        case 7:
        {
            gdate->listEvent(1);
            QBnum++;
            gdate->turn=24;
            this->reshowEvent();
            break;
        }
        case 8:
        {
            gdate->turn=24;
            this->reshowEvent();
            break;
        }
        case 9:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 10:
        {
            ui->pushButton_2->setText("试图用言语他讲道理(check交涉)");
            ui->pushButton_3->setText("直接用拳头跟他讲道理(check格斗)");
            ui->pushButton_4->setText("看看他想要什么(check心理学)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            ui->pushButton_4->show();
            if(ch->c_status==2)
            {
                ui->pushButton_2->hide();
                ui->pushButton_4->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 11:
        {
            gdate->listEvent(1);
            gdate->listEvent(2);
            ch->c_iteams.insert(iteam(6).i_id,iteam(6));
            QBnum+=2;
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 12:
        {
            gdate->listEvent(1);
            gdate->listEvent(2);
            ch->c_iteams.insert(iteam(6).i_id,iteam(6));
            QBnum+=2;
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 13:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 14:
        {
            picnum=4;
            gdate->turn=34;
            this->reshowEvent();
            break;
        }
        case 15:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 16:
        {
            gdate->listEvent(1);
            QBnum++;
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 17:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 18:
        {
            picnum=4;
            gdate->turn=34;
            this->reshowEvent();
            break;
        }
        case 19:
        {
            gdate->turn=35;
            this->reshowEvent();
            break;
        }
        case 20:
        {
            gdate->turn=35;
            this->reshowEvent();
            break;
        }
        case 21:
        {
            gdate->turn=35;
            this->reshowEvent();
            break;
        }
        case 22:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 23:
        {
            diaBtn->hide();
            ui->pushButton_3->setText("侧耳倾听(check聆听)");
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_2->hide();
                ui->pushButton_4->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            break;
        }
        case 24:
        {
            diaBtn->hide();
            ui->pushButton_2->setText("观察四周(check侦察))");
            ui->pushButton_2->show();
            if(ch->c_status==2)
            {
                ui->pushButton_2->hide();
                ui->pushButton_4->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            break;
        }
        case 25:
        {
            gdate->turn=10;
            this->reshowEvent();
            break;
        }
        case 26:
        {
            gdate->turn=10;
            this->reshowEvent();
            break;
        }
        case 27:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 28:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 29:
        {
            gdate->listEvent(1);
            QBnum++;
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 30:
        {
            gdate->listEvent(1);
            QBnum++;
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 31:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 32:
        {
            gdate->turn=33;
            this->reshowEvent();
            break;
        }
        case 33:
        {
            picnum=2;
            gdate->turn=36;
            this->reshowEvent();
            break;
        }
        case 34:
        {
            picnum=2;
            gdate->turn=36;
            this->reshowEvent();
            break;
        }
        case 35:
        {
            ui->pushButton_2->setText("试图用言语他讲道理(check交涉)");
            ui->pushButton_3->setText("直接用拳头跟他讲道理(check格斗)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_2->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 36:
        {
            ui->pushButton_2->setText("向西北方向走");
            ui->pushButton_3->setText("向正北走");
            ui->pushButton_4->setText("向东北方向走");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            ui->pushButton_4->show();
            if(ch->c_status==2)
            {
                ui->pushButton_2->hide();
                ui->pushButton_4->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 37:
        {
            ui->pushButton_2->setText("爬到树上看(check敏捷)");
            ui->pushButton_3->setText("砍个树看树轮(需要道具刀check力量)");
            ui->pushButton_4->setText("使用指南针(需要道具指南针)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            ui->pushButton_4->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                ui->pushButton_4->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 38:
        {
            picnum=6;
            gdate->turn=47;
            this->reshowEvent();
            break;
        }
        case 39:
        {
            picnum=6;
            gdate->turn=47;
            this->reshowEvent();
            break;
        }
        case 40:
        {
            gdate->turn=48;
            this->reshowEvent();
            break;
        }
        case 41:
        {
            gdate->turn=48;
            this->reshowEvent();
            break;
        }
        case 42:
        {
            picnum=12;
            if(gdate->time<10)
            {
            gdate->turn=67;
            }
            else{
                gdate->turn=69;
            }
            this->reshowEvent();
            break;
        }
        case 43:
        {
            picnum=12;
            if(gdate->time<10)
            {
            gdate->turn=67;
            }
            else{
                gdate->turn=69;
            }
            this->reshowEvent();
            break;
        }
        case 44:
        {
            gdate->turn=48;
            this->reshowEvent();
            break;
        }
        case 45:
        {
            gdate->turn=48;
            this->reshowEvent();
            break;
        }
        case 46:
        {
            picnum=12;
            if(gdate->time<10)
            {
            gdate->turn=67;
            }
            else{
                gdate->turn=69;
            }
            this->reshowEvent();
            break;
        }
        case 47:
        {
            gdate->listEvent(3);
            QBnum++;
            ui->pushButton_2->setText("去村庄看看");
            ui->pushButton_3->setText("还是别去了");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 48:
        {
            ui->pushButton_2->setText("(check幸运)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 49:
        {
            ui->pushButton_2->setText("冒险横渡(check体质)");
            ui->pushButton_3->setText("顺着河流寻找路(check幸运)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 50:
        {
            picnum=9;
            gdate->turn=56;
            this->reshowEvent();
            break;
        }
        case 51:
        {
            picnum=9;
            gdate->turn=56;
            this->reshowEvent();
            break;
        }
        case 52:
        {
            picnum=9;
            gdate->turn=56;
            this->reshowEvent();
            break;
        }
        case 53:
        {
            gdate->turn=101;
            this->reshowEvent();
            break;
        }
        case 54:
        {
            picnum=9;
            gdate->turn=56;
            this->reshowEvent();
            break;
        }
        case 55:
        {
            picnum=9;
            gdate->turn=56;
            this->reshowEvent();
            break;
        }
        case 56:
        {
            ui->pushButton_2->setText("生火守夜(check生存)");
            ui->pushButton_3->setText("做个帐篷(需要道具帐篷)");
            ui->pushButton_4->setText("找个山洞将就");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            ui->pushButton_4->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                ui->pushButton_2->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 57:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 58:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 59:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 60:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 61:
        {
            ui->pushButton_2->setText("进去看看(checkSAN)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 62:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 63:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 64:
        {
            picnum=5;
            gdate->turn=65;
            this->reshowEvent();
            break;
        }
        case 65:
        {
            picnum=7;
            gdate->turn=37;
            this->reshowEvent();
            break;
        }
        case 66:
        {
            ui->pushButton_2->setText("上前询问(check交涉)");
            ui->pushButton_3->setText("先观察一会儿(check心理学)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 67:
        {
            ui->pushButton_2->setText("在周围先观察观察(check侦察)");
            ui->pushButton_3->setText("从正面进去(check格斗)");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 68:
        {
            ui->pushButton_2->setText("寻找踪迹(check侦察)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 69:
        {
            ui->pushButton_2->setText("在周围先观察观察(check侦察)");
            ui->pushButton_3->setText("从正面进去");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 70:
        {
            picnum=13;
            gdate->turn=73;
            this->reshowEvent();
            break;
        }
        case 71:
        {
            gdate->turn=72;
            this->reshowEvent();
            break;
        }
        case 72:
        {
            ui->pushButton_2->setText("上前询问(check交涉)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 73:
        {
            gdate->listEvent(4);
            QBnum++;
            picnum=3;
            gdate->turn=74;
            this->reshowEvent();
            break;
        }
        case 74:
        {
            gdate->turn=75;
            this->reshowEvent();
            break;
        }
        case 75:
        {
            picnum=13;
            gdate->turn=76;
            this->reshowEvent();
            break;
        }
        case 76:
        {
            ui->pushButton_2->setText("寻找踪迹(check侦察)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 77:
        {
            picnum=12;
            gdate->turn=69;
            this->reshowEvent();
            break;
        }
        case 78:
        {
            picnum=12;
            gdate->turn=69;
            this->reshowEvent();
            break;
        }
        case 79:
        {
            ch->c_iteams.insert(10,iteam(10));
            ui->pushButton_2->setText("翻窗进入(check潜行)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 80:
        {
            ui->pushButton_2->setText("翻窗进入(check潜行)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 81:
        {
            picnum=14;
            gdate->turn=86;
            this->reshowEvent();
            break;
        }
        case 82:
        {
            gdate->turn=101;
            this->reshowEvent();
            break;
        }
        case 83:
        {
            gdate->turn=101;
            this->reshowEvent();
            break;
        }
        case 84:
        {
            picnum=14;
            gdate->turn=86;
            this->reshowEvent();
            break;
        }
        case 85:
        {
            gdate->turn=101;
            this->reshowEvent();
            break;
        }
        case 86:
        {
            gdate->listEvent(5);
            QBnum++;
            ui->pushButton_2->setText("解析(check智力)");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 87:
        {
            gdate->listEvent(6);
            QBnum++;
            end=1;
            gdate->turn=102;
            this->reshowEvent();
            break;
        }
        case 88:
        {
            end=1;
            gdate->turn=102;
            this->reshowEvent();
            break;
        }
        case 89:
        {
            ch->c_iteams.insert(10,iteam(10));
            gdate->turn=91;
            this->reshowEvent();
            break;
        }
        case 90:
        {
            gdate->turn=91;
            this->reshowEvent();
            break;
        }
        case 91:
        {
            ui->pushButton_2->setText("进入");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 92:
        {
            gdate->listEvent(5);
            QBnum++;
            ui->pushButton_2->setText("马上上前");
            ui->pushButton_3->setText("继续观察");
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            if(ch->c_status==2)
            {
                ui->pushButton_3->hide();
                KLnum--;
                if(KLnum==0)
                {
                   ch->c_status=0;
                }
            }
            diaBtn->hide();
            break;
        }
        case 93:
        {
            gdate->listEvent(7);
            QBnum++;
            ui->pushButton_2->setText("checkSAN");
            ui->pushButton_2->show();
            diaBtn->hide();
            break;
        }
        case 94:
        {
            gdate->turn=96;
            this->reshowEvent();
            break;
        }
        case 95:
        {
            gdate->turn=93;
            this->reshowEvent();
            break;
        }
        case 96:
        {
            gdate->listEvent(8);
            gdate->listEvent(9);
            QBnum+=2;
            end=2;
            gdate->turn=102;
            this->reshowEvent();
            break;
        }
        case 97:
        {
            gdate->turn=99;
            this->reshowEvent();
            break;
        }
        case 98:
        {
            gdate->turn=101;
            this->reshowEvent();
            break;
        }
        case 99:
        {
            gdate->turn=102;
            this->reshowEvent();
            break;
        }
        }
    });
    ui->pushButton->setText("急救(check急救)");
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        jjnum--;
        switch(check(ch->c_jj))
        {
        case 0:
        {
            ch->c_HP+=3;
            QString mes="1d100=";
            mes+=QString::number(point);
            mes+="(大成功)\n回复3血";
            ui->textEdit_4->setText(mes);
            ui->pushButton->hide();
            if(ch->c_HP>4)
            {
                ch->c_status=0;
            }
            break;
        }
        case 1:
        {
            QString mes="1d100=";
            mes+=QString::number(point);
            mes+="(成功)\n回复2血";
            ui->textEdit_4->setText(mes);
            ui->pushButton->hide();
            ch->c_HP+=2;
            if(ch->c_HP>4)
            {
                ch->c_status=0;
            }
            break;
        }
        case 2:
        {
            QString mes="1d100=";
            mes+=QString::number(point);
            mes+="(失败)\n没有回复血量";
            ui->pushButton->hide();
            ui->textEdit_4->setText(mes);
            break;
        }
        case 3:
        {
            QString mes="1d100=";
            mes+=QString::number(point);
            mes+="(大失败)\n治疗不当导致大出血，打出GG";
            ui->textEdit_4->setText(mes);
            ui->pushButton->hide();
            diaBtn->hide();
            showEnd();
        }
        }
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        switch(gdate->turn)
            {
        case 0:
        {
            gdate->turn=36;
            this->reshowEvent();
            break;
        }
        case 1:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
                gdate->turn=2;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=3;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=4;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=5;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 10:
        {
            switch(check(ch->c_js/2))
            {
            case 0:
            {
                gdate->turn=11;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=12;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=13;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=14;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 24:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
                gdate->turn=25;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=26;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=27;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=28;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 35:
        {
            switch(check(ch->c_js/2))
            {
            case 0:
            {
                gdate->turn=11;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=12;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=13;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=14;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 36:
        {
            picnum=8;
            gdate->time+=2;
            gdate->turn=49;
            this->reshowEvent();
            break;
        }
        case 37:
        {
            picnum=5;
            switch(check(ch->c_DEX))
            {
            case 0:
            {
                gdate->turn=38;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->time++;
                gdate->turn=39;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->time++;
               gdate->turn=40;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->time++;
                gdate->turn=41;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 47:
        {
            picnum=11;
            gdate->turn=66;
            this->reshowEvent();
            break;
        }
        case 48:
        {
            switch(check(ch->c_LUCK))
            {
            case 0:
            {
                if(gdate->time<10)
                {
                   picnum=11;
                   gdate->turn=66;
                }
                else
                {
                    picnum=13;
                    gdate->turn=68;
                }
                this->reshowEvent();
                break;
            }
            case 1:
            {
                if(gdate->time<10)
                {
                   picnum=11;
                   gdate->turn=66;
                }
                else
                {
                    picnum=13;
                    gdate->turn=68;
                }
                this->reshowEvent();
                break;
            }
            case 2:
            {
                picnum=12;
                if(gdate->time<10)
                {
                gdate->turn=67;
                }
                else{
                    gdate->turn=69;
                }
                this->reshowEvent();
                break;
            }
            case 3:
            {
                picnum=12;
                if(gdate->time<10)
                {
                gdate->turn=67;
                }
                else{
                    gdate->turn=69;
                }
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 49:
        {
            picnum=5;
            gdate->time++;
            switch(check(ch->c_CON))
            {
            case 0:
            {
                gdate->turn=50;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->time++;
                gdate->turn=51;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->time++;
                gdate->turn=52;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->time++;
                gdate->turn=53;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 56:
        {
            switch(check(ch->c_sc))
            {
            case 0:
            {
                gdate->turn=57;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=57;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=58;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=59;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 61:
        {
            switch(check(ch->c_SAN))
            {
            case 0:
            {
                gdate->turn=62;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=62;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=63;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=64;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 66:
        {
            gdate->turn=70;
            this->reshowEvent();
            break;
        }
        case 67:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
                gdate->turn=79;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=79;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=80;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=80;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 68:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
                gdate->turn=77;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=77;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=78;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=78;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 69:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
               gdate->turn=89;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=89;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=90;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=90;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 72:
        {
            gdate->turn=70;
            this->reshowEvent();
            break;
        }
        case 76:
        {
            switch(check(ch->c_zc))
            {
            case 0:
            {
                gdate->turn=77;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=77;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=78;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=78;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 79:
        {
            switch(check(ch->c_qx))
            {
            case 0:
            {
                gdate->turn=84;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=84;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=85;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=85;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 80:
        {
            switch(check(ch->c_qx))
            {
            case 0:
            {
                gdate->turn=84;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=84;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=85;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=85;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 86:
        {
            switch(check(ch->c_INT))
            {
            case 0:
            {
                gdate->turn=87;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=87;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=88;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=88;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 91:
        {
            if(gdate->time<100)
            {
                picnum=14;
                gdate->turn=92;
            }
            else
            {
                picnum=15;
               gdate->turn=93;
            }
            break;
        }
        case 92:
        {
            QMap<int,iteam>::iterator pos=ch->c_iteams.find(10);
            if(pos!=p->iteams.end())
            {
                gdate->turn=94;
            }
            else
            {
                gdate->turn=95;
            }
            this->reshowEvent();
            break;
        }
        case 93:
        {
            switch(check(ch->c_SAN))
            {
            case 0:
            {
                gdate->turn=97;
                this->reshowEvent();
                break;
            }
            case 1:
            {
               gdate->turn=97;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=98;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=98;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        }
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        switch(gdate->turn)
            {
        case 0:
        {
            picnum=3;
            gdate->turn=1;
            this->reshowEvent();
            break;
        }
        case 1:
        {
            switch(check(ch->c_lt))
            {
            case 0:
            {
                gdate->turn=6;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=7;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=8;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=9;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 10:
        {
            switch(check(ch->c_gd/2))
            {
            case 0:
            {
                gdate->turn=15;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=16;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=17;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=18;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 23:
        {
            switch(check(ch->c_lt))
            {
            case 0:
            {
                gdate->turn=29;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=30;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=31;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=32;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 35:
        {
            switch(check(ch->c_gd/2))
            {
            case 0:
            {
                gdate->turn=15;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=16;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=17;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=18;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 36:
        {
            picnum=8;
            gdate->time+=1;
            gdate->turn=49;
            this->reshowEvent();
            break;
        }
        case 37:
        {
            gdate->time++;
            QMap<int,iteam>::iterator pos=ch->c_iteams.find(7);
            if(pos!=ch->c_iteams.end())
            {
            switch(check(ch->c_STR))
            {
            case 0:
            {
                gdate->turn=42;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=43;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=44;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=45;
                this->reshowEvent();
                break;
            }
            }
            }
            break;
        }
        case 47:
        {
            picnum=12;
            if(gdate->time<10)
            {
            gdate->turn=67;
            }
            else{
                gdate->turn=69;
            }
            this->reshowEvent();
            break;
        }
        case 49:
        {
            picnum=5;
            switch(check(ch->c_LUCK))
            {
            case 0:
            {
                gdate->time++;
                gdate->turn=54;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->time+=2;
                gdate->turn=54;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->time+=5;
                gdate->turn=55;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->time+=5;
                gdate->turn=55;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 56:
        {
            QMap<int,iteam>::iterator pos=ch->c_iteams.find(9);
            if(pos!=ch->c_iteams.end())
            {
            gdate->turn=60;
            this->reshowEvent();
            }
            break;
        }
        case 66:
        {
            gdate->turn=71;
            this->reshowEvent();
            break;
        }
        case 67:
        {
            switch(check(ch->c_gd))
            {
            case 0:
            {
                gdate->turn=81;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=82;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=83;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=83;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 92:
        {
            picnum=15;
            gdate->turn=93;
            this->reshowEvent();
            break;
        }
        }
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        switch(gdate->turn)
        {
            case 10:
        {
            switch(check(ch->c_xlx))
            {
            case 0:
            {
                gdate->turn=19;
                this->reshowEvent();
                break;
            }
            case 1:
            {
                gdate->turn=20;
                this->reshowEvent();
                break;
            }
            case 2:
            {
                gdate->turn=21;
                this->reshowEvent();
                break;
            }
            case 3:
            {
                gdate->turn=22;
                this->reshowEvent();
                break;
            }
            }
            break;
        }
        case 36:
        {
            picnum=8;
            gdate->time+=2;
            gdate->turn=49;
            this->reshowEvent();
            break;
        }
        case 37:
        {
            QMap<int,iteam>::iterator pos=ch->c_iteams.find(8);
            if(pos!=ch->c_iteams.end())
            {
                gdate->turn=46;
            }
            break;
        }
        case 56:
        {
            picnum=10;
            gdate->turn=61;
            this->reshowEvent();
            break;
        }
        }
    });
}

game::~game()
{
    delete ui;
}

void game::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    switch(picnum)
    {
    case 1:
    {
        pix.load(":/image/saveselect.png");
        break;
    }
    case 2:
    {
        pix.load(":/image/map1_1.png");
        break;
    }
    case 3:
    {
        pix.load(":/image/map1_2.png");
        break;
    }
    case 4:
    {
        pix.load(":/image/map1_3.png");
        break;
    }
    case 5:
    {
        pix.load(":/image/map1_4.png");
        break;
    }
    case 6:
    {
        pix.load(":/image/map1_5.png");
        break;
    }
    case 7:
    {
        pix.load(":/image/map1_6.png");
        break;
    }
    case 8:
    {
        pix.load(":/image/map1_7.png");
        break;
    }
    case 9:
    {
        pix.load(":/image/map1_8.png");
        break;
    }
    case 10:
    {
        pix.load(":/image/map1_9.png");
        break;
    }
    case 11:
    {
        pix.load(":/image/map1_10.png");
        break;
    }
    case 12:
    {
        pix.load(":/image/map1_11.png");
        break;
    }
    case 13:
    {
        pix.load(":/image/map1_12.png");
        break;
    }
    case 14:
    {
        pix.load(":/image/map1_13.png");
        break;
    }
    case 15:
    {
        pix.load(":/image/map1_14.png");
        break;
    }
    default:
    {
        break;
    }
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void game::joinEvent()
{
    ui->label_5->hide();
    ui->textEdit_5->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    diaBtn->hide();
    ui->textEdit_4->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->label_4->hide();
    helpBtn->hide();
    qrBtn->hide();
    personBtn->hide();
    QMovie *movie = new QMovie(":/image/cy.gif");
    ui->into->setMovie(movie);
    //播放gif
    movie->start();
    ui->into->show();
    QTimer::singleShot(4400,this,[=](){
    movie->stop();
    ui->into->hide();
    this->reshowEvent();
    });
}

void game::reshowEvent()
{
    update();
    ui->label->show();
    ui->label_2->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    personBtn->show();
    QString mes;
    mes=QString::number(ch->c_HP);
    if(ch->c_HP<=4)
    {
        mes+="(濒死)";
        helpnum=2;
        helpBtn->show();
        if(jjnum!=0)
        {
            ui->pushButton->show();
        }
    }
    ui->lineEdit->setText(mes);
    mes=QString::number(ch->c_SAN);
    if(ch->c_SAN<=ch->c_POW/2)
    {
        mes+="(狂乱)";
        helpnum=3;
        helpBtn->show();
    }
    ui->lineEdit_2->setText(mes);
    diaBtn->show();
    ui->label_4->show();
    ui->textEdit_4->raise();
    ui->textEdit_4->show();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    switch(gdate->turn)
    {
    case 0:
    {
        ui->textEdit_4->setText("你来到了城镇和森林的交界处,\n但是天色已经渐暗了");
        break;
    }
    case 1:
    {
        ui->textEdit_4->setText("你进入了一家酒馆，这个时间点还有不少人在这喝酒聊天，\n或许能在这儿获取些信息");
        break;
    }
    case 2:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你一眼就看到酒馆里一处不显眼的角落，\n一个可疑的黑色斗篷人坐在那里";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 3:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n观察了几遍后，你将目光锁定在一处角落，\n一个可疑的黑色斗篷人坐在那里";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 4:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n观察了几遍后，你似乎没有发现值得关注的东西";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 5:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n很普通的酒吧，没有什么好观察的，还是去休息吧";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 6:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你听到不少信息，包括最近的人员失踪";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 7:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n酒馆的信息很杂，但你确实听到了有关人员失踪的信息";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 8:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n酒馆的信息很杂，你并没有听到了有关信息";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 9:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n酒馆的信息很杂，你决定直接去睡觉";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 10:
    {
        ui->textEdit_4->setText("简单的谈话后，你知道这人是个情报贩子，\n可情报贩子不会轻易交出情报");
        break;
    }
    case 11:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(大成功)\n你高超的交涉能力直接让情报贩子拜服，入手森林地图和关键情报";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 12:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(成功)\n你花费一番口舌让情报贩子认同了你，入手森林地图和关键情报";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 13:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(失败)\n你花费了时间却并没能打动情报贩子";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 14:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(失败)\n你被当成傻瓜赶出了酒馆,没法留宿了";
        picnum=4;
        ch->c_SAN-=5;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 15:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(大成功)\n你把这个守财奴打得落花流水，让他懂得人情世故，\n入手森林地图和关键情报";
        gdate->listEvent(1);
        gdate->listEvent(2);
        ch->c_iteams.insert(iteam(6).i_id,iteam(6));
        QBnum+=2;
        ui->textEdit_4->setText(mes);
        break;
    }
    case 16:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(成功)\n你把这个守财奴教训了一顿，\n入手关键情报";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 17:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(失败)\n情报贩子从后门逃跑了,你没有能获得有用信息";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 18:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(大失败)\n情报贩子身后出现了几个大汉,你被打了一顿丢出了酒馆";
        picnum=4;
        ch->c_HP-=2;
        if(ch->c_HP<4)
        {
            ch->c_status=1;
            helpnum=2;
            helpBtn->show();
            if(jjnum!=0)
            {
                ui->pushButton->show();
            }
        }
        ch->c_SAN-=5;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 19:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n通过桌上的不少酒杯和喝剩一半的酒，你判断他可能期望着一瓶好酒";
        QMap<int,iteam>::iterator pos=ch->c_iteams.find(11);
        if(pos!=ch->c_iteams.end())
        {
            ch->c_iteams[11].i_useable=0;
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 20:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n通过桌上的不少酒杯，你判断他也许是个酒鬼";
        QMap<int,iteam>::iterator pos=ch->c_iteams.find(11);
        if(pos!=ch->c_iteams.end())
        {
            ch->c_iteams[11].i_useable=0;
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 21:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你没能看透情报贩子的狡猾";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 22:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n你的眼神让他觉得失礼，情报贩子直接离开了";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 23:
    {
        ui->textEdit_4->setText("重新审视这家酒馆，这个时间点还有不少人在这喝酒聊天，\n或许能在这儿获取些信息");
        break;
    }
    case 24:
    {
        ui->textEdit_4->setText("重新审视这家酒馆，这个时间点还有不少人在这喝酒聊天，\n或许能在这儿获取些信息");
        break;
    }
    case 25:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你一眼就看到酒馆里一处不显眼的角落，\n一个可疑的黑色斗篷人坐在那里";
        ui->textEdit_4->setText(mes);
        gdate->turn=10;
        break;
    }
    case 26:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n观察了几遍后，你将目光锁定在一处角落，\n一个可疑的黑色斗篷人坐在那里";
        ui->textEdit_4->setText(mes);
        gdate->turn=10;
        break;
    }
    case 27:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n观察了几遍后，你似乎没有发现值得关注的东西";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 28:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n很普通的酒吧，没有什么好观察的，还是去休息吧";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 29:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你听到不少信息，包括最近的人员失踪，获得关键情报";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 30:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n酒馆的信息很杂，但你确实听到了有关人员失踪的信息，获得关键情报";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 31:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n酒馆的信息很杂，你并没有听到了有关信息";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 32:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n酒馆的信息很杂，你决定直接去睡觉";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 33:
    {
        gdate->time++;
        ui->textEdit_4->setText("现在你可以睡个好觉了");
        break;
    }
    case 34:
    {
        gdate->time++;
        ui->textEdit_4->setText("可怜的你只能在大街上过夜了");
        break;
    }
    case 35:
    {
        ui->textEdit_4->setText("接下来该怎么做");
        break;
    }
    case 36:
    {
        gdate->time++;
        ui->textEdit_4->setText("选择前进的方向吧");
        break;
    }
    case 37:
    {
        ui->textEdit_4->setText("经过一段时间的穿行，你在仿佛无尽的树海中迷路了，\n选择应对方法");
        break;
    }
    case 38:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你选了棵最高的树，一口气爬到了顶";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 39:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你顺利的爬到了树顶";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 40:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n身手不好的你没能爬到树顶";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 41:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n你选了棵最高的树，却狠狠的摔了下来";
        ch->c_HP-=9;
        if(ch->c_HP<4)
        {
            ch->c_status=1;
            helpnum=2;
            helpBtn->show();
            if(jjnum!=0)
            {
                ui->pushButton->show();
            }
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 42:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你找到了棵裸露的树轮，省去了多余的功夫";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 43:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你成功的砍倒了树，通过树轮辨别了方向，\n这回可不要再迷路了";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 44:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你花费了半天时间却没能砍倒树，看来力气还是太弱了";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 45:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n你花费了半天时间不仅没能砍倒树，还把小刀给弄坏了";
        ch->c_iteams.remove(7);
        ui->textEdit_4->setText(mes);
        break;
    }
    case 46:
    {
        ui->textEdit_4->setText("通过指南针轻松辨别方向\n科技改变一切");
        break;
    }
    case 47:
    {
        ui->textEdit_4->setText("在树顶俯瞰森林，你居然发现了一处村庄");
        break;
    }
    case 48:
    {
        ui->textEdit_4->setText("仍然迷路的你只能将希望寄托于运气之上");
        break;
    }
    case 49:
    {
        ui->textEdit_4->setText("走了一段路后，一条河流横拦在你的面前\n该如何办呢");
        break;
    }
    case 50:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你在极度兴奋的情况下,直接横渡了河流";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 51:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n经过一番努力,你总算渡过了河流";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 52:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你虽然过了河，但也因此生病";
        ui->textEdit_4->setText(mes);
        ch->c_HP-=2;
        if(ch->c_HP<4)
        {
            ch->c_status=1;
            helpnum=2;
            helpBtn->show();
            if(jjnum!=0)
            {
                ui->pushButton->show();
            }
        }
        break;
    }
    case 53:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n不要拿湍急的河流开玩笑，这会要了你的小命";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 54:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n走了没多远你就发现了一条小船,这或许能帮你更快过河";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 55:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n走了很远你终于到了河对面";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 56:
    {
        ui->textEdit_4->setText("天色已经不早了，看样子得想办法在森林过夜\n如何度过危险的夜晚");
        break;
    }
    case 57:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你靠着丰富的生存经验成功升起了火";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 58:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n也许是方法不对，你怎么也没能升起火\n就这么过了一夜";
        ch->c_SAN-=5;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 59:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n你不仅没能升起火，发出的声响还引来了野兽\n在与野兽的搏斗中你受了伤，虽然最后逃脱了，但这一夜也过去了";
        ch->c_HP-=2;
        if(ch->c_HP<4)
        {
            ch->c_status=1;
            helpnum=2;
            helpBtn->show();
            if(jjnum!=0)
            {
                ui->pushButton->show();
            }
        }
        ch->c_SAN-=5;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 60:
    {
        ui->textEdit_4->setText("早有准备的你在帐篷里睡了个好觉");
        break;
    }
    case 61:
    {
        ui->textEdit_4->setText("你发现了一处山洞，里面很黑什么也看不到");
        break;
    }
    case 62:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n只是一群蝙蝠从洞里发出，并没能吓到你";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 63:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你被洞里突然飞出的蝙蝠吓了一跳,这觉可能没那么安稳了";
        ch->c_SAN-=5;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 64:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大失败)\n洞里成千的红色眼睛让你胆寒，深处传来的怪异声响让你心神不宁\n没能睡个好觉";
        ch->c_SAN-=10;
        if(ch->c_SAN<20)
        {
            ch->c_status=2;
            helpnum=3;
            helpBtn->show();
        }
        ui->textEdit_4->setText(mes);
        break;
    }
    case 65:
    {
        gdate->time++;
        ui->textEdit_4->setText("不管如何,第二天的太阳照常升起，该继续前进了");
        break;
    }
    case 66:
    {
        gdate->time++;
        ui->textEdit_4->setText("你在路上遇到了一个可爱的小女孩");
        break;
    }
    case 67:
    {
        gdate->time++;
        ui->textEdit_4->setText("你来到了一处古堡面前，古堡好像被什么人看守着");
        break;
    }
    case 68:
    {
        gdate->time++;
        ui->textEdit_4->setText("你来到了一处原始的村庄，你四处检查发现村子里空无一人，但家具看起来是有人不久前用过的");
        break;
    }
    case 69:
    {
        gdate->time++;
        ui->textEdit_4->setText("你来到了一处古堡面前,古堡阴森的可怕");
        break;
    }
    case 70:
    {
        ui->textEdit_4->setText("小女孩单纯活泼，很热心的和你交谈\n并打算带你去村庄做客");
        break;
    }
    case 71:
    {
        ui->textEdit_4->setText("小女孩看起来天真无邪,让你不禁感叹这个时代还有这样的孩子");
        break;
    }
    case 72:
    {
        ui->textEdit_4->setText("接下来怎么做");
        break;
    }
    case 73:
    {
        ui->textEdit_4->setText("小女孩带你来到了一个看起来很贫穷的村庄，村子有不少人\n,奇怪的是其他人都仿佛故意避开了你，你能从中感到些许敌意");
        break;
    }
    case 74:
    {
        ui->textEdit_4->setText("小女孩将你带到家中做客，你了解到小女孩是孤儿被村里人收养，\n小女孩告诉你村里的人其实都很好，只是没见过外来者有些谨慎");
        break;
    }
    case 75:
    {
        ui->textEdit_4->setText("小女孩为你准备好了菜肴和客房,让人不禁感叹孩子的懂事和能干\n小女孩好奇的向你询问了外面的事情，融洽的交谈使你压下了疑惑");
        break;
    }
    case 76:
    {
        ui->textEdit_4->setText("凌晨你仿佛听到了一些动静，等到你醒来后却发现村子里空无一人");
        break;
    }
    case 77:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你很快发现了地上的马车印,延展向森林另一边\n你赶紧跟了上去";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 78:
    {
        gdate->time+=100;
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你花费了半天时间才从地上找到不明显的马车痕\n没时间犹豫了，你直接跟了上去";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 79:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你在古堡周围转了一圈，发现了一处开着的窗户和被丢在外面的十字架";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 80:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你在古堡周围转了一圈，只发现了一处开着的窗户";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 81:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(大成功)\n你凭借高超的武艺，大摇大摆的打败所有守卫进入了古堡";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 82:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你成功的击败了面前的两个守卫，可是更多的人出现将你包围了\n双拳难敌四手，你最终被击败昏倒了过去";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 83:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你根本不是守卫的对手，直接被一棍子撂倒了";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 84:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你成功潜入了";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 85:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你在翻越窗户的时候碰倒了柜子，一大群人马上把你包围了，\n双拳难敌四手，你马上被击倒昏了过去";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 86:
    {
        ui->textEdit_4->setText("你进入房间，地上的血色魔法阵和中间的棺材马上吸引了你的视线");
        break;
    }
    case 87:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你分析出了仪式和人口失踪的关系，决定毁了魔法阵并回报这件事";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 88:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n虽然不知道具体发生了什么，但这魔法阵一看就不像好东西，\n你决定毁了魔法阵并回报这件事";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 89:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n你在古堡周围转了一圈，发现了一处开着的窗户和被丢在外面的十字架";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 90:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n你在古堡周围转了一圈，并没有任何发现";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 91:
    {
        ui->textEdit_4->setText("接下来该怎么做");
        break;
    }
    case 92:
    {
        ui->textEdit_4->setText("你进入房间，周围是散落了一地的黑色披风和血迹，大厅中间的血色魔法阵和小女孩马上吸引了你的视线");
        break;
    }
    case 93:
    {
        ui->textEdit_4->setText("只听见一声古怪的叫声，一个怪物出现在了你的面前");
        break;
    }
    case 94:
    {
        ui->textEdit_4->setText("看着女孩痛苦的表情，你毅然冲进了魔法阵,\n魔法阵上出现诡异手向你袭来，这时你手中的十字架发出了光芒");
        break;
    }
    case 95:
    {
        ui->textEdit_4->setText("看着女孩痛苦的表情，你毅然冲进了魔法阵,\n魔法阵上出现诡异手却将你绑在原地");
        break;
    }
    case 96:
    {
        ui->textEdit_4->setText("光芒让邪恶退散，你将十字架挂在女孩胸前，她的神情总算好转了");
        break;
    }
    case 97:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(成功)\n可怕的怪物并没有使你的意志动摇\n接着怪物向你发起了攻击";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 98:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n奇异的声音直冲进你的大脑，你失去了神智";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 99:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="/2(成功)\n你险而又险的躲过了这次攻击,而怪物已经再次来到你的面前";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 100:
    {
        mes="1d100=";
        mes+=QString::number(point);
        mes+="(失败)\n只一击你就失去了意识";
        ui->textEdit_4->setText(mes);
        break;
    }
    case 101://GG
    {
        ui->textEdit_4->setText("GG");
        diaBtn->hide();
        showEnd();
        break;
    }
    case 102://win
    {
        ui->textEdit_4->setText("事件结束");
        diaBtn->hide();
        showEnd();
        break;
    }
    case 103:
    {
        end=3;
        ui->textEdit_4->setText("你身上的十字架突然发出强烈的光芒将怪物击退，你趁机逃离了这个恐怖的地方");
        diaBtn->hide();
        showEnd();
        break;
    }
    }

}

int game::check(int xx)
{
    QMovie *movie = new QMovie(":/image/check.gif");
    ui->sz->setMovie(movie);
    //播放gif
    movie->start();
    ui->sz->show();
    ui->sz->raise();
    QTimer::singleShot(2000,this,[=](){
    movie->stop();
    ui->sz->hide();
    });
    if(ch->c_status==1)
    {
        point=2*generateRandomNumber(0,100);
    }
    else{
    point=generateRandomNumber(0,100);
    }
    if(point==0){
        return 0;
    }
    else if(0<point&&point<=xx)
    {
        return 1;
    }
    else if(xx<point&&point<100)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void game::showEnd()
{
    QString mes;
    if(end==0)
    {
        mes="事件失败:";
        mes+="\ndead     -10";
        getgold-=10;
    }
    else if(end==1)
        {
        mes="事件成功:";
        mes+="\nnormalend     +50";
        getgold+=50;
    }
    else if(end==2)
    {
        mes="拯救成功:";
        mes+="\ntrueend     +100";
        getgold+=100;
    }
    else if(end==3)
    {
        mes="死里逃生:";
        mes+="\nhideend     +100";
        getgold+=100;
    }
    mes+="\n关键信息x";
    mes+=QString::number(QBnum);
    mes+="     +";
    mes+=QString::number(10*QBnum);
    getgold+=10*QBnum;
    ui->textEdit_5->setText(mes);
    ui->label_5->show();
    ui->textEdit_5->show();
    qrBtn->show();
}
