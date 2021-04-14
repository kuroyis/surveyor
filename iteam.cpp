#include "iteam.h"
#include<QDebug>
#include"player.h"
iteam::iteam()
{
    this->i_id=0;
    this->i_name="未知";
    this->i_num=1;
    this->i_gold=0;
    this->i_img=":/image/unknown.png";
    this->i_mes="未知";
}
iteam::iteam(int id)
{
    switch(id)
    {
    case 1://1 灵魂宝石
    {
        this->i_id=1;
        this->i_name="灵魂宝石";
        this->i_num=1;
        int temp=generateRandomNumber(1,5);
        if(temp==1)
        {
            this->i_img=":/image/iteam1_1.png";
        }
        else if(temp==2)
        {
            this->i_img=":/image/iteam1_2.png";
        }
        else if(temp==3)
        {
            this->i_img=":/image/iteam1_3.png";
        }
        else if(temp==4)
        {
            this->i_img=":/image/iteam1_4.png";
        }
        else if(temp==5)
        {
            this->i_img=":/image/iteam1_5.png";
        }
        this->i_gold=0;
        this->i_status=0;
        this->i_useable=0;
        this->i_mes="看起来精致漂亮的小玩意，是女神与你签订契约的道具，保护你的灵魂在肉身死亡时也不会被伤害，你无法明白其原理，也不需要明白。(可以用来往返于异界和家)";
        break;
    }
    case 2://钟表
    {
        this->i_id=2;
        this->i_name="时之表";
        this->i_num=1;
        this->i_gold=0;
        this->i_status=1;
        this->i_useable=0;
        this->i_img=":/image/iteam2.png";
        this->i_mes="男主角所拥有的神秘道具(可以将时间短暂回溯，可用3次)";
        break;
    }
    case 3://治疗药剂
    {
        this->i_id=3;
        this->i_name="治疗药剂";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam3.png";
        this->i_mes="神奇的治疗药剂，就是味道有些奇怪(可以快速饮用回复2HP)";
        break;
    }
    case 4://智力药剂
    {
        this->i_id=4;
        this->i_name="智力药剂";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam4.png";
        this->i_mes="神奇的智力药剂，这玩意比脑残片管用(可以短暂增加10点智力)";
        break;
    }
    case 5://理智药剂
    {
        this->i_id=5;
        this->i_name="理智药剂";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam5.png";
        this->i_mes="看起来有些眼熟的药剂(可以恢复10点理智)";
        break;
    }
    case 6://手绘地图
    {
        this->i_id=6;
        this->i_name="森林地图";
        this->i_num=1;
        this->i_img=":/image/iteam6.png";
        this->i_status=1;
        this->i_useable=0;
        this->i_mes="一份粗略的森林手绘地图,可以大致参考路线";
        break;
    }
    case 7://刀
    {
        this->i_id=7;
        this->i_name="小刀";
        this->i_num=1;
        this->i_gold=50;
        this->i_img=":/image/iteam7.png";
        this->i_status=0;
        this->i_useable=1;
        this->i_mes="野外生存必备";
        break;
    }
    case 8://指南针
    {
        this->i_id=8;
        this->i_name="指南针";
        this->i_num=1;
        this->i_gold=100;
        this->i_img=":/image/iteam8.png";
        this->i_status=0;
        this->i_useable=1;
        this->i_mes="上了年纪的指南针，也不知道还能用多久";
        break;
    }
    case 9://帐篷
    {
        this->i_id=9;
        this->i_name="简易帐篷";
        this->i_num=1;
        this->i_gold=100;
        this->i_img=":/image/iteam9.png";
        this->i_status=0;
        this->i_useable=1;
        this->i_mes="一个简易帐篷,可以容纳一个人,晚上有这个不管在哪也能度过了";
        break;
    }
    case 10://十字架
    {
        this->i_id=10;
        this->i_name="十字架";
        this->i_num=1;
        this->i_status=1;
        this->i_useable=1;
        this->i_img=":/image/iteam10.png";
        this->i_mes="一个银制十字架，看起来已经有了些年头";
        break;
    }
    case 11://酒
    {
        this->i_id=11;
        this->i_name="典藏酒";
        this->i_num=1;
        this->i_gold=100;
        this->i_status=0;
        this->i_useable=1;
        this->i_img=":/image/iteam11.png";
        this->i_mes="谁会想错过一瓶好酒呢";
        break;
    }
    case 12://魅力药剂
    {
        this->i_id=12;
        this->i_name="魅力药剂";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam12.png";
        this->i_mes="口服用，虽然不知道是通过什么方式(可以增加10点魅力)";
        break;
    }
    case 13://力量药剂
    {
        this->i_id=13;
        this->i_name="力量药剂";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam13.png";
        this->i_mes="此刻你感觉自己充满了力量(可以增加10点力量)";
        break;
    }
    case 14://敏捷水
    {
        this->i_id=11;
        this->i_name="敏捷水";
        this->i_num=1;
        this->i_gold=25;
        this->i_status=0;
        this->i_useable=0;
        this->i_img=":/image/iteam14.png";
        this->i_mes="唯快不破，为什么不是药剂，因为看起来像水(可以增加10点敏捷)";
        break;
    }
    }
}

