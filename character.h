#ifndef CHARACTER_H
#define CHARACTER_H
#include<QString>
#include<QMap>
#include"iteam.h"
#include"map.h"

class character
{
public:
    character();
    character(int id);
    int c_id;
    int c_STR;//力量
    int c_CON;//体质
    int c_SIZ;//体型
    int c_DEX;//敏捷
    int c_APP;//外貌
    int c_INT;//智力
    int c_POW;//意志
    int c_EDU;//教育
    int c_HP;//体力
    int c_SAN;//理智
    int c_LUCK;//幸运
    int c_gd;//格斗
    int c_cz;//操纵
    int c_js;//交涉
    int c_lt;//聆听
    int c_zc;//侦察
    int c_qx;//潜行
    int c_sb;//闪避
    int c_xlx;//心理学
    int c_sc;//生存
    int c_jj;//急救
    int c_point;//点数
    int temp[23];//初始属性
    QString c_img;//人物图片
    QString c_mes;//人物描述
    QMap<int,iteam> c_iteams;//携带道具
    map *c_map;//当前地图
    int c_levelnum;//当前难度
    int c_status=0;//人物状态 0为正常 1为濒死 2为狂乱
};
extern character *ch;

#endif // CHARACTER_H
