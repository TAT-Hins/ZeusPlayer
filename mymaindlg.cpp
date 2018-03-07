#include "mymaindlg.h"
#include "ui_mymaindlg.h"

#include<QDialog>
#include "skinbox.h"
#include <QFileDialog>
#include <QTimer>
#include <QDateTime>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QToolTip>
#include <QTime>
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>
#include <QListWidgetItem>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QTableWidgetItem>
#include <QDropEvent>
#include <QDesktopWidget>
#include <QCursor>

MyMainDlg::MyMainDlg(QWidget *parent) :QDialog(parent),ui(new Ui::MyMainDlg)
{
    ui->setupUi(this);

    QDir dir("D://ZeusLrc");//创建保存歌词的文件夹
    if(!dir.exists())
    dir.mkdir("D://ZeusLrc");
    QDir dir2("D://ZeusMusic");
    if(!dir2.exists())
    dir2.mkdir("D://ZeusMusic");
    QDir dir3("D://ZeusAlbum");
    if(!dir3.exists())
    dir3.mkdir("D://ZeusAlbum");
    nowplaywid=new MusicMarqueeWidget(this);
    nowplaywid->setGeometry(5,25,175,20);

    stack=new QStackedWidget(this);
    mymaintable=new mymaintablewidget(stack);//添加widget
    mynetmaintable=new mymaintablewidget(stack);//添加网络列表

    addtips=new QLabel("点击按钮添加\n或拖动文件到界面", mymaintable);
    addtips->setGeometry(90,150,180,50);
    addtips->setStyleSheet("color: white;font-size: 14px;font-family :微软雅黑");

    box=new skinbox(this);

    mynetwork=new MyNetWork;//网络
    downdlg=new downloadinfodlg(this);

    lrcdlg=new searchlrcdlg(this);
    lrcdlg->setModal(true);//模太对话框

    lrc=new MyLrc;

    lrcshowedit=new QTextEdit(this);
    lrcshowedit->setStyleSheet("QTextEdit{background:transparent}");
    lrcshowedit->setFrameStyle(QFrame::NoFrame);
    lrcshowedit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lrcshowedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lrcshowedit->setReadOnly(true);
    lrcshowedit->setFont(QFont("微软雅黑", 10, 0));
    lrcshowedit->setTextColor(Qt::white);
    lrcshowedit->setContextMenuPolicy(Qt::CustomContextMenu);
    lrcshowedit->setFocusPolicy(Qt::NoFocus);
    lrcshowedit->viewport()->installEventFilter(this);//事件
    lrcshowedit->viewport()->setCursor(QCursor(QPixmap(":/image/cursor_hand.png")));//原始形状的cursor

/////////////////////////////////////////netsearch的形成
    searchsongui();//查找歌曲页面的ui
    searchdownui();//下载歌曲页面的ui
/////////////////////////////////////////////////////////////
    loadlab=new QLabel(searchtable);//以搜索显示的tablewidget为父窗口
    movie=new QMovie("image/loading.gif");
    loadlab->setMovie(movie);
    movie->start();
    loadlab->raise();
    loadlab->setGeometry(81,80,64,64);
    loadlab->hide();



    stack->addWidget( lrcshowedit);//textedit
    stack->addWidget( mymaintable);//tablewidet主界面的
    stack->addWidget(mynetmaintable);//tablewidet
    stack->addWidget(netseauiwidget);//widget
    stack->addWidget(tabwidget);//tabwidget
    stack->setGeometry(310,70,650,470);//丑白框框位置和大小

    ui->widget_search->raise();//位于最上层
    ui->widget_search->hide();
    ui->lineEdit_search->setTextMargins(13,0,0,0);//为图标留下地方
///////////////////////////////////////////////////////////////////////////////滚动条样式

    this->setAcceptDrops(true);//darg和drop事件
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowTitle("zeusplayer");
    ////////////////////////////两个定时器
    timer = new QTimer();
    timer->start(1000);
    timer2 = new QTimer();
    timer2->start(200);
    /////////////////////////////////////////////////控件样式
    setDialogStyleSheet();//样式

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ui->listWidget_side->viewport()->installEventFilter(this);
    ui->horizontalSlider_vol->installEventFilter(this);//用于点击slider即到
    ui->horizontalSlider->installEventFilter(this);//用于点击slider即到
    ui->listWidget_side->setMouseTracking(true);

    nowplaywid->installEventFilter(this);
    ui->label_title->installEventFilter(this);
    ui->label_pic->installEventFilter(this);

    mymaintable->setContextMenuPolicy(Qt::CustomContextMenu);
    mynetmaintable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->horizontalSlider_vol->setRange(0,100);
    ui->pushButton_playpause->setToolTip("播放");

    /////////////////////////////////////////开关
    changevol=true;//vol的按钮改变

    checkbox=0;
    previousitem=-1;
    m_MousePressed=false;
    lrcmove=false;

    nowplaylist=1;//正在播放列表
    /////////////////////////////////////
    netplayList=new QMediaPlaylist;
    player=new QMediaPlayer;
///////////////////////////////////////////////////
    trayiconmenu();//设置系统图标菜单
    setbtnmenu();//播放模式菜单与添加菜单

    connect(mymaintable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(mytabledoubleclick(QTableWidgetItem *)));
    connect(mynetmaintable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(mynetmaintabledoublclick(QTableWidgetItem*)));

    connect(lrcdlg,SIGNAL(getlrcshow(QByteArray)),this,SLOT(replyLrc(QByteArray)));//lrc对话框获取

    connect(box,SIGNAL(listbktransparent(int)),this,SLOT(setplaylistopa(int)));//设置播放列表的背景透明度

    connect(box,SIGNAL(skinChange(QString)),downdlg,SLOT(setbk(QString)));//为下载dlg设置背景图片
    connect(box,SIGNAL(skinChange(QString)),this,SLOT(setBk(QString)));//为歌词dlg设置背景图片
    connect(box,SIGNAL(skinChange(QString)),lrcdlg,SLOT(setBk(QString)));//为歌词dlg设置背景图片
    connect(downdlg,SIGNAL(downbtninfo(int,QString)),this,SLOT(downloadsonginfo(int,QString)));//获取下载对话框的信息

    connect(searchtable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(searchtableitemclick(QTableWidgetItem*)));
    connect(searchtable,SIGNAL(entered(QModelIndex)),this,SLOT(seatabent(QModelIndex)));
    connect(mynetwork,SIGNAL(dolrcworkfinished(QByteArray)),this,SLOT(replyLrc(QByteArray)));//mynetwork连接信号与槽返回的lrc显示
    connect(mynetwork,SIGNAL(doworkfinished(QByteArray)),this,SLOT(slotmynetwork(QByteArray)));//由mynetwork发的信号槽
    connect(ui->pushButton_location,SIGNAL(clicked()),this,SLOT(scrolltoitem()));//定位
    connect(lrc,SIGNAL(changeselect(bool)),ui->checkBox,SLOT(setChecked(bool)));//用于显示歌词checkbox的选中
    connect(mynetmaintable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShownetContextMenu(const QPoint&)));//网络列表的
    connect(mymaintable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(lrcshowedit,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showlrcshoweditmenu(const QPoint&)));
    connect(ui->listWidget_side,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
    connect(timer2,SIGNAL(timeout()),this,SLOT(timerEvent2()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));

    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(chagnplaybtnsty2(QMediaPlayer::MediaStatus)));
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(changplaybtbsty(QMediaPlayer::State)));//改变播放按钮的样式

    connect(player,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(shownowplaylabel(QMediaContent)));//显示正在播放的歌曲label
    connect(player,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(seteditlrc(QMediaContent)));//当前音乐改变
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

   //改变歌曲就改变listitem选中
    connect(ui->horizontalSlider_vol,SIGNAL(valueChanged(int)),this,SLOT(volpicchange(int)));//音量图片改变
    connect(ui->horizontalSlider_vol,SIGNAL(sliderMoved(int)),this,SLOT(volpicchange(int)));//音量图片改变
    connect(ui->horizontalSlider_vol,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
    connect(ui->horizontalSlider_vol,SIGNAL(sliderMoved(int)),player,SLOT(setVolume(int)));

    connect(ui->lineEdit_search,SIGNAL(textChanged(QString)),this,SLOT(setsearchitems(QString)));
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(autonextsong(QMediaPlayer::MediaStatus)));//歌曲结尾的时候
    readlist();//读取列表

}
void MyMainDlg::setplaylistopa(int val)
{
    listopacity=val;  //用于保存透明度
    QString str="QTableWidget{background-color:rgb(255, 255, 255,"+QString::number(val)+");}"
    "QTableWidget{selection-background-color: rgb(25,65,65,150);padding: -1;}"
    "QTableWidget{selection-color: rgb(255, 255, 255);}"
    "QTableWidget{font-size : 12px;color: rgb(55, 55, 55);}";
    mymaintable->setStyleSheet(str);
    mynetmaintable->setStyleSheet(str);
}
void MyMainDlg::setlabelpic(QByteArray byt)
{
    QPixmap *pix=new QPixmap();
    pix->loadFromData(byt);
    ui->label_pic->setPixmap(pix->scaled(60,60));
}
void MyMainDlg::mynetmaintabledoublclick(QTableWidgetItem *item)//调节播放列表为第二
{
    nowplaylist=2;//设置播放列表
    mynetmaintable->mysetCurrentMedia(item->row());
    player->setMedia(mynetmaintable->myCurrentMedia());
    player->play();
}
void MyMainDlg::downloadsonginfo(int row,QString songname)//下载按钮确定后发送的信息
{
    QString songurl;
    switch(row)//判断下载对话框的质量选择
    {
    case 0:
        songurl=listSqMusic.at(nowdownrow);

        break;
    case 1:
        songurl=listHqMusic.at(nowdownrow);

        break;
    case 2:
        songurl=listLqMusic.at(nowdownrow);
        break;
    }
    qDebug()<<songurl;
    onlydownsongnetwork=new MyNetWork;//点击一下就生成一个对象
    onlydownsongnetwork->requestdownsong(songurl,songname);//网络请求随便下多少都可以
    int rowcount= downloadtable->rowCount();
    downloadtable->insertRow(rowcount);
    downloadtable->setCellWidget(rowcount,0,onlydownsongnetwork->songlabel);
    downloadtable->setCellWidget(rowcount,1,onlydownsongnetwork->precentlabel);
    downloadtable->setCellWidget(rowcount,2,onlydownsongnetwork->speedlabel);
    downloadtable->setCellWidget(rowcount,3,onlydownsongnetwork->tableitemwidget);

}
void MyMainDlg::chagnplaybtnsty2(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::InvalidMedia)//无效
    {
        ui->pushButton_playpause->setStyleSheet(play_style);
        ui->pushButton_playpause->setToolTip("播放");
        play_button->setStyleSheet("QPushButton{border-image: url(:/image/menuplay.png);}");//播放按钮
    }
    if(status==QMediaPlayer::StalledMedia)//失速
    {
        ui->pushButton_playpause->setStyleSheet(play_style);
        ui->pushButton_playpause->setToolTip("播放");
        play_button->setStyleSheet("QPushButton{border-image: url(:/image/menuplay.png);}");
    }

}
void MyMainDlg::changplaybtbsty(QMediaPlayer::State states)//用空格键控制播放暂停
{
    if(states==QMediaPlayer::PlayingState)//播放状态
    {
        ui->pushButton_playpause->setStyleSheet(pause_style);
        ui->pushButton_playpause->setToolTip("暂停");
        ui->pushButton_playpause->setShortcut(QKeySequence("space"));
        play_button->setStyleSheet("QPushButton{border-image: url(:/image/menupause.png);}");//暂停按钮
    }
    if(states==QMediaPlayer::PausedState)//暂停状态
    {
            ////////////////////
        ui->pushButton_playpause->setStyleSheet(play_style);
        ui->pushButton_playpause->setToolTip("播放");
        ui->pushButton_playpause->setShortcut(QKeySequence("space"));
        play_button->setStyleSheet("QPushButton{border-image: url(:/image/menuplay.png);}");//播放按钮
    }
}

