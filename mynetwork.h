#ifndef MYNETWORK_H
#define MYNETWORK_H
#include<QtNetwork>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include <QObject>
#include<QFile>
#include<QProgressBar>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
class MyNetWork : public QObject
{
    Q_OBJECT
public:
    explicit MyNetWork(QObject *parent = 0);
    QWidget *tableitemwidget;
    QString songname;//方便dialog调用
    QLabel *songlabel;
    QLabel *precentlabel;
    QLabel *speedlabel;
    QPushButton *playpausebtn;
    QPushButton *closedown;


    void requestalbum(QString name,QString savelocal);
    void requestnetwork(QString);
    void requestlrc(QString name,QString saveloaction);
    void requestdownsong(QString url,QString name);
signals:

    void doworkfinished(QByteArray);
    void dolrcworkfinished(QByteArray);
    void setpic(QByteArray);
    void downprogress(qint64,qint64);
public slots:
    void getfistalbum(QNetworkReply *);
    void getpic(QNetworkReply*);
    void getpic302(QNetworkReply*);
    void getdownsong302(QNetworkReply*);//用于获取302 新链接
    void progressbarget(qint64,qint64);
    void downsongfinished(QNetworkReply*);
    void workfinished(QNetworkReply*);
    void analyieslrc(QNetworkReply*);
    void analyieslrcfinished(QNetworkReply*);

    void timerslot();
private:
    qint64 nowbyte,previosbyte;
    QTimer *timer;
    QFile *file;
    QProgressBar *bar;
    QNetworkRequest *request;
    QNetworkAccessManager *manger;

    QString albumsaveloca;
    QString lrcsaveloca;

};

#endif // MYNETWORK_H
