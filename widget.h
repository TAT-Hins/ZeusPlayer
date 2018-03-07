#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMediaPlayer>
#include <QScriptEngine>
#include <QScriptValue>
#include <QMessageBox>
#include <QFile>
#include <qvolumnbutton.h>

QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolBar)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolButton)
QT_FORWARD_DECLARE_CLASS(QLineEdit)

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void slot_get_song_info (QNetworkReply*);
    void slot_play_song     (QNetworkReply*);
    void slot_download_song (QNetworkReply*);
    void slot_start_download(QNetworkReply*);
    void slot_select_to_play(int, int);
    void slot_append_to_playlist(int, int);
    void slot_append_to_downloadList(int, int);
    void slot_play_next();    
    void on_le_find_returnPressed();
    void on_pb_play_clicked();
    void on_pb_song_clicked();
    void on_pb_next_clicked();
    void on_pb_replay_clicked();
    void on_slider_valueChanged(int value);
    void updateTaskbar();
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void on_pb_minimum_clicked();
    void on_pb_close_clicked();

private:
    void mousePressEvent  (QMouseEvent *event);
    void mouseMoveEvent   (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void initWinAttribute();
    void initPlayerInterface();
    void initVolumnButton();
    void initLrcInterface();
    void initTaskbar();
    void initMediaPlayer();
    void initNetwork();
    void requestDownloadSong(QString hash);
    void parseSongInfo(QString json);
    void parseSongLink(QString json);
    void playSong     (QString link);
    void downloadSong (QString link);
    void addItemsToResultList();
    //void getOnPlaySongLyric();
    void initTableInfo(QTableWidget *widget);
    bool isSongExist(QString songname);
    void closeEvent   (QCloseEvent *);

    enum
    {
        FileName ,
        Append
    };

    struct findResult
    {
        QString hash;
        QString songName;
    }stResultList;

    struct playList
    {
        QString songName;
        QString hash;
    }stPlayList;

    Ui::Widget *ui;
    QString m_songlink;
    QString m_hash;
    QString m_songname;
    //QString m_lrcLink;
   // QString m_lyric;
    QString m_onPlaySongName;
    QString m_onPlayHash;
    QString m_onDownloadSongName;
    bool m_isSingleCircle;
   // bool m_isLrcShow;
    bool m_nextBtnPressed;
    bool mouse_press;
    QPoint move_point;
    QList<findResult> m_listResult;
    QList<playList>   m_listPlay;
    QFile         *m_file;
    //QFile         *m_fileLrc;
    QMediaPlayer  *player;
    //QShowLrc      *showLrc;
    QVolumeButton *volumeButton;
    QWinTaskbarButton     *taskbarButton;
    QWinTaskbarProgress   *taskbarProgress;
    QNetworkAccessManager *managerGetSongInfo;
    QNetworkAccessManager *managerPlay;
    QNetworkAccessManager *managerDownload;
    QNetworkAccessManager *managerStartDownload;
    //QNetworkAccessManager *managerGetSongLrc;
    //QNetworkAccessManager *managerDownloadSongLrc;
};

#endif // WIDGET_H