void MyMainDlg::volpicchange(int vol)//音量图片改变
{
    if(vol==0)
    {
        QString vol_shut_style="QPushButton{background:transparent;}"
                                "QPushButton{border-image: url(:image/volume_shut.png);}";
        ui->pushButton_vol->setStyleSheet(vol_shut_style);
    }
   else if(vol<70)
    {
       QString vol_step_style="QPushButton{background:transparent;}"
                               "QPushButton{border-image: url(:image/volume_step.png);}";
       ui->pushButton_vol->setStyleSheet(vol_step_style);
    }
    else
    {
        QString vol_style="QPushButton{background:transparent;}"
                           "QPushButton{border-image: url(:image/volume.png);}";
        ui->pushButton_vol->setStyleSheet(vol_style);
    }

    QToolTip::showText(QCursor::pos(),QString::number(vol));//通过vol的slidermove得到这个值//用于传值给tooltip 实时显示
}

void MyMainDlg::searchtableitemclick(QTableWidgetItem*tableitem)
{

    if(tableitem->column()==1)
    {

        ledit->setText(tableitem->text());
        serbtn->click();
    }
    if(tableitem->column()==0)//如果点击第一列
    {
        nowplaylist=2;//设置播放列表
        QPoint point=searchtable->mapFromGlobal(QCursor::pos());
        int nowrow=searchtable->indexAt(QPoint(point.x(),point.y()-18)).row();

        QString songname= searchtable->item(nowrow,0)->text();
        QString author=searchtable->item(nowrow,1)->text();
        netnowplaysongname=author+"-"+songname;
        int netrowcount= mynetmaintable->rowCount();

        mynetmaintable->insertRow(netrowcount);
        mynetmaintable->setItem(netrowcount,0,new QTableWidgetItem(songname));
        mynetmaintable->setItem(netrowcount,1,new QTableWidgetItem(author));
        mynetmaintable->item(netrowcount,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        mynetmaintable->plist->addMedia(QMediaContent(listmp3Url.at(nowrow)));

        mynetmaintable->mysetCurrentMedia(netrowcount);
        player->setMedia(mynetmaintable->myCurrentMedia());
        player->play();
    }
}
void MyMainDlg::shownowplaylabel(QMediaContent media)
{
    lrc_map.clear();
    lrc->label->setText("音乐");
    lrcshowedit->setTextColor(Qt::white);
    ui->label_pic->setPixmap(QPixmap(":/image/musichead.ico"));
    if(nowplaylist==1)
    {
        QFile file(media.canonicalUrl().toString());
        QFileInfo info(file);
        QString name=info.baseName();
        nowplaywid->setText(name);
        music_name_label->setText(name);

        QString url4="D://ZeusAlbum/"+name+".jpg";
        QFile file4(url4);
        if(file4.exists())//如果存在专辑图片 加载图片
         {
             file4.open(QIODevice::ReadOnly);
             QByteArray byt=file4.readAll();
             file4.close();
             QPixmap *pix=new QPixmap();
             pix->loadFromData(byt);
             ui->label_pic->setPixmap(pix->scaled(60,60));
         }
         else
         {
             QString url="D://ZeusAlbum/"+name+".jpg";
             MyNetWork *network=new MyNetWork;
             network->requestalbum(name.replace("&",""),url);
             connect(network,SIGNAL(setpic(QByteArray)),this,SLOT(setlabelpic(QByteArray)));
         }


    }
    else//如果在第二播放列表
    {
      int cur= mynetmaintable->nowindex;//播放列表的正在播放行
      QString songname=mynetmaintable->item(cur,0)->text();
      QString author=mynetmaintable->item(cur,1)->text();
      netnowplaysongname=author+"-"+songname;

      nowplaywid->setText(netnowplaysongname);
      music_name_label->setText(netnowplaysongname);
 /////////////////////////////////////////////////////////////////////////请求专辑图片
      QString url="D://ZeusAlbum/"+netnowplaysongname+".jpg";
      QFile file(url);
      if(file.exists())//如果存在专辑图片 加载图片
       {
           file.open(QIODevice::ReadOnly);
           QByteArray byt=  file.readAll();
           file.close();
           QPixmap *pix=new QPixmap();
           pix->loadFromData(byt);
           ui->label_pic->setPixmap(pix->scaled(60,60));
       }
       else
       {
           QString url="D://ZeusAlbum/"+netnowplaysongname+".jpg";
           MyNetWork *network=new MyNetWork;
           network->requestalbum(netnowplaysongname.replace("&",""),url);
           connect(network,SIGNAL(setpic(QByteArray)),this,SLOT(setlabelpic(QByteArray)));
       }
  ///////////////////////////////////////////////////////////////////////////////请求歌词
       QString url2="D://ZeusLrc/"+netnowplaysongname+".lrc";
       QFile file2(url2);
       if(file2.exists())//如果存在歌词加载歌词
       {
           file2.open(QIODevice::ReadOnly|QIODevice::Text);
           QTextStream read(&file2);
           QString lrccontent=read.readAll();
           file2.close();
              ///////////////////////////////////////////////////////
             analysislrc(lrccontent);
              ///////////////////////////////////////////////////////
             lrcshowedit->clear();//防止bug出现
             lrcshowedit->setAlignment(Qt::AlignHCenter);
             foreach(QString strrr,lrc_map)
             {
                 strrr=strrr+"\n";
                 lrcshowedit->insertPlainText(strrr);
                 lrcshowedit->setAlignment(Qt::AlignHCenter);
             }
             QTextCursor textcur=lrcshowedit->textCursor();
             textcur.setPosition(0);
             lrcshowedit->verticalScrollBar()->setValue(0);
       }
       else
       {
           ///请求歌词
           lrcshowedit->setText("正在加载网络歌词~");
           MyNetWork *network2=new MyNetWork;
           network2->requestlrc(netnowplaysongname.replace("&",""),url2);
           connect(network2,SIGNAL(dolrcworkfinished(QByteArray)),this,SLOT(replyLrc(QByteArray)));//连接信号与槽
       }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

}
void MyMainDlg::seatabent(QModelIndex index)
{
    int row=index.row();
    qDebug()<<row;
}
void MyMainDlg::searchdownui()//下载的界面
{
    tabwidget=new QTabWidget(this);
    QWidget *nowdownwid=new QWidget(tabwidget);
    QWidget *donwfinwid=new QWidget(tabwidget);
    tabwidget->addTab(nowdownwid,"正在下载");
    tabwidget->addTab(donwfinwid,"下载完成");
    tabwidget->setDocumentMode(true);
    tabwidget->setStyleSheet("background-color: rgb(250,250,250);");//下载界面背景颜色
    tabwidget->tabBar()->setStyleSheet("color: gray;");
    /////////////////////////////////////下载列表的样式
    downloadtable=new QTableWidget(nowdownwid);
    downloadtable->setMouseTracking(true);
    downloadtable->setFrameShadow(QFrame::Plain);//设置平的样式
    downloadtable->setFrameShape(QFrame::NoFrame);//设置无边样式
    downloadtable->setFocusPolicy(Qt::NoFocus);
    downloadtable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    downloadtable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
    downloadtable->setShowGrid(false);//隐藏线
    downloadtable->verticalHeader()->setVisible(false);//设置不可见
    downloadtable->setEditTriggers(QTableWidget::NoEditTriggers);//不可编辑
    downloadtable->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    downloadtable->setSelectionMode ( QAbstractItemView::NoSelection);//单选
    downloadtable->horizontalHeader()->setHighlightSections(false);//不能鼠标点击
    downloadtable->setStyleSheet("QTableWidget{font-size : 12px;color: rgb(65, 65, 65);}"
                                 "QTableWidget{selection-background-color: rgb(233,233,233);}"
                                 "QTableWidget::item{height:25;}");//background-color:rgb(242, 242, 242);//
    downloadtable->insertColumn(0);
    downloadtable->insertColumn(1);
    downloadtable->insertColumn(2);
    downloadtable->insertColumn(3);
    QStringList list;
    list<<"文件名称"<<"进度"<<"速度"<<"操作";
    downloadtable->setHorizontalHeaderLabels(list);
    QHeaderView *header=downloadtable->horizontalHeader();//调整大小
    header->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);border: 1px solid #383838;}");//
    header->resizeSection(0,100);
    header->resizeSection(1,100);
    header->resizeSection(2,100);
    header->setStretchLastSection(true);//延展最一个表头
    header->setSectionResizeMode(QHeaderView::Fixed);//不能更改列宽
    downloadtable->setGeometry(0,30,700,442);//下载管理三个键下面那个条条
    ///////////////////////////////////////
    downstart=new QPushButton("全部开始",nowdownwid);
    downpause=new QPushButton("全部暂停",nowdownwid);
    downdelall=new QPushButton("全部删除",nowdownwid);

    QFrame *frame=new QFrame(nowdownwid);
    frame->setGeometry(1,28,740,1);
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::HLine);

    downstart->setGeometry(5,5,55,20);//下载管理的三个键
    downpause->setGeometry(100,5,55,20);
    downdelall->setGeometry(195,5,55,20);
    downstart->setStyleSheet("QPushButton{background-color: rgb(128, 183, 241);color: rgb(255, 255, 255);border: NULL;border-radius:3px;}"
                             "QPushButton:hover{background-color: rgb(138, 193, 251);}");
    downpause->setStyleSheet("QPushButton{background-color: rgb(128, 183, 241);color: rgb(255, 255, 255);border: NULL;border-radius:3px;}"
                             "QPushButton:hover{background-color: rgb(138, 193, 251);}");
    downdelall->setStyleSheet("QPushButton{background-color: rgb(128, 183, 241);color: rgb(255, 255, 255);border: NULL;border-radius:3px;}"
                              "QPushButton:hover{background-color: rgb(138, 193, 251);}");

    downstart->setCursor(Qt::PointingHandCursor);//设置光标样式
    downpause->setCursor(Qt::PointingHandCursor);
    downdelall->setCursor(Qt::PointingHandCursor);
}

