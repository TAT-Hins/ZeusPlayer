#ifndef MYMAINTABLEWIDGET_H
#define MYMAINTABLEWIDGET_H
#include<QTableWidget>
#include <QObject>
#include<QModelIndex>
#include<QtMultimedia/QMediaPlaylist>
class mymaintablewidget : public QTableWidget
{
    Q_OBJECT
public:
   explicit mymaintablewidget(QWidget *parent = 0);
    mymaintablewidget(bool second);//第二构造函数
    QUrl myCurrentMedia();
    void mysetCurrentMedia(int);
    void mysetPlaybackMode(int);
    void mysetnext();
    void mysetprevious();
    void mydelitem(int);
    void myitemup(int);
    void myitemdown(int);
    void changeRowItem(int,int);
    int nowindex;
    QMediaPlaylist *plist;//方便添加

signals:

private:
    int nowmode;//0是默认1是单曲2是随机
    int previousitem;
    bool kgmousemove;//开关鼠标事件

private slots:

public slots:
    void listentered(int,int);
    void currentitemch(QTableWidgetItem*,QTableWidgetItem*);
    void mouseMoveEvent(QMouseEvent *);
    void leaveEvent(QEvent *);

};

#endif // MYMAINTABLEWIDGET_H
