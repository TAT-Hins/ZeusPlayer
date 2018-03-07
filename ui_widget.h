/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *lb_find;
    QLineEdit *le_find;
    QPushButton *pb_play;
    QPushButton *pb_song;
    QPushButton *pb_next;
    QPushButton *pb_replay;
    QLabel *lb_volumn;
    QTableWidget *tb_find;
    QFrame *frame;
    QPushButton *pb_minimum;
    QPushButton *pb_close;
    QLabel *lb_onPlay;
    QLabel *lb_duration;
    QSlider *slider;
    QTableWidget *tb_play;
    QLabel *lb_play;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(573, 527);
        Widget->setStyleSheet(QStringLiteral(""));
        lb_find = new QLabel(Widget);
        lb_find->setObjectName(QStringLiteral("lb_find"));
        lb_find->setGeometry(QRect(240, 60, 81, 21));
        le_find = new QLineEdit(Widget);
        le_find->setObjectName(QStringLiteral("le_find"));
        le_find->setGeometry(QRect(330, 61, 171, 20));
        le_find->setFocusPolicy(Qt::ClickFocus);
        pb_play = new QPushButton(Widget);
        pb_play->setObjectName(QStringLiteral("pb_play"));
        pb_play->setGeometry(QRect(10, 30, 28, 28));
        pb_play->setStyleSheet(QStringLiteral(""));
        pb_play->setFlat(true);
        pb_song = new QPushButton(Widget);
        pb_song->setObjectName(QStringLiteral("pb_song"));
        pb_song->setGeometry(QRect(130, 30, 28, 28));
        pb_song->setStyleSheet(QStringLiteral(""));
        pb_song->setDefault(false);
        pb_song->setFlat(true);
        pb_next = new QPushButton(Widget);
        pb_next->setObjectName(QStringLiteral("pb_next"));
        pb_next->setGeometry(QRect(50, 30, 28, 28));
        pb_next->setStyleSheet(QStringLiteral(""));
        pb_next->setFlat(true);
        pb_replay = new QPushButton(Widget);
        pb_replay->setObjectName(QStringLiteral("pb_replay"));
        pb_replay->setGeometry(QRect(90, 30, 28, 28));
        pb_replay->setStyleSheet(QStringLiteral(""));
        pb_replay->setFlat(true);
        lb_volumn = new QLabel(Widget);
        lb_volumn->setObjectName(QStringLiteral("lb_volumn"));
        lb_volumn->setGeometry(QRect(190, 60, 28, 20));
        tb_find = new QTableWidget(Widget);
        tb_find->setObjectName(QStringLiteral("tb_find"));
        tb_find->setGeometry(QRect(290, 90, 271, 411));
        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 1, 511, 28));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pb_minimum = new QPushButton(frame);
        pb_minimum->setObjectName(QStringLiteral("pb_minimum"));
        pb_minimum->setGeometry(QRect(440, 0, 28, 28));
        pb_minimum->setFlat(true);
        pb_close = new QPushButton(frame);
        pb_close->setObjectName(QStringLiteral("pb_close"));
        pb_close->setGeometry(QRect(470, 0, 28, 28));
        pb_close->setFlat(true);
        lb_onPlay = new QLabel(frame);
        lb_onPlay->setObjectName(QStringLiteral("lb_onPlay"));
        lb_onPlay->setGeometry(QRect(10, 3, 421, 21));
        lb_duration = new QLabel(Widget);
        lb_duration->setObjectName(QStringLiteral("lb_duration"));
        lb_duration->setGeometry(QRect(460, 30, 61, 21));
        slider = new QSlider(Widget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setGeometry(QRect(260, 33, 191, 21));
        slider->setOrientation(Qt::Horizontal);
        tb_play = new QTableWidget(Widget);
        tb_play->setObjectName(QStringLiteral("tb_play"));
        tb_play->setGeometry(QRect(10, 90, 261, 411));
        lb_play = new QLabel(Widget);
        lb_play->setObjectName(QStringLiteral("lb_play"));
        lb_play->setGeometry(QRect(60, 60, 71, 21));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        lb_find->setText(QApplication::translate("Widget", "\346\255\214\346\233\262\347\211\271\345\276\201\357\274\232", 0));
#ifndef QT_NO_WHATSTHIS
        le_find->setWhatsThis(QApplication::translate("Widget", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        le_find->setPlaceholderText(QApplication::translate("Widget", "Easy Touch", 0));
        pb_play->setText(QString());
        pb_song->setText(QString());
        pb_next->setText(QString());
        pb_replay->setText(QString());
        lb_volumn->setText(QString());
        pb_minimum->setText(QString());
        pb_close->setText(QString());
        lb_onPlay->setText(QString());
        lb_duration->setText(QApplication::translate("Widget", "00:00", 0));
        lb_play->setText(QApplication::translate("Widget", "\346\222\255\346\224\276\345\210\227\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