void MyMainDlg::searchsongui()//搜索网络歌曲界面的ui
{
   ///////////////////////////////////////////////////////////////////歌曲搜索框
    netseawidget =new QWidget(this);
    netseawidget->setGeometry(0,0,0,0);//设置动态起始的位置

    QHBoxLayout *hlyout=new QHBoxLayout;
    QVBoxLayout *vlyout=new QVBoxLayout;
    ledit=new QLineEdit;
    serbtn=new QPushButton;
    serbtn->setStyleSheet("QPushButton{background:transparent;}"
                          "QPushButton{border-image: url(:/image/search_16.ico);}");
    ledit->setStyleSheet("QLineEdit{border: 1px solid rgb(41, 57, 85);border-radius: 3px;background: gray;selection-background-color: green;font-size: 12px ;}"
                         "QLineEdit:hover{background: white;border: 1px solid blue;}");
    ledit->setContextMenuPolicy(Qt::NoContextMenu);
    connect(ledit,SIGNAL(returnPressed()),this,SLOT(leditreturnpressed()));
    serbtn->setFixedSize(16,16);
    ledit->setFixedSize(170,23);

    hlyout->addWidget(ledit);
    hlyout->addWidget(serbtn);
    hlyout->setSpacing(2);
    hlyout->setContentsMargins(0,0,0,0);
    vlyout->addLayout(hlyout);
    vlyout->setContentsMargins(0,0,0,0);//设置两个控件居中
    netseawidget->setLayout(vlyout);
    connect(serbtn,SIGNAL(clicked()),this,SLOT(songanaly()));//网络搜索按钮点击
  /////////////////////////////////////////////////////////////////////歌曲搜索显示界面
    searchtable=new mymaintablewidget(false);//新键一个mytable对象
    ////////////////////////////////////////////////////////////////
    netseauiwidget =new QWidget(this);
    QVBoxLayout *vlyout2=new QVBoxLayout;
    vlyout2->addWidget(searchtable);
    searchtable->setFixedSize(700,500);//length
    vlyout2->setSpacing(0);
    vlyout2->setContentsMargins(0,0,100,100);
    netseauiwidget->setLayout(vlyout2);
    netseauiwidget->setStyleSheet("background: rgb(250,250,250)");
}

void MyMainDlg::leditreturnpressed()//用于ledit的回车相应
{
   serbtn->click();
}

void MyMainDlg::songanaly()//网络搜索按钮
{
    searchtable->setRowCount(0);
    searchtable->clearContents();
   QString song=ledit->text().simplified();
   if(song.isEmpty())
       return;
   mynetwork->requestnetwork(song);
   loadlab->show();

}
void MyMainDlg::slotmynetwork(QByteArray byt)//由mynetwork发的信号槽
{
   listmp3Url.clear();
   listlrcurl.clear();
   listSqMusic.clear();
   listHqMusic.clear();
   listLqMusic.clear();
   loadlab->hide();//隐藏loading gif图片

    QJsonDocument doc=QJsonDocument::fromJson(byt);
    QJsonArray arry=doc.array();
    int count=arry.count();
    for(int i=0;i<count;i++)//在这里完成搜索插入列表
    {
       QJsonObject obj2=arry.at(i).toObject();
       listmp3Url<<obj2.value("ListenUrl").toString();//添加mp3Url
       listlrcurl<<obj2.value("LrcUrl").toString();//添加mp3歌词
       listSqMusic<<obj2.value("SqUrl").toString();//为下载
       listHqMusic<<obj2.value("HqUrl").toString();
       listLqMusic<<obj2.value("LqUrl").toString();


       QString songname=obj2.value("SongName").toString();
       QString artist=obj2.value("Artist").toString();

       QPushButton *addnetplaybtn=new QPushButton;
       QPushButton *downbtn=new QPushButton;

       addnetplaybtn->setCursor(QCursor(Qt::PointingHandCursor));
       downbtn->setCursor(QCursor(Qt::PointingHandCursor));

       addnetplaybtn->setStyleSheet("QPushButton{border-image: url(:/image/net_add.png);}");
       downbtn->setStyleSheet("QPushButton{border-image: url(:/image/net_download.png);}");
       addnetplaybtn->setFixedSize(16,16);
       downbtn->setFixedSize(16,16);
       QWidget *wid=new QWidget;
       QHBoxLayout *hlyout=new QHBoxLayout;
       QVBoxLayout* vlyout=new QVBoxLayout;
       hlyout->addWidget(addnetplaybtn);
       hlyout->addWidget(downbtn);
       hlyout->setSpacing(0);
       vlyout->addLayout(hlyout);
       vlyout->setContentsMargins(8,1,0,0);
       wid->setLayout(vlyout);

         int count=searchtable->rowCount();
         searchtable->insertRow(count);
         searchtable->setItem(count,0,new QTableWidgetItem(songname));
         searchtable->setItem(count,1,new QTableWidgetItem(artist));
         searchtable->setItem(count,2,new QTableWidgetItem(""));
         searchtable->setCellWidget(count,2,wid);

       connect(addnetplaybtn,SIGNAL(clicked()),this,SLOT(addplaynetListslot()));
       connect(downbtn,SIGNAL(clicked()),this,SLOT(downloadnetsong()));
       }

}


