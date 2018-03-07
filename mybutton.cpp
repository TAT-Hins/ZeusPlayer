#include "mybutton.h"
#include<QPushButton>
mybutton::mybutton(QWidget*parent,QString str,QString picname):QPushButton(parent)
{
    this->setFlat(true);
    label=new QLabel(str,this);
    label->setStyleSheet("QLabel{color:white;}"
                         "QLabel:hover{background: rgb(25,25,25,125);}");
    label->setGeometry(0,0,40,100);
    label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

    label->setCursor(Qt::PointingHandCursor);
    label->hide();

    this->setIcon(QIcon(QPixmap(":/image/"+picname+".png")));
    this->setIconSize(QSize(40,100));

}
bool mybutton::eventFilter(QObject *obj, QEvent *event)
{
    return eventFilter(obj,event);
}
void mybutton::enterEvent(QEvent *)
{
    label->show();
}
void mybutton::leaveEvent(QEvent *)
{
    label->hide();
}
