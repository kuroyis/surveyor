#include "player.h"
#include<QFile>
#include<QFileInfo>
#include<QDir>
#include<QDebug>
#include<QStringList>
#include<QMap>
#include<QRandomGenerator>
int num=0;
player *p=new player();
player::player()
{
}

void player::saveDate(QString filePath,QString fileName){
    QDir tempDir;
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"不存在该路径";
        tempDir.mkpath(filePath);
    }
    tempDir.setCurrent(filePath);
    QFile *tempFile = new QFile;
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"打开文件失败";
        }
    QString str;
    str=QString::number(this->level);
    QByteArray temp=str.toUtf8();
    tempFile->write(temp);
    tempFile->write("\n");
    str=QString::number(this->exp);
    temp=str.toUtf8();
    tempFile->write(temp);
    tempFile->write("\n");
    str=QString::number(this->gold);
    temp=str.toUtf8();
    tempFile->write(temp);
    tempFile->write("\n");
    QFileInfo fileinfo(*tempFile);
    temp=fileinfo.metadataChangeTime().toString("yyyy/MM/dd hh:mm:ss").toUtf8();
    tempFile->write(temp);
    tempFile->write("\n");
    for(QMap<int,iteam>::Iterator it=this->iteams.begin();it!=this->iteams.end();it++)
    {
        str=QString::number((*it).i_id);
        temp=str.toUtf8();
        tempFile->write(temp);
        tempFile->write("\n");
     }
    tempFile->close();
    tempDir.setCurrent(currentDir);
}

bool player::checkFile(QString filePath,QString fileName)
{
    QDir tempDir;
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"不存在该路径";
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        return true;
    }
    return false;
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
}

void player::loadDate(QString filePath, QString fileName)
{
    if(this->checkFile(filePath,fileName))
    {
        QDir tempDir;
        tempDir.setCurrent(filePath);
        QFile *tempFile = new QFile;
        tempFile->setFileName(fileName);
        if(!tempFile->open(QIODevice::ReadOnly|QIODevice::Text)){
                qDebug()<<"打开文件失败";
            }
        QByteArray temp;
        temp=tempFile->readLine();
        this->level=temp.toInt();
        temp=tempFile->readLine();
        this->exp=temp.toInt();
        temp=tempFile->readLine();
        this->gold=temp.toInt();
        temp=tempFile->readLine();
        this->changeDate=temp.trimmed();//去除换行符
        iteams.clear();
        while(!tempFile->atEnd())
        {
        temp=tempFile->readLine();
        iteam *it=new iteam(temp.toInt());       
        this->iteams.insert((*it).i_id,*it);
        }
        tempFile->close();
    }
    return;
}

player::player(int num)
{
    switch(num){
    case 1:
    {
        this->loadDate("D:\\Qt\\surveyor\\save","save1.txt");
        break;
    }
    case 2:
    {
        this->loadDate("D:\\Qt\\surveyor\\save","save2.txt");
        break;
    }
    case 3:
    {
        this->loadDate("D:\\Qt\\surveyor\\save","save3.txt");
        break;
    }
    case 4:
    {
        this->loadDate("D:\\Qt\\surveyor\\save","savetemp.txt");
        break;
    }
    default:
    {
        break;
    }
    }
}

int generateRandomNumber(int min, int max)
{
    return QRandomGenerator::global()->bounded(min,max);
}