void MyMainDlg::addplaynetListslot()
{
    QPoint point=searchtable->mapFromGlobal(QCursor::pos());
    int nowrow=searchtable->indexAt(QPoint(point.x(),point.y()-18)).row();

    QString songname= searchtable->item(nowrow,0)->text();
    QString author=searchtable->item(nowrow,1)->text();
    int netrowcount= mynetmaintable->rowCount();

    mynetmaintable->insertRow(netrowcount);
    mynetmaintable->setItem(netrowcount,0,new QTableWidgetItem(songname));
    mynetmaintable->setItem(netrowcount,1,new QTableWidgetItem(author));
    mynetmaintable->item(netrowcount,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    mynetmaintable->plist->addMedia(QMediaContent(listmp3Url.at(nowrow)));

    QToolTip::showText(QCursor::pos(),"已添加到播放列表");
}
void MyMainDlg::downloadnetsong()//搜索框的确定下载按钮
{
    QPoint point=searchtable->mapFromGlobal(QCursor::pos());
    nowdownrow=searchtable->indexAt(QPoint(point.x(),point.y()-18)).row();

    QString songname2=searchtable->item(nowdownrow,0)->text();
    QString author=searchtable->item(nowdownrow,1)->text();
    downdlg->nowdownlabel->setText(author+"-"+songname2);
//////////////////////////////////////////////////////////
    bool SqUrl=listSqMusic.at(nowdownrow).isEmpty();//如果值为空就隐藏 否则就显示
    bool HqUrl=listHqMusic.at(nowdownrow).isEmpty();//一般品质
    bool LqUrl=listLqMusic.at(nowdownrow).isEmpty();
    if(SqUrl==true)
    downdlg->tablewid->setRowHidden(0,true);
    else
    downdlg->tablewid->setRowHidden(0,false);
    if(HqUrl==true)
    downdlg->tablewid->setRowHidden(1,true);
    else
    downdlg->tablewid->setRowHidden(1,false);
    if(LqUrl==true)
    downdlg->tablewid->setRowHidden(2,true);
    else
    downdlg->tablewid->setRowHidden(2,false);
///////////////////////////////////////////////////////

    QRect rect(this->geometry());
    downdlg->setGeometry(rect.x(),rect.y()+150,250,200);//设置位置
    downdlg->show();
}

void MyMainDlg::autonextsong(QMediaPlayer::MediaStatus stat)
{
    if(stat==QMediaPlayer::EndOfMedia)
    {
        if(nowplaylist==1)//第一row
        {
         mymaintable->mysetnext();
         player->setMedia(mymaintable->myCurrentMedia());
        }
        else
        {
            mynetmaintable->mysetnext();
            player->setMedia(mynetmaintable->myCurrentMedia());
        }
        player->play();
    }
}

void MyMainDlg::showlrcshoweditmenu(const QPoint &)
{
    QMenu *menu=new QMenu(this);
    menu->setContentsMargins(1,1,1,4);
    QAction *searchlrc=new QAction("手动搜索歌词",this);
    QAction *openlrc=new QAction("打开已保存的歌词",this);
    QAction *copylrc=new QAction("复制全部歌词",this);
    menu->addAction(searchlrc);
    menu->addAction(copylrc);
    menu->addAction(openlrc);
    if(player->currentMedia().canonicalUrl().toString()==NULL)//如果没有播放歌曲
    {
        searchlrc->setDisabled(true);

    }
    else
    {
        searchlrc->setEnabled(true);

    }
    connect(searchlrc,SIGNAL(triggered()),this,SLOT(searchlrcslot()));
    connect(openlrc,SIGNAL(triggered()),this,SLOT(openlrcfolder()));
    connect(copylrc,SIGNAL(triggered()),this,SLOT(copylrccontent()));
    menu->exec(QCursor::pos());
}

void MyMainDlg::searchlrcslot()
{
    lrcdlg->show();
    lrcdlg->ledit->setText(nowplaywid->text().simplified());
    lrcdlg->serbtn->click();//搜索
    lrcdlg->songtotalname=nowplaywid->text().simplified();
    lrcdlg->setGeometry(this->geometry().x(),this->geometry().y()+200,250,300);
}

void MyMainDlg::openlrcfolder()
{
    QString path("D://ZeusLrc");
    QDesktopServices open;
    open.openUrl(QUrl(path));
}

void MyMainDlg::copylrccontent()
{
    lrcshowedit->selectAll();
    lrcshowedit->copy();
    QToolTip::showText(QCursor::pos(),"已复制到粘贴板");
}

void MyMainDlg::setDialogStyleSheet()
{

    QString exit_style= "QPushButton{background:transparent;}"
                        "QPushButton{border-image: url(:image/close24.png);}"
                        "QPushButton:hover{border-image: url(:image/close24_2.png);}";
    QString mini_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/minimize.png);}"
                       "QPushButton:hover{border-image: url(:image/minimize2.png);}";
    play_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/play_unhover.png);}"
                       "QPushButton:hover{border-image: url(:image/play_hover.png);}";
    QString next_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/next_unhover.png);}"
                       "QPushButton:hover{border-image: url(:image/next_hover.png);}";
    QString last_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/prev_unhover.png);}"
                       "QPushButton:hover{border-image: url(:image/prev_hover.png);}";
    pause_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/pause_unhover.png);}"
                       "QPushButton:hover{border-image: url(:image/pause_hover.png);}";
    QString slider_style="QSlider::groove:horizontal{border:0px;height:4px;}"
                         "QSlider::sub-page:horizontal{background:white;}"
                         "QSlider::add-page:horizontal{background:lightgray;}"
                         "QSlider::handle:horizontal{background:white;width:10px;border-radius:5px;margin:-3px 0px -3px 0px;}";
    QString vol_style="QPushButton{background:transparent;}"
                      "QPushButton{border-image: url(:image/volume.png);}";

    ui->pushButton_vol->setStyleSheet(vol_style);
    ui->horizontalSlider_vol->setStyleSheet(slider_style);
    ui->horizontalSlider->setStyleSheet(slider_style);
    ui->pushButton_exit->setStyleSheet(exit_style);
    ui->pushButton_mini->setStyleSheet(mini_style);

    //用Ctrl+左右键切歌到上一首或下一首
    ui->pushButton_next->setToolTip("下一曲");
    ui->pushButton_next->setShortcut(QKeySequence("Ctrl+Right"));
    ui->pushButton_backward->setToolTip("上一曲");
    ui->pushButton_backward->setShortcut(QKeySequence("Ctrl+Left"));

    ui->listWidget_side->setStyleSheet("QListWidget{background:transparent;color: white;}"
                                       "QListWidget::item{height: 30;font-size : 12px;};");
    //两种样式
    ui->widget_search->setStyleSheet("background-color:rgb(255, 255, 255,150)");

    netseawidget->setStyleSheet("background-color:rgb(255, 255, 255,150)");

    ui->lineEdit_search->setStyleSheet("background-color: rgb(255, 255, 255)");


    ui->pushButton_playpause->setStyleSheet(play_style);
    ui->pushButton_next->setStyleSheet(next_style);
    ui->pushButton_backward->setStyleSheet(last_style);
    ui->pushButton_skinbox->setStyleSheet("QPushButton{background:transparent;}"
                                          "QPushButton{border-image: url(:/image/skinbox.png);}"
                                          "QPushButton:hover{border-image: url(:/image/skinbox-press.png);}");
    ui->pushButton_add->setFocusPolicy(Qt::NoFocus);//设置没有先中虚线
    ui->pushButton_search->setFocusPolicy(Qt::NoFocus);//
    ui->pushButton_location->setFocusPolicy(Qt::NoFocus);//
    ui->pushButton_playmode->setFocusPolicy(Qt::NoFocus);//

    ui->pushButton_add->setStyleSheet("QPushButton::menu-indicator{image:None;}"
                                      "QPushButton{background:transparent;}"
                                      "QPushButton{border-image: url(:/image/add.png);}"
                                      "QPushButton:hover{border-image: url(:/image/add_hover.png);}");
    ui->pushButton_search->setStyleSheet("QPushButton{background:transparent;}"
                                         "QPushButton{border-image: url(:/image/search.png);}"
                                         "QPushButton:hover{border-image: url(:/image/search_hover.png);}");
    ui->pushButton_location->setStyleSheet("QPushButton{background:transparent;}"
                                        "QPushButton{border-image: url(:/image/location.png);}"
                                        "QPushButton:hover{border-image: url(:/image/location_hover.png);}");
    ui->pushButton_playmode->setStyleSheet("QPushButton::menu-indicator{image:None;}"
                                           "QPushButton{background:transparent;}"
                                           "QPushButton{border-image: url(:/image/playmode.png);}"
                                           "QPushButton:hover{border-image: url(:/image/playmode_hover.png);}");
    ui->checkBox->setStyleSheet("QCheckBox{color: rgb(255, 255, 255);}"
                                "QCheckBox::indicator::unchecked {image: url(:/image/unchecked.png);}"
                                "QCheckBox::indicator::checked{image: url(:/image/checked .png)}");


    ui->pushButton_up->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/1111.png);}");
    ui->pushButton_down->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/2222.png);}");

    ui->pushButton_webplayer->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/1.png);}");
    ui->pushButton_fmradio->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/2.png);}");
    ui->pushButton_videoplayer->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/4.png);}");
    ui->pushButton_minesweeping->setStyleSheet("QPushButton{background:transparent;}"
                                     "QPushButton{border-image:url(:/image/3.png);}");
}

void MyMainDlg::setbtnmenu()//里面有包含按钮的菜单
{
    QMenu *addmenu=new QMenu(this);
    addmenu->setContentsMargins(1,1,1,4);
    QAction *addfile=new QAction("添加文件",this);
    QAction *addfolder=new QAction("添加文件夹",this);
    addmenu->addAction(addfile);
    addmenu->addAction(addfolder);
    ui->pushButton_add->setMenu(addmenu);
    connect(addfile,SIGNAL(triggered()),this,SLOT(slot_addFile()));
    connect(addfolder,SIGNAL(triggered()),this,SLOT(addFolder()));
    /////////////////////////////////////////
    actionLoop =new QAction("  列表循环",this);
    actionLoop->setCheckable(true);
    actionLoop->setChecked(true);
    actionRandom =new QAction("  随机播放",this);
    actionRandom->setCheckable(true);
    actionCurrentItemInLoop =new QAction("  单曲循环",this);
    actionCurrentItemInLoop->setCheckable(true);
    playmode=new QMenu;
    playmode->setContentsMargins(1,1,1,4);

    playmode->addAction(actionLoop);
    playmode->addAction(actionRandom);
    playmode->addAction(actionCurrentItemInLoop);
    ui->pushButton_playmode->setMenu(playmode);

    actionGroupMode = new QActionGroup(this);
    actionGroupMode->addAction(actionLoop);
    actionGroupMode->addAction(actionRandom);
    actionGroupMode->addAction(actionCurrentItemInLoop);
    connect(actionGroupMode, SIGNAL(triggered(QAction*)), this, SLOT(modeAction(QAction*)));

}

void MyMainDlg::addFolder()//添加文件夹
{
    QString dirrr = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks);
    QDir dir(dirrr);
        if(!dir.exists())
        {
            return;
        }
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QFileInfoList list = dir.entryInfoList();


        int file_count = list.count();
        qDebug()<<file_count;
        if(file_count <= 0)
        {
            return;
        }

        QStringList files;
        for(int i=0; i<file_count;i++)
        {
            qDebug()<<i;
            QFileInfo file_info = list.at(i);
            QString suffix = file_info.suffix();
            qDebug()<<suffix;
            if(QString::compare(suffix, QString("mp3"), Qt::CaseInsensitive) == 0)
            {
                QString absolute_file_path = file_info.absoluteFilePath();
                qDebug()<<absolute_file_path;
                files.append(absolute_file_path);
            }
        }
        if(files.isEmpty())
            return;
                    int i=0;
                    while(i<files.count())
                    {
                        QString path=QDir::toNativeSeparators(files.at(i));
                        if(!path.isEmpty())
                        {
                      //      playList->addMedia(QMediaContent(QUrl::fromLocalFile(path)));
                            mymaintable->plist->addMedia(QMediaContent(QUrl::fromLocalFile(path)));
                        }
                      QFileInfo info(files[i]);
                      QString m_name=info.completeBaseName();
                      QStringList list=m_name.split("-");
                      QString songname=list.at(1);
                      QString singer=list.at(0);
                      int rowcount= mymaintable->rowCount();
                      mymaintable->insertRow(rowcount);
                      mymaintable->setItem(rowcount,0,new QTableWidgetItem(songname));
                      mymaintable->setItem(rowcount, 1, new QTableWidgetItem(singer));
                      mymaintable->item(rowcount,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                      i++;
                    }


    ////////////////////////////////////////////////////////////////////////////////////// 跳回播放列表

}

void MyMainDlg::setsearchitems(QString words)
{
    qDebug()<<words;
    int count= mymaintable->rowCount();
    for(int i=0;i<count;i++)
    {
         mymaintable->setRowHeight(i,0);
        if( mymaintable->item(i,0)->text().contains(words)|| mymaintable->item(i,1)->text().contains(words))
        {
             mymaintable->setRowHeight(i,30);
            continue;
        }
        if(words=="")
        {
             mymaintable->setRowHeight(i,30);
        }
    }
}

void MyMainDlg::showTableToolTip(QModelIndex )
{
    int index= mymaintable->indexAt( mymaintable->mapFromGlobal(QCursor::pos())).row();//获取button所在行号
    QToolTip::showText(QCursor::pos(), mymaintable->item(index,1)->text()+"-"+ mymaintable->item(index,0)->text());
    /////////////////////////////////////////////////////////////////////////////////

}

void MyMainDlg::delitem()
{

    int index= mymaintable->currentRow();
    if(index==mymaintable->nowindex)//如果遇到正在播放的歌曲
    {
        mymaintable->mysetnext();
        player->setMedia(mymaintable->plist->media(mymaintable->nowindex));
        player->play();
    }
     mymaintable->mydelitem(index);
     mymaintable->removeRow(index);
}

