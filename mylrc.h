#ifndef MYLRC_H
#define MYLRC_H

#include <QLabel>
#include<QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class QTimer;
class QAction;

class MyLrc : public QDialog
{
    Q_OBJECT
public:
    explicit MyLrc(QWidget *parent = 0);
    void start_lrc_mask(qint64 intervaltime);
    void stop_lrc_mask();
    void setMusicInfo(QString name, QString filepath);
    QLabel *label;
signals:
    void changeselect(bool);
public slots:

private slots:
    void timeout();
    void downloadLrc();
    void replyFinished(QNetworkReply *reply);
private:
    QLabel *labelmask;
    QLinearGradient linear_gradient;
    QLinearGradient mask_linear_gradient;
    QFont font;
    QTimer *timer;
    qreal lrc_mask_width;

    qreal lrc_mask_width_interval;
    QPoint offset;

    QAction *actionUpdateLrc;

    QNetworkAccessManager *network_manager;
    QNetworkRequest *network_request;

    QString m_strName;
    QString m_strPath;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void contextMenuEvent(QContextMenuEvent *ev);
    bool  eventFilter(QObject *, QEvent *);

};

#endif // MYLRC_H
