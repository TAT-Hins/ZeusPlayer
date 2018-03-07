#include "downloadinfodlg.h"
#include "ui_downloadinfodlg.h"
#include<QMouseEvent>
#include <QIcon>
downloadinfodlg::downloadinfodlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadinfodlg)
{
    ui->setupUi(this);
    m_MousePressed=false;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::X11BypassWindowManagerHint);
    ui->pushButton_exit->setStyleSheet("QPushButton{background:transparent;}"
                                       "QPushButton{border-image: url(:image/close24.png);}"
                                       "QPushButton:hover{border-image: url(:image/close24_2.png);}");

    nowdownlabel=new QLabel(ui->widget);//爹窗口位置
    nowdownlabel->setGeometry(5,1,230,20);//设置位置
    nowdownlabel->setStyleSheet("QLabel{font-size:13px;color: gray;font-family: 微软雅黑;}");

    tablewid=new QTableWidget(ui->widget);//爹窗口位置
    tablewid->setFrameShadow(QFrame::Plain);//设置平的样式
    tablewid->setFrameShape(QFrame::NoFrame);//设置无边样式
    tablewid->setFocusPolicy(Qt::NoFocus);
    tablewid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    tablewid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
    tablewid->setShowGrid(false);//隐藏线
    tablewid->verticalHeader()->setVisible(false);//设置不可见
    tablewid->setEditTriggers(QTableWidget::NoEditTriggers);//不可编辑
    tablewid->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    tablewid->setSelectionMode ( QAbstractItemView::SingleSelection);//单选
    tablewid->setStyleSheet("QTableWidget{color: gray; border: 1px solid gray;}"
                            "QTableWidget{selection-background-color: rgb(25,65,65,150);}"
                            "QTableWidget{selection-color: white;}");


    tablewid->insertColumn(0);
    tablewid->insertColumn(1);
    tablewid->insertColumn(2);

    tablewid->horizontalHeader()->setVisible(false);//不可以看见
    tablewid->verticalHeader()->setVisible(false);//不可以看见

    tablewid->horizontalHeader()->resizeSection(0,60);
    tablewid->horizontalHeader()->resizeSection(1,30);
    tablewid->horizontalHeader()->setStretchLastSection(true);//延展最后一下column
    tablewid->insertRow(0);
    tablewid->insertRow(1);
    tablewid->insertRow(2);

    tablewid->setRowHeight(0,25);
    tablewid->setRowHeight(1,25);
    tablewid->setRowHeight(2,25);

    tablewid->setItem(0,0,new QTableWidgetItem("超高品质"));
    tablewid->setItem(1,0,new QTableWidgetItem("普高品质"));
    tablewid->setItem(2,0,new QTableWidgetItem("标准品质"));

    tablewid->setItem(0,1,new QTableWidgetItem(QIcon(":/image/sq.png"),""));
    tablewid->setItem(1,1,new QTableWidgetItem(QIcon(":/image/hd.png"),""));
    tablewid->setItem(2,1,new QTableWidgetItem(QIcon(":/image/sd.png"),""));

    tablewid->setItem(0,2,new QTableWidgetItem("320kbps/mp3"));
    tablewid->setItem(1,2,new QTableWidgetItem("192kbps/mp3"));
    tablewid->setItem(2,2,new QTableWidgetItem("128kbps/mp3"));
    tablewid->setGeometry(60,30,180,80);

    tablewid->setCurrentItem(tablewid->item(0,0));

}
void downloadinfodlg::setbk(QString picName)
{
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/image/"+picName+".png")));
    setPalette(palette);
}
downloadinfodlg::~downloadinfodlg()
{
    delete ui;
}

void downloadinfodlg::on_pushButton_exit_clicked()
{
    this->close();
}
void downloadinfodlg::mousePressEvent(QMouseEvent *event)
{
    QRect *rc=new QRect(0,0,250,25);
    if(rc->contains(this->mapFromGlobal(QCursor::pos()))==true)
    {
      if (event->button() == Qt::LeftButton)
     {

       m_WindowPos = this->pos();
       m_MousePos = event->globalPos();
      this->m_MousePressed = true;
      }
    }

}
void downloadinfodlg::mouseMoveEvent(QMouseEvent *event)
{
    if (m_MousePressed)
        {
            this->move(m_WindowPos + (event->globalPos() - m_MousePos));
        }

}
void downloadinfodlg::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        this->m_MousePressed = false;
    }
}

void downloadinfodlg::on_pushButton_clicked()
{
    QString songname=nowdownlabel->text();
    int curow=tablewid->currentRow();
    emit downbtninfo(curow,songname);
    this->close();//隐藏起来
}