void MyMainDlg::trayiconmenu()
{
    trayIcon=new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(tr(":image/sysicon.ico")));
    trayIcon->show();
    aboutapp=new QAction("   关于程序",this);
    quitapp=new QAction(QIcon(QPixmap(":/image/MD-brightness.png")), "   退出",this);
    QAction *activiteapp=new QAction("   打开主界面",this);
    QAction *updateapp=new QAction("   检查版本",this);
    QAction *showlrc=new QAction("   打开歌词",this);
    QAction *hidelrc=new QAction("   关闭歌词",this);
    playmenuaction=new QWidgetAction(this);
    play_button = new QPushButton();
    QPushButton*backward_button = new QPushButton();
    QPushButton*forward_button = new QPushButton();
    music_name_label = new QLabel();
    QWidget *play_widget = new QWidget;

    play_button->setCursor(QCursor(Qt::PointingHandCursor));
    backward_button->setCursor(QCursor(Qt::PointingHandCursor));
    forward_button->setCursor(QCursor(Qt::PointingHandCursor));

    play_button->setFlat(true);
    backward_button->setFlat(true);
    forward_button->setFlat(true);
    play_button->setStyleSheet("QPushButton{border-image: url(:/image/menuplay.png);}");
    backward_button->setStyleSheet("QPushButton{border-image: url(:/image/menuback.png);}");
    forward_button->setStyleSheet("QPushButton{border-image: url(:/image/menuforward.png);}");
    play_button->setFixedSize(26,26);
    backward_button->setFixedSize(25,25);
    forward_button->setFixedSize(25,25);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(backward_button);
    layout->addWidget(play_button);
    layout->addWidget(forward_button);
    layout->setSpacing(0);
    layout->setContentsMargins(10,0,10,0);


    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addLayout(layout);
    layout2->addWidget(music_name_label, 0, Qt::AlignCenter);
    layout2->setSpacing(2);
    layout2->setContentsMargins(0,5,0,0);
    music_name_label->setText("音乐");
    music_name_label->setEnabled(false);
    play_widget->setLayout(layout2);
    play_widget->setFixedSize(140,60);//防止BUG有时候layout有问题
    playmenuaction->setDefaultWidget(play_widget);

    trayIconMenu=new QMenu(this);
    trayIconMenu->addAction(playmenuaction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(activiteapp);
    trayIconMenu->addAction(showlrc);
    trayIconMenu->addAction(hidelrc);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutapp);
    trayIconMenu->addAction(updateapp);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitapp);
    trayIconMenu->setContentsMargins(1,1,1,5);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setToolTip("欢迎使用-zeusplayer");

    connect(showlrc,SIGNAL(triggered()),this,SLOT(traymenushowlrc()));
    connect(hidelrc,SIGNAL(triggered()),this,SLOT(traymenuhidelrc()));
    connect(activiteapp,SIGNAL(triggered(bool)),this,SLOT(activitewindows()));
    connect(aboutapp,SIGNAL(triggered()),this,SLOT(about()));
    connect(quitapp, SIGNAL(triggered()),this,SLOT(saveList()));
    connect(quitapp, SIGNAL(triggered()), qApp, SLOT(quit()));//退出
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this,SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
    connect(play_button,SIGNAL(clicked(bool)),ui->pushButton_playpause,SIGNAL(clicked(bool)));

    connect(forward_button,SIGNAL(clicked(bool)),ui->pushButton_next,SIGNAL(clicked(bool)));
    connect(backward_button,SIGNAL(clicked(bool)),ui->pushButton_backward,SIGNAL(clicked(bool)));
}

void MyMainDlg::traymenushowlrc()
{
    if(ui->checkBox->checkState()==Qt::Checked)
        return;
    ui->checkBox->click();
}

void MyMainDlg::traymenuhidelrc()
{
    if(ui->checkBox->checkState()==Qt::Unchecked)
        return;
    ui->checkBox->click();
}

void MyMainDlg::setBk(QString picName)
{
    saveskinname=picName;//保存当前皮肤
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/image/"+picName+".png")));
    setPalette(palette);
}
void MyMainDlg::activitewindows()
{
    this->showNormal();
    this->activateWindow();
}

void MyMainDlg::seteditlrc(QMediaContent media)//这个是bug
{

  if(nowplaylist==1)
  {
    QUrl url=media.canonicalUrl();
    QFile file2(url.toString());
     QFileInfo info(file2);
///////////////////////////////////////////////////////////////////////歌曲文件下的歌词文件
    QString songfilename=url.toString();
 //   qDebug()<<songfilename;
    QString lrcremovefilename=songfilename.remove(songfilename.left(8));
    QString lrcremovefilemp3=lrcremovefilename.remove(lrcremovefilename.right(3));
    QString lrcfilename=lrcremovefilemp3+"lrc";
///////////////////////////////////////////////////////////////////////Execellentlrc文件夹下的
    QString path("D://ZeusLrc");
    QString  barename=info.fileName();
    QString lrcname=barename.remove("mp3")+"lrc";
    path2lrc=path+'/'+lrcname;
    QFile filesave(path2lrc);//歌词文件第二个

    ////////////////////////////////////////////////////////////////////////
 QFile file1(lrcfilename);//歌词在歌曲目录下的
 if(file1.exists())//如果文件存在
 {
      if(!file1.open(QIODevice::ReadOnly|QIODevice::Text))
      {
       lrcshowedit->setAlignment(Qt::AlignHCenter);
       lrc_map.clear();//程序启动时不会擦掉zeusplayer
       return;
      }
        QTextStream writein(&file1);
        QString lrccontent=writein.readAll();
        file1.close();
        lrc_map.clear();
    ///////////////////////////////////////////////////////
    analysislrc(lrccontent);
    ///////////////////////////////////////////////////////
    lrcshowedit->clear();//去除bug
    lrcshowedit->setAlignment(Qt::AlignHCenter);
    foreach(QString strrr,lrc_map)
    {
        strrr=strrr+"\n";
        lrcshowedit->insertPlainText(strrr);
        lrcshowedit->setAlignment(Qt::AlignHCenter);
    }
    QTextCursor textcur=lrcshowedit->textCursor();
    textcur.setPosition(0);
    lrcshowedit->verticalScrollBar()->setValue(0);
    return;
    /////////////////////////////////////////////////设置对齐方式
    ///
 }
   else if(filesave.exists())//如果存在在D:ZeusLrc中的话
      {

          if(!filesave.open(QIODevice::ReadOnly|QIODevice::Text))
          {
              QMessageBox::information(this,"关于","歌词打不开");
          }
          QTextStream read(&filesave);
          QString lrccontent=read.readAll();
             filesave.close();
             ///////////////////////////////////////////////////////
            analysislrc(lrccontent);
             ///////////////////////////////////////////////////////
            lrcshowedit->clear();//防止bug出现
            lrcshowedit->setAlignment(Qt::AlignHCenter);
            foreach(QString strrr,lrc_map)
            {
                strrr=strrr+"\n";
                lrcshowedit->insertPlainText(strrr);
                lrcshowedit->setAlignment(Qt::AlignHCenter);
            }
            QTextCursor textcur=lrcshowedit->textCursor();
            textcur.setPosition(0);
            lrcshowedit->verticalScrollBar()->setValue(0);
            return;
      }
      else//如果两个地方都没有歌词文件
      {
         lrcshowedit->clear();
         lrcshowedit->setPlainText("正在加载网络歌词");
         QString barename=info.baseName();
        if(barename.contains(QRegExp("dx")))//如果包含数字3就退出
            return;
        MyNetWork *network=new MyNetWork;
         network->requestlrc(barename.replace("&",""),path2lrc);//交给mynetwork，请求歌词与位置
         connect(network,SIGNAL(dolrcworkfinished(QByteArray)),this,SLOT(replyLrc(QByteArray)));//连接信号与槽
     }
  }
  else
    {
      return;
    }
}
void MyMainDlg::analysislrc(QString lrccontent11)
{
    lrc_map.clear();

    QString all_text;
    if(lrccontent11.split("\n").length()<10)//如果小于十行的
    {
    QStringList list=lrccontent11.split("[");
    QString getstr;
    for(int i=0;i<list.count();i++)  
    getstr+="["+list.at(i)+"\n";
    list.empty();
    all_text=getstr;
    }
    else
    {
        all_text=lrccontent11;
    }
    QStringList lines = all_text.split("\n");
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");//这个是时间标签的格式[00:05.54]
                                            //正则表达式d{2}表示匹配2个数字
    foreach(QString oneline, lines) {
        QString temp = oneline;
        temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
        // 然后依次获取当前行中的所有时间标签          ，并分别与歌词文本存入QMap中
        //indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
        //正常情况下pos后面应该对应的是歌词文件
        int pos = rx.indexIn(oneline, 0);
        while (pos != -1) { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
            // 插入到lrc_map中
            lrc_map.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
    }
    lrcshowedit->clear();
}
void MyMainDlg::replyLrc(QByteArray byt)//json返回的内容解析
{
    QString showlrc(byt);
    analysislrc(showlrc);
   ///////////////////////////////////////////////////////
     lrcshowedit->setAlignment(Qt::AlignHCenter);
     foreach(QString strrr,lrc_map)
     {
       strrr=strrr+"\n";
       lrcshowedit->insertPlainText(strrr);
       lrcshowedit->setAlignment(Qt::AlignHCenter);
     }
    /////////////////用于lrc处理全部红色的bug
     QTextCursor textcur=lrcshowedit->textCursor();
     textcur.select(QTextCursor::Document);
     QTextCharFormat formatchar;
     formatchar.setForeground(Qt::white);
     textcur.mergeCharFormat(formatchar);
     lrcshowedit->mergeCurrentCharFormat(formatchar);
     textcur.setPosition(0);
     lrcshowedit->verticalScrollBar()->setValue(0);

    ///////////////////////////////////////////////////////先关闭保存文件  必须使用这个方法

}


void MyMainDlg::paintEvent(QPaintEvent *)
{

}

bool MyMainDlg::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->label_title||obj==nowplaywid)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(event->type()==QEvent::MouseButtonPress)
        {
            if(mouseEvent->button()==Qt::LeftButton)
            {
            m_WindowPos = this->pos();
            m_MousePos = mouseEvent->globalPos();
            m_MousePressed = true;
            }
        }
        if(event->type()==QEvent::MouseMove)
        {
            if (m_MousePressed)
                {
                   this->move(m_WindowPos +(mouseEvent->globalPos()-m_MousePos));

                }
        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
            if(mouseEvent->button()==Qt::LeftButton)
                m_MousePressed = false;
        }
    }

    if(obj==ui->label_pic)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            ui->listWidget_side->setCurrentRow(0);//点击就跳转到0
        }
    }
    if(obj==ui->horizontalSlider_vol)                          //判断是哪个控件（音量滑块）
      {
          if (event->type()==QEvent::MouseButtonPress)           //判断类型
          {
              QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
              if (mouseEvent->button() == Qt::LeftButton)	//判断左键
              {
                 int dur = ui->horizontalSlider_vol->maximum() - ui->horizontalSlider_vol->minimum();
                 volpos = ui->horizontalSlider_vol->minimum() + dur * ((double)mouseEvent->x() / ui->horizontalSlider_vol->width());
                 if(volpos != ui->horizontalSlider_vol->sliderPosition())
                  {
                    ui->horizontalSlider_vol->setValue(volpos);
                    QToolTip::showText(QCursor::pos(),QString::number(ui->horizontalSlider_vol->value()));
                    if(volpos>=100)
                        QToolTip::showText(QCursor::pos(),QString::number(100));
                    if(volpos<=0)
                        QToolTip::showText(QCursor::pos(),QString::number(0));
                  }
              }
          }

      }
    if(obj==ui->horizontalSlider)                   //判断是哪个控件（进度）
      {
          if (event->type()==QEvent::MouseButtonPress)           //判断类型
          {
              QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
              if (mouseEvent->button() == Qt::LeftButton)	//判断左键
              {
                 int dur = ui->horizontalSlider->maximum() - ui->horizontalSlider->minimum();
                 int pos = ui->horizontalSlider->minimum() + dur * ((double)mouseEvent->x() / ui->horizontalSlider->width());
                 if(pos != ui->horizontalSlider->sliderPosition())
                  {
                    ui->horizontalSlider->setValue(pos);
                    player->setPosition(pos);
                  }
              }

          }

      }

    if(obj==lrcshowedit->viewport())//歌词移动
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                lrcmove=true;
                lrcshowedit->viewport()->setCursor(QCursor(QPixmap(":/image/cursor_drag_hand.png")));//原始形状的cursor
            }
        }
        if(event->type()==QEvent::MouseButtonRelease)//还原
        {

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                lrcshowedit->viewport()->setCursor(QCursor(QPixmap(":/image/cursor_hand.png")));//原始形状的cursor
            }
        }
        if(event->type()==QEvent::MouseMove)
        {
            if(lrcmove==true)//如果为真
            {
                lrcshowedit->verticalScrollBar()->value();

                int nowypos =this->cursor().pos().y();
                if(nowypos<lastypos)
                {
                    lrcshowedit->verticalScrollBar()->setValue(lrcshowedit->verticalScrollBar()->value()+1);
                }
                if(nowypos>=lastypos)
                {
                    lrcshowedit->verticalScrollBar()->setValue(lrcshowedit->verticalScrollBar()->value()-1);
                }
                    lastypos=nowypos;
                    lrcshowedit->setTextInteractionFlags( Qt::NoTextInteraction);//防止选择文字
                    m_MousePressed=false;//防止出现bug//乱跑
            }
        }
    }
    if(obj==ui->listWidget_side->viewport())
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            box->hide();
        }
        if(event->type()==QEvent::MouseMove)
        {
            QListWidgetItem *itemss=ui->listWidget_side->item(previousitem);
            QModelIndex index= ui->listWidget_side->indexAt(ui->listWidget_side->mapFromGlobal(QCursor::pos()));
            int nowrow=index.row();
            if(itemss!=Q_NULLPTR&&previousitem!=ui->listWidget_side->currentRow())
            {
            ui->listWidget_side->item(previousitem)->setBackgroundColor(Qt::transparent);
            ui->listWidget_side->item(previousitem)->setBackgroundColor(Qt::transparent);
            }
            if(ui->listWidget_side->itemAt(ui->listWidget_side->mapFromGlobal(QCursor::pos()))!=NULL&&nowrow!=ui->listWidget_side->currentRow())
            {
            ui->listWidget_side->item(nowrow)->setBackgroundColor(QColor(25,65,65,100));
            ui->listWidget_side->item(nowrow)->setBackgroundColor(QColor(25,65,65,100));
            previousitem=nowrow;
            }
        }
        if(event->type()==QEvent::Leave)
        {
            QListWidgetItem *itemss=ui->listWidget_side->item(previousitem);
            if(itemss!=Q_NULLPTR&&previousitem!=ui->listWidget_side->currentRow())
            {
            ui->listWidget_side->item(previousitem)->setBackgroundColor(Qt::transparent);
            ui->listWidget_side->item(previousitem)->setBackgroundColor(Qt::transparent);
            }
        }
    }
       return QObject::eventFilter(obj, event);
}
void MyMainDlg::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}
void MyMainDlg::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    for(int i=0;i<urls.size();i++)//遍历 应该使用forreach();
    {
        if(urls.at(i).toString().contains(".mp3"))
        {
          mymaintable->plist->addMedia(QMediaContent(QUrl(urls.at(i))));//添加到播放列表
          QFile files(urls.at(i).toString());
          QFileInfo info(files);
          QString m_name=info.completeBaseName();
          QString songname;
          QString singer;
          if(m_name.contains("-"))//如果遍历的时候包含了"-"这个字符
          {
            QStringList list=m_name.split("-");
            songname=list.at(1);
            singer=list.at(0);
          }
          else
          {
              songname=m_name;
              singer="";
          }
          int rowcount= mymaintable->rowCount();
           mymaintable->insertRow(rowcount);
           mymaintable->setItem(rowcount,0,new QTableWidgetItem(songname));
           mymaintable->setItem(rowcount, 1, new QTableWidgetItem(singer));
           mymaintable->item(rowcount,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        }
    }
}

