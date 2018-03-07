#include "widget.h"
#include "ui_widget.h"
#include "qaudio.h"
#include <QtWinExtras>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget), m_songlink(""),
    m_onPlaySongName(""), m_onPlayHash(""), m_onDownloadSongName(""),
    m_isSingleCircle(false), m_nextBtnPressed(false),
    mouse_press(false), m_file(0), player(0), volumeButton(0), taskbarButton(0), taskbarProgress(0),
    managerGetSongInfo(0), managerPlay(0), managerDownload(0),
    managerStartDownload(0)
{
    ui->setupUi(this);    //初始化Ui界面
    initMediaPlayer();    //初始化媒体播放器
    initWinAttribute();   //初始化窗口属性
    initPlayerInterface();//初始化播放器界面
    initTaskbar();        //初始化任务栏图标
    initNetwork();        //初始化网络接口
    m_listResult.clear(); //清空搜索列表
    m_listPlay.clear();   //清空播放列表
}

Widget::~Widget()
{
    delete ui;
    delete player;
    //delete showLrc;
    delete volumeButton;
    delete taskbarButton;
    delete managerPlay;
    delete managerGetSongInfo;
    delete managerDownload;
    delete managerStartDownload;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
        //showLrc->move(QPoint(x()+width(), y()));
    }
}

void Widget::initWinAttribute()
{
    setWindowTitle("webPlayer");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void Widget::initMediaPlayer()
{
    player  = new QMediaPlayer(this);
    connect(player, SIGNAL(positionChanged(qint64)),
            this, SLOT(updatePosition(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)),
            this, SLOT(updateDuration(qint64)));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(updateState(QMediaPlayer::State)));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(updateTaskbar()));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(slot_play_next()));
}

void Widget::updatePosition(qint64 position)
{
    ui->slider->setValue(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->lb_duration->setText(duration.toString(tr("mm:ss")));
}

void Widget::updateDuration(qint64 duration)
{
    ui->slider->setRange(0, duration);
    ui->slider->setEnabled(duration > 0);
    ui->slider->setPageStep(duration / 10);
}

void Widget::updateState(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
    {
        ui->pb_play->setToolTip(tr("Pause"));
        ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        ui->pb_play->setToolTip(tr("Play"));
        ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void Widget::updateTaskbar()
{
    switch(player->state())
    {
    case QMediaPlayer::PlayingState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        taskbarProgress->show();
        taskbarProgress->resume();
        break;
    case QMediaPlayer::PausedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPause));
        taskbarProgress->show();
        taskbarProgress->pause();
        break;
    case QMediaPlayer::StoppedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaStop));
        taskbarProgress->hide();
        break;
    }
}

void Widget::slot_play_next()
{
    if((player->mediaStatus() == QMediaPlayer::EndOfMedia) || m_nextBtnPressed)
    {
        if(m_isSingleCircle)
        {
            player->setPosition(0);
            player->play();
            return;
        }
        int sumRow = m_listPlay.count();
        for(int i=0; i<sumRow-1; ++i)
        {
            QString songName = m_listPlay.at(i).songName;
            if(m_onPlaySongName == songName)
            {
                if(sumRow > i+1)
                {
                    emit slot_select_to_play(i+1, 0);
                    m_nextBtnPressed = false;
                }
                break;
            }
        }
    }
}

