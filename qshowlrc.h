#ifndef QSHOWLRC_H
#define QSHOWLRC_H

#include <QTextEdit>
#include <QMouseEvent>

namespace Ui
{
    class QShowLrc;
}

class QShowLrc : public QWidget
{
    Q_OBJECT

public:
    explicit QShowLrc(QWidget *parent = 0);
    ~QShowLrc();
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void initWinAttribute();
    void initWinInterface();
    void initTextEdit();
    void setLrc(QString lrc);
    void regExgLrc(QString lrc);
    void showLrcOnText();

private slots:
    void on_pb_close_clicked();

private:
    Ui::QShowLrc *ui;
    QMap<qint64, QString> lrc_map;
    QPoint move_point;
    bool mouse_press;
};

#endif // QSHOWLRC_H