void MyMainDlg::ShownetContextMenu(const QPoint& pos)
{
    QPoint globalPos =mynetmaintable->mapToGlobal(pos);
       QMenu *myMenu=new QMenu(this);
       myMenu->setContentsMargins(1,1,1,4);
       QAction *play=new QAction("  播 放",this);
       QAction *location=new QAction("  定位",this);
       QAction *deletesong=new QAction("  删除歌曲",this);
       QAction *empty=new QAction("  清空网络列表",this);
       if(mynetmaintable->itemAt(mynetmaintable->mapFromGlobal(QCursor::pos()))!=NULL)//如果在上面
       {
                 myMenu->addAction(play);
                 myMenu->addAction(location);
                 myMenu->addAction(deletesong);
       }
       myMenu->addAction(empty);
       connect(empty,SIGNAL(triggered()),this,SLOT(netplaylistempty()));
       connect(location,SIGNAL(triggered()),this,SLOT(netlocationplaylist()));
       connect(play,SIGNAL(triggered()),this,SLOT(netplay()));
       connect(deletesong,SIGNAL(triggered()),this,SLOT(netdeleteplaylist()));
       myMenu->exec(globalPos);
}
void MyMainDlg::netplaylistempty()
{
    ui->label_pic->setPixmap(QPixmap(":/image/musichead.ico"));
    mynetmaintable->clear();
    mynetmaintable->setRowCount(0);
    mynetmaintable->plist->clear();
    if(nowplaylist!=1)//如果正在播放当前的列表 就停止
    {
        player->pause();
        player->stop();
        player->dumpObjectInfo();
    }

    lrcshowedit->clear();
    nowplaytext="";
    music_name_label->setText("");
    ui->pushButton_playpause->setToolTip("播放");
    nowplaywid->setText("");
    ui->label_playtime->setText("00:00/00:00");

}
void MyMainDlg::netlocationplaylist()
{
   int nowdex= mynetmaintable->nowindex;
   mynetmaintable->setCurrentItem(mynetmaintable->item(nowdex,0));
   mynetmaintable->scrollToItem(mynetmaintable->item(nowdex,0));
}
void MyMainDlg::netplay()
{
   emit mynetmaintable->itemDoubleClicked(mynetmaintable->currentItem());
}
void MyMainDlg::netdeleteplaylist()
{
    int index=mynetmaintable->currentRow();
    if(index==mynetmaintable->nowindex)//如果遇到正在播放的歌曲
    {
        mynetmaintable->mysetnext();
        player->setMedia(mynetmaintable->plist->media(mynetmaintable->nowindex));
        player->play();
    }
    mynetmaintable->mydelitem(index);
    mynetmaintable->removeRow(index);

    if(mynetmaintable->plist->mediaCount()==0)//如果删除最后一首
    {
        netplaylistempty();
        player->dumpObjectInfo();
    }

}
void MyMainDlg::opensysfile()//打开并选中
{

    QUrl url=mymaintable->plist->media( mymaintable->currentRow()).canonicalUrl();
    QString fileFull=url.toLocalFile();
    fileFull.replace('/','\\');
}

