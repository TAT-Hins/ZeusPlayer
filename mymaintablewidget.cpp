#include "mymaintablewidget.h"
#include<QModelIndex>
#include<QHeaderView>
#include<QDebug>
#include<QMouseEvent>
#include<QEvent>
#include<QGraphicsOpacityEffect>
#include<QScrollBar>
#include<QTime>
#include<QObject>

mymaintablewidget::mymaintablewidget(QWidget *parent): QTableWidget(parent)
{

       this->setMouseTracking(true);
       kgmousemove=true;
       plist=new QMediaPlaylist;
       previousitem=-1;
       setFrameShadow(QFrame::Plain);//设置平的样式
       setFrameShape(QFrame::NoFrame);//设置无边样式
       setFocusPolicy(Qt::NoFocus);
       setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
       setShowGrid(false);//隐藏线
       this->horizontalHeader()->setVisible(false);
       this->verticalHeader()->setVisible(false);
       setEditTriggers(QTableWidget::NoEditTriggers);
       setSelectionBehavior (QAbstractItemView::SelectRows);
       setSelectionMode (QAbstractItemView::SingleSelection);
       setAcceptDrops(true);
       setGeometry(55,132,194,444);

       setContextMenuPolicy(Qt::CustomContextMenu);
       this->insertColumn(0);
       this->insertColumn(1);
       this->horizontalHeader()->resizeSection(0,360);
       this->horizontalHeader()->setStretchLastSection(true);

       this->setStyleSheet("QTableWidget{background-color:rgb(255, 255, 255,150);}"
                           "QTableWidget{font-size : 12px;color: rgb(55, 55, 55);}"
                           "QTableWidget{selection-background-color: rgb(25,65,65,150);padding: -1;}"
                           "QTableWidget{selection-color: rgb(255, 255, 255);}");
       QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
       this->verticalScrollBar()->setGraphicsEffect(opacityEffect);
       opacityEffect->setOpacity(0.5);

       QScrollBar *vbar=this->verticalScrollBar();
       vbar->setContextMenuPolicy(Qt::NoContextMenu);//"QScrollBar::handle{}"
       //
       vbar->setStyleSheet("QScrollBar{background:white; width: 10px;margin: 10px 0 10px 0;}"
                           "QScrollBar::handle{background:light gray;border-radius:5px;}"
                           "QScrollBar::handle:hover{background: rgb(55,55,55);}"
                           "QScrollBar::add-line:vertical {background:black; border-image: url(:/image/down.png); height: 10px; subcontrol-position: bottom;subcontrol-origin: margin;}"
                           "QScrollBar::sub-line:vertical {background:black; border-image: url(:/image/top.png);height: 10px;subcontrol-position: top;subcontrol-origin: margin;}"
                           "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:white;}");
       connect(this,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),this,SLOT(currentitemch(QTableWidgetItem*,QTableWidgetItem*)));
       connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(listentered(int,int)));
       mysetPlaybackMode(0);


}
mymaintablewidget::mymaintablewidget(bool kg)
{
    kgmousemove=kg;
    setMouseTracking(true);
    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
    setShowGrid(false);//隐藏线
    verticalHeader()->setVisible(false);//设置不可见
    setEditTriggers(QTableWidget::NoEditTriggers);//不可编辑
    setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    setSelectionMode ( QAbstractItemView::NoSelection);//单选
    horizontalHeader()->setHighlightSections(false);//不能鼠标点击
    setStyleSheet("QTableWidget{background-color:rgb(255, 255, 255,100);}"
                  "QTableWidget{font-size : 12px;color: rgb(65, 65, 65);}"

                  "QTableWidget::item:hover{color: red;}");//background-color:rgb(242, 242, 242);// "QTableWidget{selection-background-color: rgb(233,233,233);}"
    insertColumn(0);
    insertColumn(1);
    insertColumn(2);
    QStringList list;
    list<<" 歌曲"<<" 歌手"<<"操作";
    setHorizontalHeaderLabels(list);
    QHeaderView *header=this->horizontalHeader();//调整大小
    header->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);border: 1px solid #383838;}");//
    header->resizeSection(0,180);
    header->resizeSection(1,180);
    header->setStretchLastSection(true);//延展最一个表头
    header->setSectionResizeMode(QHeaderView::Fixed);//不能更改列宽
    this->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);//第一列表头对齐方式
    this->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);//第2列表头位置方式
}
void mymaintablewidget::listentered(int row, int column)
{
    qDebug()<<row<<column;
}
void mymaintablewidget::currentitemch(QTableWidgetItem*,QTableWidgetItem*)//用于当前选择项为白字黑底
{

}
void mymaintablewidget::mouseMoveEvent(QMouseEvent *)
{
    if(!kgmousemove)//如果开关为false
        return;

    QTableWidgetItem *itemss=this->item(previousitem,0);
    QModelIndex index= this->indexAt(this->mapFromGlobal(QCursor::pos()));
    int nowrow=index.row();
    if(itemss!=Q_NULLPTR)
    {
    this->item(previousitem,0)->setBackgroundColor(Qt::transparent);
    this->item(previousitem,1)->setBackgroundColor(Qt::transparent);
    }
    if(this->itemAt(this->mapFromGlobal(QCursor::pos()))!=NULL&&nowrow!=currentRow())
    {
    this->item(nowrow,0)->setBackgroundColor(QColor(25,65,65,50));
    this->item(nowrow,1)->setBackgroundColor(QColor(25,65,65,50));
    previousitem=nowrow;
    }
}
void mymaintablewidget::leaveEvent(QEvent *)
{
    QTableWidgetItem *itemss=this->item(previousitem,0);
    if(itemss!=Q_NULLPTR)//如果itemss不为空
    {
        this->item(previousitem,0)->setBackgroundColor(Qt::transparent);
        this->item(previousitem,1)->setBackgroundColor(Qt::transparent);
    }
}
QUrl mymaintablewidget::myCurrentMedia()
{
    return plist->media(nowindex).canonicalUrl();
}
void mymaintablewidget::mysetCurrentMedia(int nowsong)
{
     nowindex=nowsong;
}
void mymaintablewidget::mysetPlaybackMode(int mode)//0是列表1是单曲2是随机
{
    nowmode=mode;
}
void mymaintablewidget::mysetnext()
{

    if(nowmode==0)//顺序列表播放到尾巴上 从头再来
    {
        if(nowindex==plist->mediaCount()-1)
        {
            nowindex=0;
            QTableWidgetItem *item= this->item(nowindex,0);
            this->setCurrentItem(item);
            return;
        }
        nowindex+=1;
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
    }
    if(nowmode==1)//单曲循环
    {

        return;
    }
    if(nowmode==2)//随机播放
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%plist->mediaCount();
        nowindex=xxx;
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
    }

}
void mymaintablewidget::mysetprevious()
{
    if(nowmode==0)//顺序列表播放头上再按上一曲， 从头播放第一首
    {
        if(nowindex==0)
        {
            nowindex=0;

            return;
        }

        nowindex-=1;
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
    }
    if(nowmode==1)//单曲循环
    {
        return;
    }
    if(nowmode==2)//随机播放
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%plist->mediaCount();
        nowindex=xxx;
        this->setCurrentCell(nowindex,0);
    }

}
void mymaintablewidget::mydelitem(int index)
{
    if(index<nowindex)
    {
        plist->removeMedia(index);
        nowindex--;//当前播放的歌曲变成null
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
        return;
    }
    if(index==nowindex)
    {
        plist->removeMedia(index);
        nowindex++;
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
        return;
    }
    if(index>nowindex)
    {
        plist->removeMedia(index);
        QTableWidgetItem *item= this->item(nowindex,0);
        this->setCurrentItem(item);
        return;
    }
}

