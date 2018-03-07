#include "block_area.h"
#include <QDebug>

Block_Area::Block_Area(int Trow,int Tcolumn,int Tmine) : QWidget()
{
    if(Trow<0||Trow>10) return;
    if(Tcolumn<0||Tcolumn>10) return;
    if(Tmine<0||Trow>Trow*Tcolumn) return;

    this->row=Trow;
    this->column=Tcolumn;
    this->mine_count=Tmine;



    mainLayout=new QGridLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(6);

    setAreaAttr(this->column,this->row,mine_count);
}

void Block_Area::setAreaAttr(int mycolumn,int myrow,int mines)
{
    int flag[mycolumn*myrow];
    int i;

    int initBlock=(mycolumn*myrow-mines)/10;        //初始化可见方格数目


    for(i=0;i<mines;i++)                                flag[i]=0;
    for(i=mines;i<mines+initBlock;i++)                  flag[i]=1;
    for(i=mines+initBlock;i<mycolumn*myrow;i++)         flag[i]=2;

    std::random_shuffle(flag,flag+mycolumn*myrow);     //产生随机序列

    for(i=0;i<mycolumn*myrow;i++)
    {
        Block *bl=new Block();
        MineBlock<<bl;
        if(flag[i]==1)      //没有雷,但是初始可见
        {
            MineBlock[i]->mine_Flag=false;
            MineBlock[i]->visible_Flag=true;
        }
        else if(flag[i]==2)
        {
            MineBlock[i]->mine_Flag=false;
            MineBlock[i]->visible_Flag=false;
        }
        else
        {
            MineBlock[i]->mine_Flag=true;
            MineBlock[i]->visible_Flag=false;
        }
    }
//    qDebug("MyLen=%d\n",MineBlock.length());
    for(i=0;i<mycolumn*myrow;i++)       //方块逐个初始化
    {
        setMineCount(i);        //设置雷的数目

        if(MineBlock[i]->mine_Flag==false&&MineBlock[i]->visible_Flag==true)
            MineBlock[i]->setText(QString::number(MineBlock[i]->mine_Num));     //显示初始化可见方格

        mainLayout->addWidget(MineBlock[i],i/mycolumn,i%mycolumn);

        connect(MineBlock[i],SIGNAL(Restart()),this,SLOT(slt_restart()));
        connect(MineBlock[i],SIGNAL(FlagChange()),this,SLOT(slt_flagChange()));
    }
}

int Block_Area::getBlockMineNum(int x,int y)
{
//    qDebug("x=%d\n",x);
//    qDebug("y=%d\n",y);
//    qDebug("Column=%d\n",column);
//    qDebug("Len2=%d\n",x+y*column);
    if(x>=column||y>=row||x<0||y<0) return 0;

    else if(MineBlock[x+y*column]->mine_Flag==true)   return 1;
    else                                        return 0;
}

void Block_Area::setMineCount(int index)
{
    int x;
    int y;

    x=index%column;
    y=index/column;

    MineBlock[index]->mine_Num=getBlockMineNum(x-1,y-1)+     //1
            getBlockMineNum(x,y-1)+                          //2
            getBlockMineNum(x+1,y-1)+                        //3
            getBlockMineNum(x-1,y)+                          //4
            0+                                               //5
            getBlockMineNum(x+1,y)+                          //6
            getBlockMineNum(x-1,y+1)+                        //7
            getBlockMineNum(x,y+1)+                          //8
            getBlockMineNum(x+1,y+1);                        //9
}

void Block_Area::slt_restart()
{
    sgn_restart();      //信号传递
}

int Block_Area::cal_flag(int trow,int tcolumn)
{
    int flagNum=0;
    for(int i=0;i<trow*tcolumn;i++)
    {
        if(MineBlock[i]->mark_Flag==true)    flagNum++;
    }
    return flagNum;
}

void Block_Area::slt_flagChange()
{
    sgn_flagChang();    //信号传递
}
