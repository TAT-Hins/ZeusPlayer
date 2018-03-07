#include "qshowlrc.h"
#include "ui_qshowlrc.h"

QShowLrc::QShowLrc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QShowLrc)
{
    ui->setupUi(this);
    initWinAttribute();
    initWinInterface();
    initTextEdit();
}

QShowLrc::~QShowLrc()
{
    delete ui;
}

void QShowLrc::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void QShowLrc::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void QShowLrc::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}

void QShowLrc::initWinAttribute()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(QSize(width(), height()));
}

void QShowLrc::initWinInterface()
{
    QPixmap pixmap = QPixmap(":/share/2.png").scaled(ui->textEdit->size());
    QPalette palette(ui->textEdit->palette());
    palette.setBrush(QPalette::Base, QBrush(pixmap));
    palette.setColor(QPalette::Text, QColor(255, 255, 255));
    ui->textEdit->setPalette(palette);

    ui->pb_close->setIconSize(QSize(28, 28));
    ui->pb_close->setIcon(QIcon(":/share/close_hover.png"));
}

void QShowLrc::initTextEdit()
{
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPixmap pixmap = QPixmap(":/share/2.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

void QShowLrc::setLrc(QString lrc)
{
    lrc_map.clear();
    ui->textEdit->clear();
    if(!lrc.contains("\n"))
    {
        ui->textEdit->setText(lrc);
        ui->textEdit->setAlignment(Qt::AlignCenter);
        return;
    }
    regExgLrc(lrc);
    showLrcOnText();
}

void QShowLrc::regExgLrc(QString lrc)
{
    QStringList lines = lrc.split("\n");
    QRegExp regExp("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString oneLine, lines)
    {
        QString temp = oneLine;     //取出一行
        temp.replace(regExp, "");   //替换掉时间
        int pos = regExp.indexIn(oneLine, 0);
        while(pos > -1)
        {
            QString cap = regExp.cap(0);
            QRegExp rx;
            rx.setPattern("\\d{2}(?=:)");
            rx.indexIn(cap);
            int minute = rx.cap(0).toInt();
            rx.setPattern("\\d{2}(?=\\.)");
            rx.indexIn(cap);
            int second = rx.cap(0).toInt();
            rx.setPattern("\\d{2}(?=\\])");
            rx.indexIn(cap);
            int millisecond = rx.cap(0).toInt();
            qint64 totalTime = minute * 60000
                             + second * 1000
                             + millisecond * 10;
            // 插入到lrc_map中
            lrc_map.insert(totalTime, temp);
            pos += regExp.matchedLength();
            pos = regExp.indexIn(oneLine, pos);
        }
    }
}

void QShowLrc::showLrcOnText()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
    foreach(QString oneLine, lrc_map.values())
    {
        ui->textEdit->append(oneLine);
    }
    ui->textEdit->scrollToAnchor("\n");
}

void QShowLrc::on_pb_close_clicked()
{
    hide();
}
