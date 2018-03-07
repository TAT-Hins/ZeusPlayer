#include "mylrc.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QTextCodec>
#include<QPushButton>
MyLrc::MyLrc(QWidget *parent) :
    QDialog(parent)
{
    label=new QLabel(this);

   setStyleSheet("QLabel::hover{background: rgb(100,100,100,100);border: 1px solid gray;}"
                 "QPushButton{background: rgb(100,100,100,100);border: 1px solid gray;}"
                 "QLabel::pressed{background: rgb(100,100,100,100);border: 1px solid gray;}");
   setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint|Qt::Tool|Qt::X11BypassWindowManagerHint);
   this->setAttribute(Qt::WA_TranslucentBackground, true);

    this->setGeometry(200,10,65,800);
    labelmask=new QLabel(this);
    labelmask->setMaximumSize(800, 45);
    labelmask->setMinimumSize(800, 45);
    labelmask->setGeometry(0,20,800,45);

    label->hide();

    this->installEventFilter(this);
    label->installEventFilter(this);

    label->setText(tr("zeusplayer"));
    label->setAlignment(Qt::AlignHCenter);
    // 固定显示区域大小
    label->setMaximumSize(800, 45);
    label->setMinimumSize(800, 45);
    this->setMaximumSize(800, 65);
    this->setMinimumSize(800, 65);
    //歌词的线性渐变填充
    linear_gradient.setStart(0, 10);//填充的起点坐标
    linear_gradient.setFinalStop(0, 40);//填充的终点坐标
    //第一个参数终点坐标，相对于我们上面的区域而言，按照比例进行计算
    linear_gradient.setColorAt(0.1, QColor(14, 179, 255));
    linear_gradient.setColorAt(0.5, QColor(114, 232, 255));
    linear_gradient.setColorAt(0.9, QColor(14, 179, 255));

    // 遮罩的线性渐变填充
    mask_linear_gradient.setStart(0, 10);
    mask_linear_gradient.setFinalStop(0, 40);
    mask_linear_gradient.setColorAt(0.1, QColor(222, 54, 4));
    mask_linear_gradient.setColorAt(0.5, QColor(255, 72, 16));
    mask_linear_gradient.setColorAt(0.9, QColor(222, 54, 4));

    // 设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);

    // 设置定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    lrc_mask_width = 0;
    lrc_mask_width_interval = 0;

    // 设置网络连接
    network_manager = new QNetworkAccessManager();
    network_request = new QNetworkRequest();
    connect(network_manager, &QNetworkAccessManager::finished, this, &MyLrc::replyFinished);

}
#include<QToolTip>

bool MyLrc::eventFilter(QObject *obj, QEvent *event)
{

    if(obj==label)
    {
        if(event->type()==QEvent::MouseMove)//随时变化slider的tooltip
        {
            QToolTip::showText(QCursor::pos(),QString::number(12));//通过vol的slidermove得到这个值

        }

    }

     return QObject::eventFilter(obj, event);
}
void MyLrc::setMusicInfo(QString name, QString filepath) {
    m_strName = name;
    m_strPath = filepath;
    qDebug() << m_strPath << m_strPath;
}

// 开启遮罩，需要指定当前歌词开始与结束之间的时间间隔
void MyLrc::start_lrc_mask(qint64 intervaltime)
{
    // 这里设置每隔30毫秒更新一次遮罩的宽度，因为如果更新太频繁
    // 会增加CPU占用率，而如果时间间隔太大，则动画效果就不流畅了
    qreal count = intervaltime / 30;
    // 获取遮罩每次需要增加的宽度，这里的800是部件的固定宽度
    lrc_mask_width_interval = 800 / count;
    lrc_mask_width = 0;
    timer->start(30);
}

void MyLrc::stop_lrc_mask()
{
    timer->stop();
    lrc_mask_width = 0;
    update();
}


void MyLrc::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(font);

    // 先绘制底层文字，作为阴影，这样会使显示效果更加清晰，且更有质感
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(21, 21, 800, 60, Qt::AlignLeft, label->text());//左对齐

    // 再在上面绘制渐变文字
    painter.setPen(QPen(linear_gradient, 0));
    painter.drawText(20, 20, 800, 60, Qt::AlignLeft, label->text());

    // 设置歌词遮罩
    painter.setPen(QPen(mask_linear_gradient, 0));
    painter.drawText(20, 20, lrc_mask_width, 60, Qt::AlignLeft, label->text());
    label->setAlignment(Qt::AlignHCenter);

}

//左击操作

void MyLrc::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        offset = event->globalPos() - frameGeometry().topLeft();

}


void MyLrc::mouseMoveEvent(QMouseEvent *event)
{
    //event->buttons()返回鼠标点击的类型，分为左击，中击，右击
    //这里用与操作表示是左击
    if (event->buttons() & Qt::LeftButton) {
        setCursor(Qt::DragMoveCursor);
        //实现移动操作
        move(event->globalPos() - offset);

       }
}

//右击事件
void MyLrc::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu=new QMenu;
    menu->setContentsMargins(1,1,1,4);//样式
    QAction *hideaction=new QAction("关闭",this);
    menu->addAction(hideaction);
    actionUpdateLrc = menu->addAction("在线更新歌词", this, SLOT(downloadLrc()));
    connect(hideaction,SIGNAL(triggered(bool)),this,SLOT(hide()));
    connect(hideaction,SIGNAL(triggered(bool)),this,SIGNAL(changeselect(bool)));
    menu->exec(event->globalPos());//globalPos()为当前鼠标的位置坐标
}


void MyLrc::timeout()
{
    //每隔一段固定的时间笼罩的长度就增加一点
    lrc_mask_width += lrc_mask_width_interval;
    update();//更新widget，但是并不立即重绘，而是安排一个Paint事件，当返回主循环时由系统来重绘
}

//
void MyLrc::downloadLrc() {

    QString strUrl = QString("http://ting.baidu.com/data2/lrc/%1/%2.lrc")
            .arg("小苹果").arg("小苹果");
//    network_request->setUrl(QUrl("http://ting.baidu.com/data2/lrc/15265710/15265710.lrc"));
    qDebug() << strUrl;
    network_request->setUrl(QUrl(strUrl));
    network_manager->get(*network_request);
}

void MyLrc::replyFinished(QNetworkReply *reply){
    QFile file(m_strPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error!" << m_strPath << m_strName;
        return;
    }
    QByteArray ba = reply->readAll();
    QTextCodec *gbkCodec = QTextCodec::codecForName("GBK");
    QString all_text = gbkCodec->toUnicode(ba);
    qDebug() << all_text;
    file.write(ba);
    file.close();
    file.flush();
}