void mymaintablewidget::myitemup(int index){

    //对当前播放歌曲的操作
    if(index == nowindex){
        QMediaContent content = plist->media(index-1);//暂存选定项对应的歌曲
        plist->removeMedia(index-1);//删除选定歌曲
        nowindex-=1;
        plist->insertMedia(index,content);//在原选定项上一项的上方插入原选定歌曲
        //光标跟随
        QTableWidgetItem * ptr = this->item((index-1),0);
        this->setCurrentItem(ptr);
        return;
    }

    else{
        //同上操作
        QMediaContent content = plist->media(index);
        plist->removeMedia(index);
        plist->insertMedia((index-1),content);

        if(index == (nowindex +1)){   //与当前播放歌曲交换后，继续播放原播放歌曲
            nowindex+=1;
        }
        //光标跟随
        QTableWidgetItem * ptr = this->item((index-1),0);
        this->setCurrentItem(ptr);
        return;
    }
}

/*下调操作与上调操作同理
 *index不适用于列表最后一项*/
void mymaintablewidget::myitemdown(int index){

    if(index == nowindex){
        QMediaContent content = plist->media(index+1);
        plist->removeMedia(index+1);
        plist->insertMedia(index,content);
        nowindex+=1;
        QTableWidgetItem * ptr = this->item((index+1),0);
        this->setCurrentItem(ptr);
        return;
    }
    else{
        QMediaContent content = plist->media(index);
        plist->removeMedia(index);
        plist->insertMedia((index+1),content);
        if((index+1) == nowindex){
            nowindex-=1;
        }
        QTableWidgetItem * ptr = this->item((index+1),0);
        this->setCurrentItem(ptr);
        return;
    }
}

void mymaintablewidget::changeRowItem(int row_Up, int row_Down){

    //暂存需要交换的两行内容
    QTableWidgetItem * item11 = this->item(row_Up,0);
    QTableWidgetItem * item12 = this->item(row_Up,1);
    QTableWidgetItem * item21 = this->item(row_Down,0);
    QTableWidgetItem * item22 = this->item(row_Down,1);

    //删除原有内容但保留行
    for (int i=0; i<2; i++){
        this->takeItem(row_Up,i);
        this->takeItem(row_Down,i);
    }

    //两行内容交换存入
    this->setItem(row_Up,0,item21);
    this->setItem(row_Up,1,item22);
    this->setItem(row_Down,0,item11);
    this->setItem(row_Down,1,item12);
}

