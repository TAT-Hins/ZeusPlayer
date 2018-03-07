#include "block.h"

Block::Block(QWidget *parent)
    : QLabel(parent)
{
    mine_Flag=false;            //雷的标记
    mine_Num=5;                 //雷的数目
    visible_Flag=false;         //可见标记
    mark_Flag=false;            //插旗标记
    this->setStyleSheet("background-color: rgb(230,230,230);color: rgb(0,0,0);");       //设置背景颜色
    this->setAlignment(Qt::AlignCenter);        //居中对齐
    this->setMinimumSize(40,40);                //最小尺寸
}

Block::~Block()
{

}

void Block::setMine_Flag(bool flag)
{
    mine_Flag=flag;
}

void Block::setMine_Num(int num)
{
    if(mine_Flag==false)        //只有在该方框不是雷的时候才能设置周围的雷数目
    {
        mine_Num=num;
    }
    else    mine_Num=0;
}

void Block::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            setVisible_Flag();
            break;
        case Qt::RightButton:
            setMark_Flag();
            FlagChange();        //发送标志改变信号
            break;
    default:
        break;
    }
}

void Block::setVisible_Flag(void)
{
    if(mark_Flag==false)     //能否被打开依赖于是否被标记
    {
        if(mine_Flag==false)
        {
            visible_Flag=true;      //设置可见属性
            this->setText(QString::number(this->mine_Num));      //同时显示雷的数目
        }
        else
        {
            Restart();      //触发重启信号
            this->setStyleSheet("background-color: rgb(100,100,100);color: rgb(100,100,100);");
        }
    }
}

void Block::setMark_Flag(void)
{
    if(visible_Flag==false)     //只有不可见的方块才能被标记
    {
        if(mark_Flag==false) {mark_Flag=true;this->setStyleSheet("background-color: rgb(0,230,230);color: rgb(0,0,0);");}        //蓝色
        else                {mark_Flag=false;this->setStyleSheet("background-color: rgb(230,230,230);color: rgb(0,0,0);");}
    }
}

void Block::GameOver()
{
}


