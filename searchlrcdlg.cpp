#include "searchlrcdlg.h"
#include "ui_searchlrcdlg.h"
#include<QMouseEvent>
#include<QJsonDocument>
#include<QJsonArray>
#include<QMovie>
#include<QJsonObject>
#include<QGraphicsOpacityEffect>
#include<QScrollBar>
searchlrcdlg::searchlrcdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchlrcdlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::X11BypassWindowManagerHint);
    loadlab=new QLabel(ui->listWidget);//以搜索显示的tablewidget为父窗口
    QMovie *movie=new QMovie("image/loading.gif");
    loadlab->setMovie(movie);
    movie->start();
    loadlab->raise();
    loadlab->setGeometry(95,100,64,64);
    loadlab->hide();

    m_MousePressed=false;
    ledit=new QLineEdit(ui->widget);
    ledit->setGeometry(48,10,170,20);
    ledit->setStyleSheet("color: blue;");
    ui->pushButton_exit->setStyleSheet("QPushButton{background:transparent;}"
                                       "QPushButton{border-image: url(:image/close24.png);}"
                                       "QPushButton:hover{border-image: url(:image/close24_2.png);}");
    serbtn=new QPushButton("搜索",ui->widget);
    serbtn->setGeometry(218,10,30,20);
    connect(serbtn,SIGNAL(clicked()),this,SLOT(slotbtn()));//搜索
    connect(ledit,SIGNAL(returnPressed()),this,SLOT(returnpress()));


    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    ui->listWidget->verticalScrollBar()->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);

    QScrollBar *vbar=ui->listWidget->verticalScrollBar();
    vbar->setContextMenuPolicy(Qt::NoContextMenu);
    vbar->setStyleSheet("QScrollBar{background:white; width: 10px;margin: 10px 0 10px 0;}"
                        "QScrollBar::handle{background:light gray;border-radius:5px;}"
                        "QScrollBar::handle:hover{background: rgb(55,55,55);}"
                        "QScrollBar::add-line:vertical {background:black; border-image: url(:/image/down.png); height: 10px; subcontrol-position: bottom;subcontrol-origin: margin;}"
                        "QScrollBar::sub-line:vertical {background:black; border-image: url(:/image/top.png);height: 10px;subcontrol-position: top;subcontrol-origin: margin;}"
                        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:white;}");


    QGraphicsOpacityEffect *opacityEffect2 = new QGraphicsOpacityEffect;
    ui->listWidget->horizontalScrollBar()->setGraphicsEffect(opacityEffect2);
    opacityEffect2->setOpacity(0.5);
    QScrollBar *hbar=ui->listWidget->horizontalScrollBar();
    hbar->setContextMenuPolicy(Qt::NoContextMenu);
    hbar->setStyleSheet("QScrollBar{background:white; height: 10px;}"
                        "QScrollBar::handle{background:light gray;border-radius:5px;}"
                        "QScrollBar::handle:hover{background: rgb(55,55,55);}");


}
void searchlrcdlg::returnpress()
{
    emit serbtn->click();
}
searchlrcdlg::~searchlrcdlg()
{
    delete ui;
}

void searchlrcdlg::on_pushButton_exit_clicked()
{
    this->hide();
}
void searchlrcdlg::setBk(QString picName)
{
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/image/"+picName+".png")));
    setPalette(palette);
}
void searchlrcdlg::mousePressEvent(QMouseEvent *event)
{
    QRect *rc=new QRect(0,0,250,25);
    if(rc->contains(this->mapFromGlobal(QCursor::pos()))==true)//如果按下的位置
    {
      if (event->button() == Qt::LeftButton)
     {

       m_WindowPos = this->pos();
       m_MousePos = event->globalPos();
      this->m_MousePressed = true;
      }
    }

}
void searchlrcdlg::mouseMoveEvent(QMouseEvent *event)
{
    if (m_MousePressed)
        {
            this->move(m_WindowPos + (event->globalPos() - m_MousePos));
        }

}
void searchlrcdlg::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_MousePressed = false;
    }
}

void searchlrcdlg::slotbtn()
{
    listlrc.clear();
    loadlab->raise();
    loadlab->show();
    ui->listWidget->clear();
    QString songencod(ledit->text().toUtf8().toPercentEncoding());
    QString totalurl="http://yyfm.xyz/search/dx/"+songencod+"?p=1&f=json&sign=";
    QNetworkRequest *request1=new QNetworkRequest;
    QNetworkAccessManager *manger1=new QNetworkAccessManager;
    request1->setUrl(totalurl);
    manger1->get(*request1);
    connect(manger1,SIGNAL(finished(QNetworkReply*)),this,SLOT(analyieslrc(QNetworkReply*)));
}
void searchlrcdlg::analyieslrc(QNetworkReply*reply1)
{
    loadlab->hide();
    if(reply1->error()==QNetworkReply::TimeoutError)
    {
        reply1->deleteLater();
        return;
    }
    if(reply1->error()==QNetworkReply::NoError)
    {
    QByteArray byt=reply1->readAll();
    QJsonDocument doc=QJsonDocument::fromJson(byt);
    QJsonArray arry=doc.array();
    for(int i=0;i<arry.count();i++)
    {
    QJsonObject obj=arry.at(i).toObject();
    QString lrcurl=obj.value("LrcUrl").toString();
    listlrc<<lrcurl;
    QString songname=obj.value("SongName").toString();
    QString artist=obj.value("Artist").toString();
    ui->listWidget->insertItem(i,artist+"-"+songname);
    }
    }
    reply1->deleteLater();
}

void searchlrcdlg::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    int nowrow= item->listWidget()->currentRow();
    QString url=listlrc.at(nowrow);

    QNetworkRequest *request1=new QNetworkRequest;
    QNetworkAccessManager *manger1=new QNetworkAccessManager;
    request1->setUrl(url);
    manger1->get(*request1);
    connect(manger1,SIGNAL(finished(QNetworkReply*)),this,SLOT(lrcsearslot(QNetworkReply*)));

}
void searchlrcdlg::lrcsearslot(QNetworkReply* reply)
{
    if(reply->error()==QNetworkReply::TimeoutError)
    {
        reply->deleteLater();
        return;
    }
    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray byt=reply->readAll();
        emit getlrcshow(byt);
        QString url="D://ZeusLrc/"+songtotalname+".lrc";

        QFile file(url);
        file.resize(0);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream in(&file);
        in<<byt;
        file.close();
    }
    else
    {
        return;
    }
}
