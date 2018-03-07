#ifndef SEARCHLRCDLG_H
#define SEARCHLRCDLG_H
#include"mynetwork.h"
#include <QDialog>
#include<QLineEdit>
#include<QList>
#include<QListWidgetItem>
#include<mynetwork.h>
namespace Ui {
class searchlrcdlg;
}

class searchlrcdlg : public QDialog
{
    Q_OBJECT

public:
    explicit searchlrcdlg(QWidget *parent = 0);
     QLineEdit *ledit;
    QPushButton *serbtn;
     QString songtotalname;

    ~searchlrcdlg();
signals:
    void getlrcshow(QByteArray);
private slots:
    void on_pushButton_exit_clicked();
    void slotbtn();
    void analyieslrc(QNetworkReply*);
    void lrcsearslot(QNetworkReply*);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void returnpress();

public slots:
    void setBk(QString);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::searchlrcdlg *ui;
     QList <QString> listlrc;
    bool    m_MousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;
    QLabel *loadlab;

};

#endif // SEARCHLRCDLG_H