void MyMainDlg::ShowContextMenu(const QPoint& pos)
{
       QPoint globalPos =  mymaintable->mapToGlobal(pos);
           myMenu=new QMenu(this);
           myMenu->setContentsMargins(1,1,1,4);
           QAction *play=new QAction("  播  放",this);
           QAction *songitem=new QAction("  歌曲定位",this);
           QAction *delsong=new QAction("  删除歌曲",this);
           QAction *playmodes=new QAction("  播放模式",this);
           QAction *opensysfile=new QAction("  打开文件夹",this);
           QAction *emptyList=new QAction("  清空列表",this);
           playmodes->setMenu(playmode);
           if( mymaintable->itemAt( mymaintable->mapFromGlobal(QCursor::pos()))!=NULL)
           {
           myMenu->addAction(play);
           myMenu->addAction(songitem);
           myMenu->addAction(delsong);
           myMenu->addAction(playmodes);
           myMenu->addAction(opensysfile);
           }
           myMenu->addAction(emptyList);
           connect(delsong,SIGNAL(triggered()),this,SLOT(delitem()));
           connect(emptyList,SIGNAL(triggered()),this,SLOT(emptyList()));
           connect(play,SIGNAL(triggered()),this,SLOT(tablemenuplay()));
           connect(songitem,SIGNAL(triggered()),this,SLOT(scrolltoitem()));//右键的歌曲定位
           connect(opensysfile,SIGNAL(triggered()),this,SLOT(opensysfile()));
           myMenu->exec(globalPos);

}
void MyMainDlg::emptyList()
{
    ui->label_pic->setPixmap(QPixmap(":/image/musichead.ico"));
    if(nowplaylist==1)//如果正在播放第一个列表
    {
      player->pause();
      player->stop();
      player->dumpObjectInfo();
    }
       mymaintable->setRowCount(0);
       mymaintable->plist->clear();
       mymaintable->clearContents();

      lrcshowedit->clear();
      nowplaytext="";
      music_name_label->setText("");
      ui->pushButton_playpause->setToolTip("播放");
      nowplaywid->setText("");
      ui->label_playtime->setText("00:00/00:00");

}
void MyMainDlg::tablemenuplay()
{
    emit mymaintable->itemDoubleClicked(mymaintable->currentItem());
}
void MyMainDlg::readlist()
{

    QFile file1("plist.m3u");
    if(file1.exists())//文件存在
    {
        file1.open(QIODevice::ReadOnly|QIODevice::Text);
        mymaintable->plist->load(&file1,"m3u");
    }
    file1.close();
    //////////////读取
    QFile fileskin("config.ini");//各种设置
    if(!fileskin.open(QIODevice::ReadOnly|QIODevice::Text))//如果打开失败了
    {
        emit box->skinChange("background2");
        box->setBk("background2");
        ui->horizontalSlider_vol->setValue(100);
        ui->listWidget_side->setCurrentRow(1);
        box->setslidervalue(150);
        return;
    }
    QTextStream readskin(&fileskin);
    QByteArray byt=readskin.readAll().toUtf8();
    QByteArray byt2=QByteArray::fromBase64(byt);

    fileskin.close();
    QJsonDocument json=QJsonDocument::fromJson( byt2);
    QJsonObject obj=json.object();
    ////////////////////////////////////背景
    QString background=obj.value("background").toString();
    emit box->skinChange(background);
    box->setBk(background);

    //////////////////////////////////
    QString strvol=obj.value("volume").toString();
    ui->horizontalSlider_vol->setValue(strvol.toInt());//记录的音量大小
    QString strcheck=obj.value("checkbox").toString();
    checkbox=strcheck.toInt();       //记录歌词的开关状态
    if(checkbox==1)
    {
        ui->checkBox->click();
    }

     /////////////////
    QString curlistitem= obj.value("currentlistitem").toString();
    if(curlistitem.toInt()==1)
    {
        ui->listWidget_side->setCurrentRow(1);
    }
    else
    {
        ui->listWidget_side->setCurrentRow(2);
    }
    QString opacity=obj.value("listopa").toString();
    box->setslidervalue(opacity.toInt());
   //////////////////////////////////
   QString textplaymode=obj.value("playmode").toString();
   if(textplaymode=="列表循环")
   {
       actionLoop->setChecked(true);
       emit actionGroupMode->triggered(actionLoop);
   }
   if(textplaymode=="随机播放")
   {
      actionRandom->setChecked(true);
      emit actionGroupMode->triggered(actionRandom);
   }
   if(textplaymode=="单曲循环")
   {
       actionCurrentItemInLoop->setChecked(true);
       emit actionGroupMode->triggered(actionCurrentItemInLoop);
   }

   ///////////////////////////////
    QFile file2("plist.m3u");
    file2.open(QIODevice::ReadOnly|QIODevice::Text);
    int songcount=mymaintable->plist->mediaCount();
    QTextStream textinput(&file2);
    int i=0;
    while(i<songcount)
    {
       QString songurl=textinput.readLine();
       QFile *file=new QFile(songurl);
       QFileInfo info(*file);
       QString barename=info.baseName();
       QString song;
       QString singer;
       if(!barename.contains('-'))
       {
            song=barename;
            singer="";
       }
       else
       {
         QStringList songlist=barename.split("-");
         singer=songlist.at(0);
         song=songlist.at(1);
       }

       int rownum= mymaintable->rowCount();
        mymaintable->insertRow(rownum);

        mymaintable->setItem(rownum, 0, new QTableWidgetItem(song));
       mymaintable->setItem(rownum, 1, new QTableWidgetItem(singer));
       mymaintable->item(rownum,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

       ///////////////////////////////////////////////
       i++;
    }
    file2.close();
///////////////////////////////////////////////////////////////////网络列表
    QFile file3("pnetlist.m3u");
    if(file3.exists())//文件存在
    {
        file3.open(QIODevice::ReadOnly|QIODevice::Text);
        mynetmaintable->plist->load(&file3,"m3u");
    }
    file3.close();

    QFile file4("pnetlist.tab");
    if(!file4.open(QIODevice::ReadOnly|QIODevice::Text))//如果打开网络列表失败
            return;
    int songcount2=mynetmaintable->plist->mediaCount();
    QTextStream textinput2(&file4);
    int j=0;
    while(j<songcount2)
    {
       QByteArray byt=textinput2.readLine().toUtf8();
       QByteArray byt2=QByteArray::fromBase64(byt);
       QString barename=QString(byt2);

       QStringList songlist=barename.split("-");

       QString singer=songlist.at(0);
       QString song=songlist.at(1);

       int rownum= mynetmaintable->rowCount();
       mynetmaintable->insertRow(rownum);

       mynetmaintable->setItem(rownum, 0, new QTableWidgetItem(song));
       mynetmaintable->setItem(rownum, 1, new QTableWidgetItem(singer));
       mynetmaintable->item(rownum,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
       ///////////////////////////////////////////////
       j++;
    }
    file4.close();
///////////////////////////////////////////////////////////////////网络列表
}

void MyMainDlg::saveList()
{
    QFile file2("pnetlist.m3u");
    file2.resize(0);
    file2.open(QIODevice::WriteOnly|QIODevice::Text);
    mynetmaintable->plist->save(&file2,"m3u");
    file2.close();


    QFile file3("pnetlist.tab");//用于显示tablewidgetitem
    file3.resize(0);
    if(!file3.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(this,"错误","保存网络列表错误！");
    }
    else
    {
        QTextStream in(&file3);
        for(int i=0;i<mynetmaintable->rowCount();i++)//行行保存
        {
           QString songname= mynetmaintable->item(i,0)->text();
           QString author= mynetmaintable->item(i,1)->text();
           QString total=author+"-"+songname;
           in<<total.toUtf8().toBase64()<<"\n";
        }
    }
    file3.close();

    QFile file("plist.m3u");
    file.resize(0);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    mymaintable->plist->save(&file,"m3u");
    file.close();

    //////////////////////////////////////////生成json
    QJsonObject json;
    json.insert("volume", QString::number(player->volume()));
    json.insert("background", QString(saveskinname));
    json.insert("currentlistitem",QString::number(nowplaylist));
    json.insert("checkbox", QString::number(checkbox));
    json.insert("listopa",QString::number(listopacity));
    json.insert("playmode",QString(actionGroupMode->checkedAction()->text().simplified()));

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    /////////////////////////////////////////////json文字写入文伯
    QFile fileskins("config.ini");
    fileskins.resize(0);//重新写入
    if(!fileskins.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(this,"提示","皮肤保存失败！");
        return;
    }
    QTextStream textoutputskin(&fileskins);//
    textoutputskin<<json_str.toUtf8().toBase64();
    fileskins.close();

     ////////////////


}
void MyMainDlg::scrolltoitem()
{
    QTableWidgetItem *item= mymaintable->item(mymaintable->nowindex,0);
     mymaintable->setCurrentItem(item);
     mymaintable->scrollToItem(item);
}

void MyMainDlg::setVolpic()
{
    QString vol_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/volume.png);}";
    ui->pushButton_vol->setStyleSheet(vol_style);
}

void MyMainDlg::about()
{
    this->showNormal();
    if(QMessageBox::Ok==QMessageBox::information(this,"关于zeusplayer",
                                                 "实现的功能有:\n"
                                                 "1.程序列表自动保存\n"
                                                 "2.托动文件到程序即可添加至播放列表\n"
                                                 "3.网络自动获取歌词文件,并保存至D://ZeusLrc\n"
                                                 "4.多线程处理歌词"
                                                 ,QMessageBox::Ok))
        return;

}
void MyMainDlg::trayiconActivated(QSystemTrayIcon::ActivationReason reason)

{

    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        this->setWindowState(Qt::WindowActive);//窗口由最小化激活下常
        this->activateWindow();//激活窗口在最上层
        this->raise();
        break;
    default:
        break;
    }
}
void MyMainDlg::closeEvent(QCloseEvent *event)
{

    if(trayIcon->isVisible())
    {
           QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");//动画特效
           animation->setDuration(1000);
           animation->setStartValue(1);
           animation->setEndValue(0);
           animation->start();
           connect(animation, SIGNAL(finished()), this, SLOT(animationfinished()));

      event->ignore();
    }
    else
    {
    event->accept();
}
}
void MyMainDlg::animationfinished()
{
    this->hide();
    this->setWindowOpacity(1);
}
void MyMainDlg::modeAction(QAction *act)//播放模式
{

    if (act == actionCurrentItemInLoop)
    {
        mynetmaintable->mysetPlaybackMode(1);
        mymaintable->mysetPlaybackMode(1);//单曲
    }
    else if (act == actionLoop)
    {
        mynetmaintable->mysetPlaybackMode(0);
        mymaintable->mysetPlaybackMode(0);//循环
    }
    else if (act == actionRandom)
    {
        mynetmaintable->mysetPlaybackMode(2);
        mymaintable->mysetPlaybackMode(2);//随机
    }
    // 设置当前播放模式
}

void MyMainDlg::changelistitem(int j)//把j付给一个全局值 再判断
{
    QTableWidgetItem *item= mymaintable->item(j,0);
     mymaintable->scrollToItem(item);
     mymaintable->setCurrentItem(item);
}


void MyMainDlg::positionChanged(qint64 position)//歌词滚动
{
    ui->horizontalSlider->setValue(position);
    QTime currentTime(0, (position/60000)%60, (position/1000)%60);//设置实时改变播放时间信息
    QString format = "mm:ss";
    currentTime.toString(format);
    QString todisplay;
    todisplay = currentTime.toString(format);
    ui->label_playtime->setText(todisplay+"/"+totaldisplay);
    //////////////////////////////////////////////
    qint64 total_time_value = player->duration();//直接获取该音频文件的总时长参数，单位为毫秒
    if(!lrc_map.isEmpty())//如果歌词不是空的
    {
        qint64 previous = 0;
        qint64 later = 0;
        foreach (qint64 value, lrc_map.keys())//查找
        {
            if (position >= value)//如果匹配
            {

                previous = value;

                QTextDocument *doc=lrcshowedit->document();
                QTextCursor  textCursor=lrcshowedit->textCursor();
////////////////////////////////////////previous先前的

                int positionspre=doc->findBlockByNumber(prviouslrc).position();
                textCursor.setPosition(positionspre,QTextCursor::MoveAnchor);
                lrcshowedit->setTextCursor(textCursor);
                if(!textCursor.hasSelection())
                    textCursor.select(QTextCursor::Document);
                QTextCharFormat formatpre;

                formatpre.setFont(QFont("微软雅黑", 10, 0));

                formatpre.setForeground(Qt::white);
                textCursor.mergeCharFormat(formatpre);

                ////////////////////////////////////当前的
                int nowlrc=lrc_map.keys().indexOf(previous);//根据时间获取歌词位置 第几行

                int positions=doc->findBlockByNumber(nowlrc).position();//Block的位置
                textCursor.setPosition(positions,QTextCursor::MoveAnchor);
                lrcshowedit->setTextCursor(textCursor);
                if(!textCursor.hasSelection())//如果没有选中单前行
                    textCursor.select(QTextCursor::BlockUnderCursor);
                QTextCharFormat format;

                format.setFont(QFont("微软雅黑", 12, 57));
                format.setForeground(QBrush(QColor(250,0,0)));

                textCursor.mergeCharFormat(format);

               //////////////滚动
                textCursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,12);
                lrcshowedit->setTextCursor(textCursor);
               ///////////////////
                prviouslrc=nowlrc;
            }
            else
            {
                later = value;
                break;
            }
        }
        if (later == 0)
            later = total_time_value;

        // 获取当前时间所对应的歌词内容
        QString current_lrc = lrc_map.value(previous);

        // 如果是新的一行歌词，那么重新开始显示歌词遮罩
        if(current_lrc != lrc->label->text())
        {
            lrc->label->setText(current_lrc);
            qint64 interval_time = later - previous;
            lrc->start_lrc_mask(interval_time);
        }
    }
}

