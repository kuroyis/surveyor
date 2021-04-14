#include "character.h"
#include"player.h"
#include"personscene.h"
character *ch=new character();

character::character()
{

}

character::character(int id)
{
    c_id=id;
    c_STR=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    c_CON=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    c_SIZ=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+6);
    c_DEX=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    c_APP=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    c_INT=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+6);
    c_POW=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    c_EDU=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+6);
    c_HP=12;
    c_SAN=c_POW;
    c_LUCK=5*(generateRandomNumber(1,6)+generateRandomNumber(1,6)+generateRandomNumber(1,6));
    if(id==1)//主角
    {
    c_gd=40+c_STR/5;//格斗
    c_cz=40+c_INT/5;//操纵
    c_js=40+c_APP/5;//交涉
    c_lt=50;//聆听
    c_zc=50;//侦察
    c_qx=50;//潜行
    c_sb=40+c_DEX/5;//闪避
    c_xlx=40+c_EDU/5;//心理学
    c_sc=40+c_CON/5;//生存
    c_jj=30;//急救
    c_point=0+p->level;
    c_img=":/image/character1.png";
    c_mes="普普通通的主角(拥有平衡的属性，无基础加点，有专属道具时之表)";
    c_iteams.insert(iteam(2).i_id,iteam(2));
    }
    else if(id==2)//警探
    {
    c_gd=15+c_STR/5;//格斗
    c_cz=10+c_INT/5;//操纵
    c_js=5+c_APP/5;//交涉
    c_lt=20;//聆听
    c_zc=25;//侦察
    c_qx=25;//潜行
    c_sb=15+c_DEX/5;//闪避
    c_xlx=0+c_EDU/5;//心理学
    c_sc=10+c_CON/5;//生存
    c_point=250+p->level;
    c_jj=30;//急救
    c_img=":/image/character2.png";
    c_mes="警探(偏向战斗探索的角色,初始携带武器手枪)";
//    c_iteams.insert(iteam(2).i_id,iteam(2));
    }
    else if(id==3)//马猴烧酒
    {
        c_SAN-=10;
        c_gd=15+c_STR/5;//格斗
        c_cz=10+c_INT/5;//操纵
        c_js=15+c_APP/5;//交涉
        c_lt=25;//聆听
        c_zc=20;//侦察
        c_qx=20;//潜行
        c_sb=15+c_DEX/5;//闪避
        c_xlx=0+c_EDU/5;//心理学
        c_sc=15+c_CON/5;//生存
        c_point=250+p->level;
        c_jj=25;//急救
        c_img=":/image/character3.png";
        c_mes="魔法少女(具有战斗和交涉能力，理智偏低，初始携带魔棒)";
    }
    temp[1]=c_STR;
    temp[2]=c_CON;
    temp[3]=c_SIZ;
    temp[4]=c_DEX;
    temp[5]=c_APP;
    temp[6]=c_INT;
    temp[7]=c_POW;
    temp[8]=c_EDU;
    temp[9]=c_HP;
    temp[10]=c_SAN;
    temp[11]=c_LUCK;
    temp[12]=c_gd;
    temp[13]=c_cz;
    temp[14]=c_js;
    temp[15]=c_lt;
    temp[16]=c_zc;
    temp[17]=c_qx;
    temp[18]=c_sb;
    temp[19]=c_xlx;
    temp[20]=c_sc;
    temp[21]=c_jj;
    temp[22]=c_point;
}
