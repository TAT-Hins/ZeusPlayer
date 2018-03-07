#include "myui.h"

MyUI::MyUI(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("扫雷"));
    //Block_Area *mine_area;
    //设置布局
    int wsize=60,hsize=20;
    rowLabel=new QLabel(tr("行数:"));
    rowLabel->setMinimumSize(wsize,hsize);
    rowLabel->setMaximumSize(wsize,hsize);

    rowLineEdit=new QLineEdit(tr("6"));
    rowLineEdit->setMinimumSize(wsize,hsize);
    rowLineEdit->setMaximumSize(wsize,hsize);

    columnLabel=new QLabel(tr("列数:"));
    columnLabel->setMinimumSize(wsize,hsize);
    columnLabel->setMaximumSize(wsize,hsize);

    columnLineEdit=new QLineEdit(tr("6"));
    columnLineEdit->setMinimumSize(wsize,hsize);
    columnLineEdit->setMaximumSize(wsize,hsize);

    mineLabel=new QLabel(tr("雷总数:"));
    mineLabel->setMinimumSize(wsize,hsize);
    mineLabel->setMaximumSize(wsize,hsize);

    mineLineEdit=new QLineEdit(tr("16"));
    mineLineEdit->setMinimumSize(wsize,hsize);
    mineLineEdit->setMaximumSize(wsize,hsize);

    startBtn=new QPushButton(tr("重新开始"));
    startBtn->setMinimumSize(wsize,2*hsize);
    startBtn->setMaximumSize(wsize,2*hsize);

    mineShowLabel=new QLabel(tr("剩余雷数:"));
    mineShowLabel->setMinimumSize(wsize,hsize);
    mineShowLabel->setMaximumSize(wsize,hsize);

    mineNumLabel=new QLabel(tr("6"));
    mineNumLabel->setMinimumSize(wsize,hsize);
    mineNumLabel->setMaximumSize(wsize,hsize);

    flagLabel=new QLabel(tr("标记数:"));
    flagLabel->setMinimumSize(wsize,hsize);
    flagLabel->setMaximumSize(wsize,hsize);

    flagNumLabel=new QLabel(tr("0"));
    flagNumLabel->setMinimumSize(wsize,hsize);
    flagNumLabel->setMaximumSize(wsize,hsize);

    setingLayout=new QGridLayout();
    //setingLayout->setMargin(4);
    //setingLayout->setSpacing(2);
    setingLayout->addWidget(rowLabel,0,0,1,1,Qt::AlignLeft);
    setingLayout->addWidget(rowLineEdit,0,1,1,1,Qt::AlignLeft);
    setingLayout->addWidget(columnLabel,1,0,1,1,Qt::AlignLeft);
    setingLayout->addWidget(columnLineEdit,1,1,1,1,Qt::AlignLeft);
    setingLayout->addWidget(mineLabel,2,0,1,1,Qt::AlignLeft);
    setingLayout->addWidget(mineLineEdit,2,1,1,1,Qt::AlignLeft);
    setingLayout->addWidget(startBtn,3,0,1,1,Qt::AlignLeft);


    setingLayout->addWidget(mineShowLabel,0,3,1,1,Qt::AlignLeft);
    setingLayout->addWidget(mineNumLabel,0,4,1,1,Qt::AlignLeft);
    setingLayout->addWidget(flagLabel,1,3,1,1,Qt::AlignLeft);
    setingLayout->addWidget(flagNumLabel,1,4,1,1,Qt::AlignLeft);

    //扫雷布局区
    int temprow,tempcolumn,tempmine;
    temprow=rowLineEdit->text().toInt();
    tempcolumn=columnLineEdit->text().toInt();
    tempmine=mineLineEdit->text().toInt();
    MineArea=new Block_Area(temprow,tempcolumn,tempmine);
    mineNumLabel->setText(QString::number(tempmine));
    flagNumLabel->setText(QString::number(0));

    mainLayout=new QGridLayout(this);
    //mainLayout->setMargin(8);
    //mainLayout->setSpacing(4);

    mainLayout->addLayout(setingLayout,0,0);
    mainLayout->addWidget(MineArea,1,0);

    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(restart()));
    connect(MineArea,SIGNAL(sgn_restart()),this,SLOT(restart()));
    connect(MineArea,SIGNAL(sgn_flagChang()),this,SLOT(updateflag()));
}

void MyUI::restart()
{
    QMessageBox::StandardButton btn=QMessageBox::critical(this,tr("地雷"),tr("重新开始!"),QMessageBox::Yes );
    if(btn==QMessageBox::Yes)
    {
        mainLayout->removeWidget(MineArea);
        MineArea->deleteLater();
        int temprow,tempcolumn,tempmine;
        temprow=rowLineEdit->text().toInt();
        tempcolumn=columnLineEdit->text().toInt();
        tempmine=mineLineEdit->text().toInt();
        MineArea=new Block_Area(temprow,tempcolumn,tempmine);
        int flagnums=MineArea->cal_flag(temprow,tempcolumn);
        mineNumLabel->setText(QString::number(tempmine-flagnums));
        flagNumLabel->setText(QString::number(flagnums));

        mainLayout->addWidget(MineArea,1,0);
        connect(MineArea,SIGNAL(sgn_restart()),this,SLOT(restart()));       //重新连接信号和槽
        connect(MineArea,SIGNAL(sgn_flagChang()),this,SLOT(updateflag()));
    }
}

void MyUI::updateflag()
{
    int flagnums;
    int temprow,tempcolumn,tempmine;
    temprow=rowLineEdit->text().toInt();
    tempcolumn=columnLineEdit->text().toInt();
    tempmine=mineLineEdit->text().toInt();
    flagnums=MineArea->cal_flag(temprow,tempcolumn);
    mineNumLabel->setText(QString::number(tempmine-flagnums));
    flagNumLabel->setText(QString::number(flagnums));
}