void Widget::initPlayerInterface()
{
    //初始化音量图标
    initVolumnButton();
    //设置背景图片
    QPixmap pixmap = QPixmap(":/image/background.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    //设置初始播放标签为Easy Player的标题
    ui->lb_onPlay->setText(tr("webPlayer0"));
    //设置按钮图标和大小
    ui->pb_minimum->setIconSize(QSize(28, 28));
    ui->pb_close->setIconSize(QSize(28, 28));
    ui->pb_minimum->setIcon(QIcon(":/share/min_pressed.png"));
    ui->pb_close  ->setIcon(QIcon(":/share/close_hover.png"));
    ui->pb_next   ->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pb_replay ->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pb_play   ->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pb_song   ->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    //列表
    initTableInfo(ui->tb_find);
    initTableInfo(ui->tb_play);
    connect(ui->tb_find, SIGNAL(cellClicked(int,int)),
            this, SLOT(slot_append_to_playlist(int, int)));
    connect(ui->tb_play, SIGNAL(cellClicked(int,int)),
            this, SLOT(slot_append_to_downloadList(int, int)));
    connect(ui->tb_play, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(slot_select_to_play(int, int)));
}

void Widget::initVolumnButton()
{
    volumeButton = new QVolumeButton(ui->lb_volumn);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(player->volume());
    connect(volumeButton, SIGNAL(volumeChanged(int)), player, SLOT(setVolume(int)));
}

void Widget::initTableInfo(QTableWidget *widget)
{
    widget->setColumnCount(2);
    widget->horizontalHeader()->setHidden(true);
    widget->verticalHeader()->setHidden(true);
    widget->setColumnWidth(0, 192);
    widget->setColumnWidth(1, 30);
    widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget->setStyleSheet("selection-background-color:gray");
    widget->setSelectionMode(QAbstractItemView::SingleSelection);
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    widget->setShowGrid(false);
    widget->setAlternatingRowColors(true);
    widget->setFocusPolicy(Qt::NoFocus);
}

void Widget::slot_append_to_playlist(int row, int col)
{
    if(col == Append)
    {
        stPlayList.songName = m_listResult.at(row).songName;
        stPlayList.hash = m_listResult.at(row).hash;
        m_listPlay.append(stPlayList);

        QTableWidgetItem *songItem = new QTableWidgetItem(stPlayList.songName);
        QTableWidgetItem *appendItem = new QTableWidgetItem
                (QIcon(style()->standardIcon(QStyle::SP_ArrowDown)), NULL);
        songItem->setFlags(Qt::ItemIsEnabled);
        appendItem->setFlags(Qt::ItemIsEnabled);
        int playRow = ui->tb_play->rowCount();
        ui->tb_play->insertRow(playRow);
        ui->tb_play->setItem(playRow, FileName, songItem);
        ui->tb_play->setItem(playRow, Append, appendItem);
    }
}

void Widget::slot_append_to_downloadList(int row, int col)
{
    if(col == 1)
    {
        m_onDownloadSongName = m_listPlay.at(row).songName;
        if(!isSongExist(m_onDownloadSongName))
        {
            QString hash = m_listPlay.at(row).hash;
            requestDownloadSong(hash);
        }
    }
}

void Widget::slot_select_to_play(int row, int col)
{
    if(player)
    {
        player->pause();
    }
    if(col == 0)
    {
        QString hash = m_listPlay.at(row).hash;
        m_onPlaySongName = m_listPlay.at(row).songName;
        //获取歌曲链接
        QNetworkRequest request;
        request.setUrl(QUrl("http://m.kugou.com/app/i/getSongInfo.php?"));
        QByteArray byteArray;
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/x-www-form-urlencoded");
        byteArray.append("hash=" + hash);
        byteArray.append("&cmd=playInfo");
        managerPlay->post(request, byteArray);
    }
}

void Widget::initTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());
    taskbarProgress = taskbarButton->progress();
    connect(ui->slider, SIGNAL(valueChanged(int)),
            taskbarProgress, SLOT(setValue(int)));
    connect(ui->slider, SIGNAL(rangeChanged(int,int)),
            taskbarProgress, SLOT(setRange(int,int)));
}

void Widget::initNetwork()
{
    managerGetSongInfo      = new QNetworkAccessManager(this);
    managerPlay             = new QNetworkAccessManager(this);
    managerDownload         = new QNetworkAccessManager(this);
    managerStartDownload    = new QNetworkAccessManager(this);
   // managerGetSongLrc       = new QNetworkAccessManager(this);
    //managerDownloadSongLrc  = new QNetworkAccessManager(this);

    connect(managerGetSongInfo, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_get_song_info(QNetworkReply*)));
    connect(managerPlay, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_play_song(QNetworkReply*)));
    connect(managerDownload, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_download_song(QNetworkReply*)));
    connect(managerStartDownload, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_start_download(QNetworkReply*)));
}

void Widget::on_le_find_returnPressed()
{
    //清空上一个搜索列表
    ui->tb_find->clear();
    int row = ui->tb_find->rowCount();
    for(int i=row; i>=0; --i)
    {
        ui->tb_find->removeRow(i);
    }
    m_listResult.clear();
    //获取输入的文本
    QString strInput = ui->le_find->text();
    //将文本转换为utf-8编码
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QByteArray byteArrayCodec = codec->fromUnicode(strInput);
    QByteArray byteArrayPercentEncoded = byteArrayCodec.toPercentEncoding();
    QString strSongName = QString(byteArrayPercentEncoded);
    //获取歌曲信息
    QNetworkRequest request;
    QString strUrl =
            QString("http://mobilecdn.kugou.com/api/v3/search/song?keyword=%1")
            .arg(strSongName);
    qDebug() << strUrl;
    request.setUrl(QUrl(strUrl));
    managerGetSongInfo->get(request);    
}

