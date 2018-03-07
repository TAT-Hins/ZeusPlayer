#include "myplaylist.h"
#include<QTime>
myplayList::myplayList()
{

}
QUrl myplayList::myCurrentMedia()
{
    return media(nowindex).canonicalUrl();
}
void myplayList::mysetCurrentMedia(int nowsong)
{
     nowindex=nowsong;
}
void myplayList::mysetPlaybackMode(int mode)//0是列表1是单曲2是随机
{
    nowmode=mode;
}
void myplayList::mysetnext()
{
    if(nowmode==0)
    {
        if(nowindex==mediaCount()-1)//顺序列表播放到尾巴上 从头再来
        {
            nowindex=0;
            return;
        }
        nowindex+=1;
    }
    if(nowmode==1)
    {
        return;
    }
    if(nowmode==2)
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%mediaCount();
        nowindex=xxx;
    }
}
void myplayList::mysetprevious()
{
    if(nowmode==0)
    {
        if(nowindex==0)//顺序列表播放头上再按上一曲， 从头播放第一首
        {
            nowindex=0;
            return;
        }

        nowindex-=1;
    }
    if(nowmode==1)
    {
        return;
    }
    if(nowmode==2)
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%mediaCount();
        nowindex=xxx;
    }
}
void myplayList::mydelitem(int index)
{
    if(index<nowindex)
    {
        this->removeMedia(index);
        nowindex--;//当前播放的歌曲变成null
        return;
    }
    if(index==nowindex)
    {
        this->removeMedia(index);
        nowindex++;
        return;
    }
    if(index>nowindex)
    {
        this->removeMedia(index);
        return;
    }
}
