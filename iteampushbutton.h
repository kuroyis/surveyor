#ifndef ITEAMPUSHBUTTON_H
#define ITEAMPUSHBUTTON_H

#include <QPushButton>
#include"iteam.h"

class iteamPushButton : public QPushButton
{
public:
    iteamPushButton();
    iteamPushButton(iteam tempiteam);
    iteam tempIteam;//按钮对应的道具
    int status=0;//选中状态 1为选中 0为未选中
};

#endif // ITEAMPUSHBUTTON_H
