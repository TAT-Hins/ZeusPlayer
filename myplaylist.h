#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H
#include<QtMultimedia/QMediaPlaylist>
#include <QObject>

class myplayList : public QMediaPlaylist
{
public:
    myplayList();
    QUrl myCurrentMedia();
    void mysetCurrentMedia(int);
    void mysetPlaybackMode(int);
    void mysetnext();
    void mysetprevious();
    void mydelitem(int);

    int nowindex;
private:

    int nowmode;//0是默认1是单曲2是随机
};

#endif // MYPLAYLIST_H
