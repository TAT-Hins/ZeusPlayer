#ifndef MYMAINDLG_H
#define MYMAINDLG_H
#include "ui_mymaindlg.h"

#include <QDialog>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QtGui>
#include <QSystemTrayIcon>
#include <QToolTip>
#include <QStackedWidget>
#include <QTextEdit>
#include <QMediaContent>
#include <QWidgetAction>
#include <QLabel>
#include "skinbox.h"
#include "mylrc.h"
#include "mynetwork.h"
#include <QtMultimedia/QMediaPlayer>
#include <QMap>
#include <QHBoxLayout>
#include "myplaylist.h"
#include "downloadinfodlg.h"
#include "searchlrcdlg.h"
#include<QProgressBar>
#include<QMovie>
#include"mymaintablewidget.h"
#include"musicmarqueewidget.h"
#include "fmradiowindow.h"
#include "videoplayer.h"
#include"block.h"
#include "block_area.h"
#include"myui.h"
#include "widget.h"
#include "qvolumnbutton.h"

namespace Ui {
class MyMainDlg;
}
class MyMainDlg : public QDialog
{
    Q_OBJECT
signals:

public:
    explicit MyMainDlg(QWidget *parent = 0);
    ~MyMainDlg();
    QMovie *movie;
    QTimer *timer;
    QTimer *timer2;

    QString totaldisplay,nowplaytext;
    QString play_style;
    QString pause_style;
    QString path2lrc;//用于保存歌词名字

    QStackedWidget *stack;

    QTextEdit *lrcshowedit;

    QAction *aboutapp;
    QAction *quitapp;
    QAction *actionCurrentItemInLoop,*actionLoop,*actionRandom;//播放模式

    QMenu *playmode,*myMenu,*trayIconMenu,*pop_menu;//菜单

    QMediaPlayer *player;

    QMediaPlaylist *netplayList;

//    myplayList *myplaylist;

    QLabel*music_name_label;

    QWidgetAction *playmenuaction;

    skinbox *box;

    QSystemTrayIcon *trayIcon;

    MyLrc *lrc;

    QMap<qint64, QString> lrc_map;

    QHBoxLayout *lout;

    QTabWidget *tabwidget;

    QWidget *netseawidget;//用于动态效果
    QWidget *netseauiwidget;//添加到stackwidget
 //   QWidget *widget;
    QTableWidget *downloadtable;
    mymaintablewidget *searchtable;//搜索歌曲的显示table

    QLineEdit *ledit;//用于搜索歌曲的编辑框
    //网络
    MyNetWork *onlydownsongnetwork;
    MyNetWork *mynetwork;
    QNetworkReply *searchreply;

    downloadinfodlg *downdlg;//下载信息界面

    QPushButton *serbtn;//用于搜索歌曲的按钮
    QPushButton *play_button;
    QPushButton *delbtn;
///////////////////////////////////////用于包含下载开始 暂停 删除按钮
    QPushButton *downstart;
    QPushButton *downpause;
    QPushButton *downdelall;
    QWidget *downwid;
///////////////////////////////////////
    searchlrcdlg *lrcdlg;

    QLabel *loadlab,*addtips;

protected:
     bool eventFilter(QObject *obj, QEvent *event);
     void paintEvent(QPaintEvent *);
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
public slots:
     void downloadsonginfo(int,QString);//网上下载歌曲

private slots:
     void setplaylistopa(int);//列表透明度

     void setlabelpic(QByteArray);
     void searchlrcslot();

     void chagnplaybtnsty2(QMediaPlayer::MediaStatus);
     void changplaybtbsty(QMediaPlayer::State);//播放按钮的样式
     void leditreturnpressed();//return enter键按下

     void downloadnetsong();//搜索框的确定按钮返回的json解析
     void addplaynetListslot();
     void shownowplaylabel(QMediaContent);//ui上显示正在播放的歌曲
     void searchtableitemclick(QTableWidgetItem*);
     void seatabent(QModelIndex);//slot搜索的槽
     void searchdownui();
     void searchsongui();
     void slotmynetwork(QByteArray);//由mynetwork发的信号槽
     void songanaly();    //歌曲分析从搜索
     void analysislrc(QString);
     void animationfinished();
     void netlocationplaylist();//网络
     void netplaylistempty();

     void netdeleteplaylist();
     void netplay();
     void openlrcfolder();
     void copylrccontent();
     void autonextsong(QMediaPlayer::MediaStatus);
     void volpicchange(int);//音量图片改变

     void replyLrc(QByteArray);
     void addFolder();
     void emptyList();
     void setDialogStyleSheet();
     void setbtnmenu();
     void slot_addFile();
     void dragEnterEvent(QDragEnterEvent *);
     void dropEvent(QDropEvent *);
     void traymenushowlrc();
     void traymenuhidelrc();
     void tablemenuplay();
     void setsearchitems(QString);

     void showTableToolTip(QModelIndex);
     void delitem();
     void setBk(QString);
     void activitewindows();

     void trayiconmenu();
    void opensysfile();
    void seteditlrc(QMediaContent);
    void showlrcshoweditmenu(const QPoint&);
    void ShownetContextMenu(const QPoint&);
    void ShowContextMenu(const QPoint&);
    void scrolltoitem();
    void readlist();//读取列表
    void saveList();//保存列表
    void setVolpic();//设置音量三种图片
    void about();//关于
    void trayiconActivated(QSystemTrayIcon::ActivationReason);//系统托盘图标
    void closeEvent(QCloseEvent *event);//关闭事件
    void modeAction(QAction *act);//音乐模式选择
    void changelistitem(int j);//改变列表操作
    void positionChanged(qint64);
    void durationChanged(qint64);
    void setPosition(int);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent2();
    void timerEvent();

    void on_pushButton_backward_clicked();

    void on_pushButton_playpause_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_vol_clicked();

   void mytabledoubleclick(QTableWidgetItem *);

   void on_pushButton_skinbox_clicked();

   void on_checkBox_clicked(bool checked);

   void on_pushButton_search_clicked();

   void on_pushButton_searchclose_clicked();

   void on_listWidget_side_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

   void on_listWidget_side_currentRowChanged(int currentRow);


   void on_pushButton_exit_clicked();

    void mynetmaintabledoublclick(QTableWidgetItem*);
    void on_pushButton_mini_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_webplayer_clicked();

    void on_pushButton_videoplayer_clicked();

    void on_pushButton_fmradio_clicked();

    void on_pushButton_minesweeping_clicked();

private:
    Ui::MyMainDlg *ui;
    /////////////////////////////
    bool    m_MousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;

    QString saveskinname; //用于保存皮肤名称
    QString netnowplaysongname;

    bool changevol;
////////////////////////
    bool lrcmove;
    int lastypos;
    int lastindex;
////////////////////

    int vol;//用于音量按钮静音与恢复
    int volpos;//eventfilter中
    int checkbox;
    int previousitem;
    int prviouslrc;

    //用于保存歌词文件
    int nowdownrow;//用于获取下载按钮的行位置 给json解析第几个位置

    int listopacity;
    int nowplaylist;//用于分析现在正在播放的列表

    QList <QString> listSqMusic;//高品质
    QList <QString> listHqMusic;//一般品质
    QList <QString> listLqMusic;//听歌品质

    QList <QString> listlrcurl;
    QList <QString> listmp3Url;

    mymaintablewidget *mymaintable ,*mynetmaintable;
    QActionGroup *actionGroupMode;

    MusicMarqueeWidget *nowplaywid;


};
#endif // MYMAINDLG_H
