#ifndef SKINBOX_H
#define SKINBOX_H
#include"ui_skinbox.h"
#include <QDialog>
#include<QFocusEvent>
#include <QPoint>
#include <QMouseEvent>
#include <QDialog>
#include<QSignalMapper>
#include<QSlider>
#include"mybutton.h"
namespace Ui {
class skinbox;
}

class skinbox : public QDialog
{
    Q_OBJECT
public slots:
    void setBk(QString);
public:
    explicit skinbox(QWidget *parent = 0);
    ~skinbox();
    void setslidervalue(int);

    QSlider *slider;
    QSignalMapper *signalMapper;
signals:
    void listbktransparent(int);
    void skinChange(QString);

protected:
   bool eventFilter(QObject *, QEvent *);
private:
    Ui::skinbox *ui;
    mybutton *btn,*btn1,*btn2,*btn3,*btn4,*btn5, *btn6,*btn7;
};


#endif // SKINBOX_H
