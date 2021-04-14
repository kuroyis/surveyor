#ifndef ITEAM_H
#define ITEAM_H
#include<QString>

class iteam
{
public:
    iteam();
    iteam(int id);
    QString i_name;//道具名
    int i_id;//道具id
    int i_num;//道具数量
    int i_gold;//道具价格 0为不可交易
    int i_status;//0为全局道具 1为临时道具
    int i_useable;//0为可使用 1为不可使用
    QString i_mes;//道具描述
    QString i_img;//道具图片路径
};

#endif // ITEAM_H