void Widget::slot_get_song_info(QNetworkReply* reply)
{
    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);                //转化为字符串
        parseSongInfo(result);                //解析Json数据
        addItemsToResultList();               //添加结果到搜索列表
    }
    reply->deleteLater();
}

void Widget::addItemsToResultList()
{
    if(!m_listResult.isEmpty())
    {
        const int tableRow = m_listResult.count();
        ui->tb_find->setRowCount(tableRow);
        for(int row=0; row<tableRow; row++)
        {
            findResult info = m_listResult.at(row);
            QTableWidgetItem *songItem = new QTableWidgetItem(info.songName);
            QTableWidgetItem *appendItem = new QTableWidgetItem
                    (QIcon(style()->standardIcon(QStyle::SP_ArrowRight)), NULL);
            songItem->setFlags(Qt::ItemIsEnabled);
            appendItem->setFlags(Qt::ItemIsEnabled);
            ui->tb_find->setItem(row, FileName, songItem);
            ui->tb_find->setItem(row, Append, appendItem);
        }
    }
}

void Widget::parseSongInfo(QString json)
{
    //从字符串数据转换为Json数据
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment =
            QJsonDocument::fromJson(byte_array.append(json), &json_error);
    //如果没有错误
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject object = parse_doucment.object();
            if(object.contains("data"))
            {
                QJsonValue value_data = object.take("data");
                if(value_data.isObject())
                {
                    QJsonObject object_data = value_data.toObject();
                    if(object_data.contains("info"))
                    {
                        QJsonValue value_info = object_data.take("info");
                        if(value_info.isArray())
                        {
                            QJsonArray array_info = value_info.toArray();
                            const int size = array_info.size();
                            for(int i=0; i<size; ++i)
                            {
                                QJsonValue value_first = array_info.at(i);
                                if(value_first.isObject())
                                {
                                    QString songname;
                                    QString hash;
                                    QJsonObject object_first = value_first.toObject();
                                    if(object_first.contains("filename"))
                                    {
                                        QJsonValue value_filename = object_first.take("filename");
                                        songname = value_filename.toString();
                                    }
                                    if(object_first.contains("hash"))
                                    {
                                        QJsonValue value_hash = object_first.take("hash");
                                        hash = value_hash.toString();
                                    }
                                    stResultList.songName = songname;
                                    stResultList.hash = hash;
                                    m_listResult.append(stResultList);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << "error ... ...";
    }
}

void Widget::on_pb_play_clicked()
{    
    if(player->state() == QMediaPlayer::PlayingState)
    {
        ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        player->pause();
    }
    else
    {
        ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        player->play();
    }
}

void Widget::slot_play_song(QNetworkReply* reply)
{
    //无错误返回
    ui->lb_onPlay->setText(tr("正在获取歌曲资源，请稍后... ..."));
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);                //转化为字符串
        parseSongLink(result);                //解析Json数据        
        if(!m_songlink.isEmpty())
        {
            player->setMedia(QUrl(m_songlink));
            ui->lb_onPlay->setText(m_onPlaySongName);
            player->play();
            //getOnPlaySongLyric();
        }
    }
    reply->deleteLater();
}

/*void Widget::getOnPlaySongLyric()
{
    QNetworkRequest request;
    QString strUrl;
    if(m_onPlaySongName.isEmpty())
    {
        return;
    }
    else
    {
        QStringList listSplit = m_onPlaySongName.split("- ");
        if(listSplit.isEmpty())
        {
            strUrl = QString("http://geci.me/api/lyric/%1")
                    .arg(listSplit[1]);
        }
        else
        {
            strUrl = QString("http://geci.me/api/lyric/%1/%2")
                    .arg(listSplit[1])
                    .arg(listSplit[0]);
        }
    }
    request.setUrl(QUrl(strUrl));
    managerGetSongLrc->get(request);
}*/

void Widget::parseSongLink(QString json)
{
    QScriptEngine engine;
    QScriptValue sv = engine.evaluate("value=" + json);
    if(sv.property("status").toInt32() == 1)
    {
        m_songlink = sv.property("url").toString();
    }
}

bool Widget::isSongExist(QString songname)
{
    QString filename = songname+".m4a";
    if(QFile::exists(filename))
    {
        QMessageBox msg;
        msg.setWindowTitle("下载歌曲");
        msg.setIcon(QMessageBox::Warning);
        msg.setText(tr("当前路径下已存在歌曲：%1，是否覆盖？").arg(filename));
        msg.addButton(tr("覆盖"), QMessageBox::YesRole);
        msg.addButton(tr("取消"), QMessageBox::NoRole);
        msg.setDefaultButton(QMessageBox::No);
        if(msg.exec() == 1)
        {
            qDebug() << "取消下载.";
            return true;
        }
        QFile::remove(filename);
        qDebug() << "歌曲已进入下载通道.";
    }
    return false;
}

void Widget::on_pb_song_clicked()
{
    m_onDownloadSongName = m_onPlaySongName;
    if(isSongExist(m_onDownloadSongName))
    {
        return;
    }
    const int onPlayCount = m_listPlay.count();
    for(int i=0; i<onPlayCount; ++i)
    {
        QString songName = m_listPlay.at(i).songName;
        if(songName == m_onDownloadSongName)
        {
            m_onPlayHash = m_listPlay.at(i).hash;
            requestDownloadSong(m_onPlayHash);
            break;
        }
    }
}

void Widget::requestDownloadSong(QString hash)
{
    QNetworkRequest request;
    QString strUrl =
            QString("http://m.kugou.com/app/i/getSongInfo.php?hash=%1&cmd=playInfo")
            .arg(hash);
    request.setUrl(QUrl(strUrl));
    managerDownload->get(request);
}

void Widget::slot_download_song(QNetworkReply *reply)
{
    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);                //转化为字符串
        parseSongLink(result);                //解析Json数据
        //如果歌曲链接不为空，则播放音乐
        if(!m_songlink.isEmpty())
        {
            downloadSong(m_songlink);
        }
    }
    reply->deleteLater();
}

void Widget::downloadSong(QString link)
{
    QNetworkRequest request;
    request.setUrl(QUrl(link));
    managerStartDownload->get(request);
}

void Widget::slot_start_download(QNetworkReply* reply)
{
    QByteArray byteArray = reply->readAll();

    if(!m_onDownloadSongName.isEmpty())
    {
        QString filename = m_onDownloadSongName+".m4a";
        m_file = new QFile(filename);
        if (!m_file->open(QIODevice::WriteOnly))
        {
            QMessageBox msg;
            msg.setWindowTitle(tr("歌曲下载失败"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText(tr("无法写入文件 %1: %2.")
                        .arg(filename)
                        .arg(m_file->errorString()));
            msg.addButton(QString("确认"), QMessageBox::YesRole);
            msg.setDefaultButton(QMessageBox::Yes);
            msg.exec();
            delete m_file;
            m_file = NULL;
            return;
        }

        m_file->write(byteArray);
        m_file->close();
        m_file->deleteLater();
        m_file = NULL;
        QMessageBox msg;
        msg.setWindowTitle(tr("歌曲下载完成"));
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("歌曲：%1 下载完成.").arg(filename));
        msg.addButton(QString("好的"), QMessageBox::YesRole);
        msg.setDefaultButton(QMessageBox::Yes);
        msg.exec();
    }
}

void Widget::on_pb_next_clicked()
{
    m_nextBtnPressed = true;
    emit slot_play_next();
}

void Widget::on_pb_replay_clicked()
{
    if(m_isSingleCircle)
    {
        m_isSingleCircle = false;
        qDebug() << "已取消单曲循环";
    }
    else
    {
        m_isSingleCircle = true;
        qDebug() << "已设置单曲循环";
    }
}

void Widget::on_slider_valueChanged(int value)
{
    if(qAbs(player->position() - value) > 99)
    {
        player->setPosition(value);
    }
}

void Widget::on_pb_minimum_clicked()
{
    showMinimized();
}

void Widget::on_pb_close_clicked()
{
    close();
}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox msg;
    msg.setWindowTitle(tr("退出webPlayer"));
    msg.setIcon(QMessageBox::Warning);
    msg.setText("你真的要离开webPlayer吗?");
    msg.addButton(QString("狠心离开"), QMessageBox::YesRole);
    msg.addButton(QString("再等一下"), QMessageBox::NoRole);
    msg.setDefaultButton(QMessageBox::Yes);
    if(msg.exec() == 0)
    {
        event->accept();
        close();
        //showLrc->close();
        return;
    }
    event->ignore();
}
