#ifndef PLAYER_H
#define PLAYER_H
extern int num; //存档序号
#include<QMap>
#include"iteam.h"
int generateRandomNumber(int min,int max);//获取随机数
class player
{
public:
    player();
    player(int num);//根据序号读存档
    int level;//等级
    int exp;//当前等级的经验
    int gold;//金钱
    QString changeDate;//存档日期
    QMap<int,iteam> iteams;//道具

    bool checkFile(QString filePath,QString fileName);//检测存档是否存在
    void saveDate(QString filePath,QString fileName);//储存数据
    void loadDate(QString filePath,QString fileName);//读取数据
};
extern player *p;

#endif // PLAYER_H
