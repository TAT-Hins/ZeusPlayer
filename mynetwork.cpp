#include "mynetwork.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QLabel>
#include<QTimer>
#include<QHBoxLayout>
#include<QEventLoop>
MyNetWork::MyNetWork(QObject *parent) : QObject(parent)
{
}
void MyNetWork::requestalbum(QString name,QString savelocal)
{
    albumsaveloca=savelocal;
    QString songencod(name.toUtf8().toPercentEncoding());
    QString totalurl="http://yyfm.xyz/search/dx/"+songencod+"?p=1&f=json&sign=";
    QNetworkRequest *request1=new QNetworkRequest;
    QNetworkAccessManager *manger1=new QNetworkAccessManager;
    request1->setUrl(totalurl);
    manger1->get(*request1);
    connect(manger1,SIGNAL(finished(QNetworkReply*)),this,SLOT(getfistalbum(QNetworkReply*)));
}
void MyNetWork::getfistalbum(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::TimeoutError)
    {

        reply->deleteLater();
        return;
    }
    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray byt=reply->readAll();
        QJsonDocument doc=QJsonDocument::fromJson(byt);
        QJsonArray arry=doc.array();
        QJsonObject obj=arry.at(0).toObject();

        QString picurl=obj.value("PicUrl").toString();
        if(picurl.isEmpty())
            return;
        QNetworkRequest *request3=new QNetworkRequest;
        QNetworkAccessManager *manger3=new QNetworkAccessManager;
        request3->setUrl(picurl);
        manger3->get(*request3);
        connect(manger3,SIGNAL(finished(QNetworkReply*)),this,SLOT(getpic302(QNetworkReply*)));
    }

    reply->deleteLater();
}
void MyNetWork::getpic302(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::TimeoutError)
    {

        reply->deleteLater();
        return;
    }
    QByteArray byt= reply->rawHeaderPairs().at(2).second;
     reply->deleteLater();

    QNetworkRequest *request3=new QNetworkRequest;
    QNetworkAccessManager *manger3=new QNetworkAccessManager;
    request3->setUrl(QString(byt));
    manger3->get(*request3);
    connect(manger3,SIGNAL(finished(QNetworkReply*)),this,SLOT(getpic(QNetworkReply*)));
}

