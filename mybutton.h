#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QLabel>
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QString>
class mybutton : public QPushButton
{
public:
   explicit mybutton(QWidget*parent=0,QString title="",QString picname="");
protected:
    bool eventFilter(QObject *, QEvent *);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
private:
    QLabel *label;
};

#endif // MYBUTTON_H