void MyMainDlg::durationChanged(qint64 duration)//作全局变量保存总时间长度然后加到lable
{
    ui->horizontalSlider->setRange(0, duration);
    QTime total_time(0, (duration/60000)%60, (duration/1000)%60);
    QString format = "mm:ss";
    total_time.toString(format);
    totaldisplay=total_time.toString(format);
}
void MyMainDlg::setPosition(int position)//slider的位置改变就设置
{
     player->setPosition(position);
}

void MyMainDlg::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
       {
          //进行界面退出，重写Esc键，否则重写reject()方法
         case Qt::Key_Escape:
         case Qt::Key_Return:
        return ;

        default:
           QDialog::keyPressEvent(event);
       }
}

MyMainDlg::~MyMainDlg()
{
    timer->destroyed();
    timer2->destroyed();
    delete ui;
}
void MyMainDlg::timerEvent2()
{
    //////////////////////////////////设置音量图标
    if(!player->isAudioAvailable())//不能获取音乐
    {
       ui->horizontalSlider->setMaximum(0);
    }
  ////////////////////////////////////////////////////////////
    if( mymaintable->rowCount()==0)//提示信息
    {
        addtips->show();
    }
    else
    {
       addtips->hide();
    }
}

void MyMainDlg::timerEvent()//歌曲数
{
    //////////////////////////////检查歌曲数目
    int songcount= mymaintable->rowCount();
    songcount+=mynetmaintable->rowCount();
    ui->label_songscount->setText("歌曲数:"+QString::number(songcount));
    ////////////////////////////////////////////////////
}
void MyMainDlg::mousePressEvent(QMouseEvent *event)
{
      if (event->button() == Qt::LeftButton)
     {
       m_WindowPos = this->pos();
       m_MousePos = event->globalPos();
       this->m_MousePressed = true;

       box->hide();
     }

}
void MyMainDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (m_MousePressed)
        {
           this->move(m_WindowPos +(event->globalPos()-m_MousePos));

        }
}
void MyMainDlg::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        this->m_MousePressed = false;
    }
}

void MyMainDlg::slot_addFile()
{
    static QString  initialName ="F:/MP3s764东西/MUSIC";
    QStringList files=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr("*.mp3"));
    if(files.isEmpty())
        return;
                int i=0;
                while(i<files.count())
                {
                    QString path=QDir::toNativeSeparators(files.at(i));
                    if(!path.isEmpty())
                    {
                        //playList->addMedia(QMediaContent(QUrl::fromLocalFile(path)));
                        mymaintable->plist->addMedia(QMediaContent(QUrl::fromLocalFile(path)));
                    }
                  QFileInfo info(files[i]);
                  QString m_name=info.completeBaseName();
                  QString songname;
                  QString singer;
                  if(m_name.contains("-"))//如果遍历的时候包含了"-"这个字符
                  {
                    QStringList list=m_name.split("-");
                    songname=list.at(1);
                    singer=list.at(0);
                  }
                  else
                  {
                      songname=m_name;
                      singer="";
                  }
                  int rowcount= mymaintable->rowCount();
                   mymaintable->insertRow(rowcount);
                   mymaintable->setItem(rowcount,0,new QTableWidgetItem(songname));
                   mymaintable->setItem(rowcount, 1, new QTableWidgetItem(singer));
                   mymaintable->item(rowcount,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                  i++;
                }

////////////////////////////////////////////////////////////////////////////////////// 跳回播放列表
     ui->listWidget_side->setCurrentRow(1);
}

void MyMainDlg::on_pushButton_backward_clicked()
{

    if(player->isAudioAvailable()==true)//没有音乐输入就没法按按钮
      {
        ///////////////////////改变playpause图片
        if(nowplaylist==1)
        {
        mymaintable->mysetprevious();
        player->setMedia(mymaintable->myCurrentMedia());
        }
        else
        {
            mynetmaintable->mysetprevious();
            player->setMedia(mynetmaintable->myCurrentMedia());
        }
        player->play();
        ui->pushButton_playpause->setToolTip("暂停");
    }
}

void MyMainDlg::on_pushButton_playpause_clicked()
{
    ///////////////////////////////设置play和pause的按钮图片状态
    if(player->state()==QMediaPlayer::PlayingState)
    {
    player->pause();

    }
    else
    {
    if(player->isAudioAvailable()==true)//没有音乐输入就没法按按钮
    {
    player->play();

    }
    }
    //////////////////////////////////////////
}

void MyMainDlg::on_pushButton_next_clicked()//出现bug
{
    if(player->isAudioAvailable()==true)//没有音乐输入就没法按按钮
      {
        ///////////////////////改变playpause图片
        if(nowplaylist==1)
        {
        mymaintable->mysetnext();
        player->setMedia(mymaintable->myCurrentMedia());
        }
        else
        {
            mynetmaintable->mysetnext();
            player->setMedia(mynetmaintable->myCurrentMedia());
        }
        player->play();
       ui->pushButton_playpause->setToolTip("暂停");
    }
}
void MyMainDlg::on_pushButton_vol_clicked()//静音
{

    if(changevol==true)
    {
    vol= player->volume();
    QString vol_shut_style="QPushButton{background:transparent;}"
                            "QPushButton{border-image: url(:image/volume_shut.png);}";
    ui->pushButton_vol->setStyleSheet(vol_shut_style);
    ui->horizontalSlider_vol->setValue(0);
    }
    else
    {
    QString vol_style="QPushButton{background:transparent;}"
                       "QPushButton{border-image: url(:image/volume.png);}";
    ui->pushButton_vol->setStyleSheet(vol_style);
    player->setVolume(vol);
    ui->horizontalSlider_vol->setValue(vol);
    }
    changevol=!changevol;
}
void MyMainDlg::on_pushButton_skinbox_clicked()
{
    if(box->isHidden())
    {
     box->show();
     box->setGeometry(this->geometry().x()+8,this->geometry().y()+23,250,285);
    }
     else
     {
         box->hide();
     }

}
void MyMainDlg::mytabledoubleclick(QTableWidgetItem *item)
{
    nowplaylist=1;//用于区分正在播放哪个列表
    mymaintable->mysetCurrentMedia(item->row());
    player->setMedia(mymaintable->myCurrentMedia());
    player->play();
}

void MyMainDlg::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        lrc->show();
        checkbox=1;
    }
    else
    {
        lrc->hide();
        checkbox=0;
    }
}

void MyMainDlg::on_pushButton_search_clicked()
{

    if(ui->widget_search->isHidden())
    {
        ui->widget_search->show();
        ui->listWidget_side->setCurrentRow(1);
    }
    else
    {
        ui->widget_search->hide();
        ui->lineEdit_search->clear();
        ui->listWidget_side->setCurrentRow(1);
    }
}

void MyMainDlg::on_pushButton_searchclose_clicked()
{
     ui->lineEdit_search->setText("");
     QTableWidgetItem *item= mymaintable->item(mymaintable->nowindex,0);
      mymaintable->setCurrentItem(item);
      mymaintable->scrollToItem(item);
     ui->widget_search->hide();
}

void MyMainDlg::on_listWidget_side_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)//当前的itwm改变
{
    if(current==Q_NULLPTR)
        return;
       if(previous!=Q_NULLPTR)
       {

           previous->setBackgroundColor(Qt::transparent);
           previous->setTextColor(Qt::white);
       }
       current->setBackgroundColor(QColor(255, 255, 255,100));
       current->setTextColor(Qt::black);
}
void MyMainDlg::on_listWidget_side_currentRowChanged(int currentRow)//用于防止虚线
{
    if(currentRow==3)
    {
       ledit->setFocus();
       QPropertyAnimation *animal1=new QPropertyAnimation(netseawidget,"geometry");
       animal1->setStartValue(QRect(250,132,194,25));
       animal1->setEndValue(QRect(55,132,194,25));
       animal1->setDuration(500);
       animal1->start();
       netseawidget->show();
       netseawidget->raise();

    }
    else if(currentRow==0)//如果在歌词界面
    {
        netseawidget->hide();
        ui->label_musicicon->setFocus();
    }
    else
    {
        netseawidget->hide();
         ui->label_musicicon->setFocus();
    }

}
void MyMainDlg::on_pushButton_exit_clicked()//退出
{
    box->hide();
    this->close();
}

void MyMainDlg::on_pushButton_mini_clicked()//最小化
{
    box->hide();
    this->setWindowState(Qt::WindowMinimized);
}

void MyMainDlg::on_pushButton_up_clicked()
{
    int index = mymaintable->currentRow();
            if (index >= 1)
            {
                mymaintable->myitemup(index);
                mymaintable->changeRowItem(index,index-1);
            }
}

void MyMainDlg::on_pushButton_down_clicked()
{
    int index = mymaintable->currentRow();
           int count = mymaintable->plist->mediaCount();
           if (index < (count-1))
           {
               mymaintable->myitemdown(index);
               mymaintable->changeRowItem(index,index+1);
           }
}
void MyMainDlg::on_pushButton_webplayer_clicked()
{
    Widget* vp = new Widget;
    vp->setWindowFlags(Qt::Window);
    vp->show();
}

void MyMainDlg::on_pushButton_videoplayer_clicked()
{
    VideoPlayer * vp = new VideoPlayer;
    vp->setWindowFlags(Qt::Window);
    vp->show();
}

void MyMainDlg::on_pushButton_fmradio_clicked()
{
    FMRadioWindow * window = new FMRadioWindow;
    window->setWindowFlags(Qt::Window);
    window->show();
}

void MyMainDlg::on_pushButton_minesweeping_clicked()
{
    MyUI * window = new MyUI;
    window->setWindowFlags(Qt::Window);
    window->show();
}