void MyNetWork::getpic(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::TimeoutError)
    {

        reply->deleteLater();
        return;
    }
    QByteArray byt=reply->readAll();
    emit setpic(byt);
    reply->deleteLater();

    QFile file(albumsaveloca);
    file.resize(0);
    file.open(QIODevice::WriteOnly);
    file.write(byt);
    file.close();

}
void MyNetWork::requestdownsong(QString url,QString name)
{
    tableitemwidget=new QWidget;
    playpausebtn=new QPushButton;
    closedown=new QPushButton;
    playpausebtn->setFixedSize(16,16);
    closedown->setFixedSize(16,16);
    QHBoxLayout *hout=new QHBoxLayout;
    hout->addWidget(playpausebtn);
    hout->addWidget(closedown);
    hout->setSpacing(0);
    hout->setContentsMargins(0,0,0,0);
    tableitemwidget->setLayout(hout);

    bar=new QProgressBar;
    songname=name;
    songlabel=new QLabel(name);
    songlabel->setFixedWidth(60);
    songlabel->setStyleSheet("color:gray;");

    precentlabel=new QLabel;
    precentlabel->setFixedWidth(40);
    precentlabel->setStyleSheet("color:gray;");
    precentlabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    speedlabel=new QLabel;
    speedlabel->setFixedWidth(50);
    speedlabel->setStyleSheet("color:gray;");
    speedlabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    file=new QFile("D://ZeusMusic/"+name+".mp3");
    file->open(QIODevice::WriteOnly);

    QNetworkAccessManager *manger3=new QNetworkAccessManager;
    QNetworkRequest *request=new QNetworkRequest;
    request->setUrl(url);
    manger3->get(*request);
    connect(manger3,SIGNAL(finished(QNetworkReply*)),this,SLOT(getdownsong302(QNetworkReply*)));

}
void MyNetWork::getdownsong302(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::TimeoutError)
    {

        reply->deleteLater();
        return;
    }
    if(reply->error()==QNetworkReply::NoError)
    {
    qDebug()<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    QByteArray byt= reply->rawHeaderPairs().at(2).second;
    reply->deleteLater();
    qDebug()<<byt;

    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerslot()));
    timer->start(1000);

    QNetworkAccessManager *manger3=new QNetworkAccessManager;
    QNetworkRequest *request=new QNetworkRequest;
    request->setUrl(QUrl(QString(byt)));
    QNetworkReply *replymin= manger3->get(*request);

    connect(replymin,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(progressbarget(qint64,qint64)));
    connect(manger3,SIGNAL(finished(QNetworkReply*)),this,SLOT(downsongfinished(QNetworkReply*)));
    }
    reply->deleteLater();
}
void MyNetWork::timerslot()
{
    int cz=(nowbyte-previosbyte)/1000;
    previosbyte=nowbyte;
    speedlabel->setText(QString::number(cz)+"kb/s");
}
void MyNetWork::progressbarget(qint64 recieved, qint64 total)
{
    qDebug()<<recieved;
    nowbyte=recieved;
    bar->setMaximum(total);
    bar->setValue(recieved);
    precentlabel->setText(bar->text());
}
void MyNetWork::downsongfinished(QNetworkReply *reply4)
{
    if(reply4->error()==QNetworkReply::TimeoutError)
    {

        reply4->deleteLater();
        return;
    }
    if(reply4->error()==QNetworkReply::NoError)
    {
    file->write(reply4->readAll());
    file->close();
    }
    timer->stop();//定时器stop
    reply4->deleteLater();
}
void MyNetWork::requestnetwork(QString str)//请求歌曲
{
    QByteArray byt=str.toUtf8().toPercentEncoding();

    QString url="http://yyfm.xyz/search/dx/"+byt+"?p=1&f=json&sign=";
    QNetworkAccessManager *manger=new QNetworkAccessManager;

    QNetworkRequest *request=new QNetworkRequest;
    request->setUrl(url);
    manger->get(*request);

    /*request=new QNetworkRequest;
    manger=new QNetworkAccessManager;
    QNetworkAccessManager *manger=new QNetworkAccessManager;
    QNetworkRequest *request=new QNetworkRequest;
    request->setUrl(QUrl("http://music.163.com/api/search/pc"));
    request->setRawHeader("Cookie","os=pc");
    request->setRawHeader("Host","music.163.com");
    request->setRawHeader("MUSIC_U","5339640232");
    request->setRawHeader("Referer","http://music.163.com/");
    manger->post(*request,"offset=0&total=true&limit=100&type=1&s="+byt);*/

    connect(manger,SIGNAL(finished(QNetworkReply*)),this,SLOT(workfinished(QNetworkReply*)));
}
void MyNetWork::workfinished(QNetworkReply*reply2)
{
    if(reply2->error()==QNetworkReply::TimeoutError)
    {

        reply2->deleteLater();
        return;
    }
   if(reply2->error()==QNetworkReply::NoError)
   {
   QByteArray arry=reply2->readAll();
   emit doworkfinished(arry);//交给dialog
   }
   reply2->deleteLater();
}


void MyNetWork::requestlrc(QString lrcname,QString lrcloaction)//请求歌词 顺便请求图片
{
    lrcsaveloca=lrcloaction;
    QString songencod(lrcname.toUtf8().toPercentEncoding());
    QString totalurl="http://yyfm.xyz/search/dx/"+songencod+"?p=1&f=json&sign=";
    QNetworkRequest *request1=new QNetworkRequest;
    QNetworkAccessManager *manger1=new QNetworkAccessManager;
    request1->setUrl(totalurl);
    manger1->get(*request1);
    connect(manger1,SIGNAL(finished(QNetworkReply*)),this,SLOT(analyieslrc(QNetworkReply*)));

}
void MyNetWork::analyieslrc(QNetworkReply*reply1)
{
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
    QJsonObject obj=arry.at(0).toObject();
    QString lrcurl=obj.value("LrcUrl").toString();
    QNetworkRequest *request2=new QNetworkRequest;
    QNetworkAccessManager *manger2=new QNetworkAccessManager;
    request2->setUrl(lrcurl);
    manger2->get(*request2);
    connect(manger2,SIGNAL(finished(QNetworkReply*)),this,SLOT(analyieslrcfinished(QNetworkReply*))); 
    }
    else
    {
        return;
    }
    reply1->deleteLater();
}

void MyNetWork::analyieslrcfinished(QNetworkReply *reply3)
{
    if(reply3->error()==QNetworkReply::TimeoutError)
    {

        reply3->deleteLater();
        return;
    }
    if(reply3->error()==QNetworkReply::NoError)
    {
    QByteArray byt=reply3->readAll();
    emit dolrcworkfinished(byt);//发送做完的信号
    ////////////////////////////用于保存
    QString content(byt);
    QFile file(lrcsaveloca);
    file.resize(0);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))//如果打开失败
    {
      file.close();
      return;
    }
    QTextStream stream(&file);
    stream<<content;
    ////////////////////////////////////
    file.close();

    }
    else
    {
        return;
    }
    reply3->deleteLater();
}
