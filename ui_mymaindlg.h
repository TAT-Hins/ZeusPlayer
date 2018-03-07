/********************************************************************************
** Form generated from reading UI file 'mymaindlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINDLG_H
#define UI_MYMAINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMainDlg
{
public:
    QPushButton *pushButton_next;
    QSlider *horizontalSlider_vol;
    QPushButton *pushButton_backward;
    QLabel *label_playtime;
    QWidget *widget_search;
    QLabel *label_search;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_searchclose;
    QFrame *line_6;
    QPushButton *pushButton_skinbox;
    QPushButton *pushButton_add;
    QCheckBox *checkBox;
    QPushButton *pushButton_playmode;
    QLabel *label_pic;
    QPushButton *pushButton_search;
    QListWidget *listWidget_side;
    QSlider *horizontalSlider;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_playpause;
    QFrame *line_borderleft;
    QPushButton *pushButton_vol;
    QLabel *label_title;
    QFrame *line_5;
    QPushButton *pushButton_location;
    QLabel *label_songscount;
    QPushButton *pushButton_mini;
    QLabel *label_musicicon;
    QPushButton *pushButton_up;
    QPushButton *pushButton_down;
    QPushButton *pushButton_webplayer;
    QPushButton *pushButton_fmradio;
    QPushButton *pushButton_videoplayer;
    QPushButton *pushButton_minesweeping;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QDialog *MyMainDlg)
    {
        if (MyMainDlg->objectName().isEmpty())
            MyMainDlg->setObjectName(QStringLiteral("MyMainDlg"));
        MyMainDlg->resize(1000, 618);
        MyMainDlg->setMinimumSize(QSize(1000, 618));
        MyMainDlg->setMaximumSize(QSize(1000, 618));
        pushButton_next = new QPushButton(MyMainDlg);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(532, 575, 32, 32));
        pushButton_next->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_next->setStyleSheet(QLatin1String("border-image: url(:/next_hover.png);\n"
"border-image: url(:/next_unhover.png);"));
        pushButton_next->setFlat(true);
        horizontalSlider_vol = new QSlider(MyMainDlg);
        horizontalSlider_vol->setObjectName(QStringLiteral("horizontalSlider_vol"));
        horizontalSlider_vol->setGeometry(QRect(885, 580, 91, 21));
        horizontalSlider_vol->setStyleSheet(QStringLiteral("background:transparent;"));
        horizontalSlider_vol->setPageStep(10);
        horizontalSlider_vol->setTracking(false);
        horizontalSlider_vol->setOrientation(Qt::Horizontal);
        horizontalSlider_vol->setInvertedControls(false);
        pushButton_backward = new QPushButton(MyMainDlg);
        pushButton_backward->setObjectName(QStringLiteral("pushButton_backward"));
        pushButton_backward->setGeometry(QRect(432, 575, 32, 32));
        pushButton_backward->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_backward->setStyleSheet(QLatin1String("border-image: url(:/prev_hover.png);\n"
"border-image: url(:/prev_unhover.png);"));
        pushButton_backward->setFlat(true);
        label_playtime = new QLabel(MyMainDlg);
        label_playtime->setObjectName(QStringLiteral("label_playtime"));
        label_playtime->setGeometry(QRect(790, 580, 61, 16));
        label_playtime->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background:transparent;"));
        widget_search = new QWidget(MyMainDlg);
        widget_search->setObjectName(QStringLiteral("widget_search"));
        widget_search->setGeometry(QRect(310, 30, 261, 36));
        widget_search->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_search = new QLabel(widget_search);
        label_search->setObjectName(QStringLiteral("label_search"));
        label_search->setGeometry(QRect(10, 13, 16, 16));
        label_search->setStyleSheet(QStringLiteral("border-image: url(:/image/search_16.ico);"));
        lineEdit_search = new QLineEdit(widget_search);
        lineEdit_search->setObjectName(QStringLiteral("lineEdit_search"));
        lineEdit_search->setGeometry(QRect(38, 10, 191, 20));
        lineEdit_search->setAutoFillBackground(false);
        lineEdit_search->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(41, 57, 85);\n"
"font: 13pt \"\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2\";\n"
"background-color:transparent;"));
        lineEdit_search->setFrame(true);
        pushButton_searchclose = new QPushButton(widget_search);
        pushButton_searchclose->setObjectName(QStringLiteral("pushButton_searchclose"));
        pushButton_searchclose->setGeometry(QRect(235, 12, 16, 16));
        pushButton_searchclose->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_searchclose->setStyleSheet(QLatin1String("background:transparent;\n"
"border-image: url(:/image/searchclose.ico);"));
        pushButton_searchclose->setDefault(false);
        pushButton_searchclose->setFlat(true);
        line_6 = new QFrame(MyMainDlg);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(0, 610, 331, 31));
        line_6->setStyleSheet(QStringLiteral("background:transparent;"));
        line_6->setFrameShadow(QFrame::Plain);
        line_6->setFrameShape(QFrame::HLine);
        pushButton_skinbox = new QPushButton(MyMainDlg);
        pushButton_skinbox->setObjectName(QStringLiteral("pushButton_skinbox"));
        pushButton_skinbox->setGeometry(QRect(910, 0, 25, 25));
        pushButton_skinbox->setFlat(true);
        pushButton_add = new QPushButton(MyMainDlg);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setGeometry(QRect(40, 470, 30, 30));
        pushButton_add->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_add->setStyleSheet(QStringLiteral(""));
        pushButton_add->setAutoDefault(true);
        pushButton_add->setDefault(true);
        pushButton_add->setFlat(true);
        checkBox = new QCheckBox(MyMainDlg);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(320, 570, 71, 41));
        checkBox->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"font: 18pt \"\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2\";\n"
"color: rgb(255, 255, 255);\n"
""));
        pushButton_playmode = new QPushButton(MyMainDlg);
        pushButton_playmode->setObjectName(QStringLiteral("pushButton_playmode"));
        pushButton_playmode->setGeometry(QRect(190, 470, 30, 30));
        pushButton_playmode->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_playmode->setAcceptDrops(false);
        pushButton_playmode->setFlat(true);
        label_pic = new QLabel(MyMainDlg);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        label_pic->setGeometry(QRect(40, 555, 61, 61));
        label_pic->setCursor(QCursor(Qt::PointingHandCursor));
        label_pic->setStyleSheet(QLatin1String("background-color: rgba(250, 250, 250, 150);\n"
"background-image: url(:/image/musichead.ico);"));
        label_pic->setScaledContents(false);
        pushButton_search = new QPushButton(MyMainDlg);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(90, 470, 30, 30));
        pushButton_search->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_search->setAutoDefault(true);
        pushButton_search->setFlat(true);
        listWidget_side = new QListWidget(MyMainDlg);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\271\346\255\243\345\205\260\344\272\255\350\266\205\347\273\206\351\273\221\347\256\200\344\275\223"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_side);
        __qlistwidgetitem->setFont(font);
        __qlistwidgetitem->setIcon(icon);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_side);
        __qlistwidgetitem1->setFont(font);
        listWidget_side->setObjectName(QStringLiteral("listWidget_side"));
        listWidget_side->setGeometry(QRect(0, 80, 261, 71));
        listWidget_side->setMaximumSize(QSize(261, 16777215));
        listWidget_side->setFocusPolicy(Qt::NoFocus);
        listWidget_side->setContextMenuPolicy(Qt::DefaultContextMenu);
        listWidget_side->setStyleSheet(QLatin1String("backgroud:transparent;\n"
"font: 13pt \"PingFang SC\";\n"
""));
        listWidget_side->setFrameShape(QFrame::NoFrame);
        listWidget_side->setFrameShadow(QFrame::Plain);
        listWidget_side->setLineWidth(1);
        listWidget_side->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget_side->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget_side->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget_side->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget_side->setMovement(QListView::Static);
        listWidget_side->setFlow(QListView::TopToBottom);
        listWidget_side->setProperty("isWrapping", QVariant(false));
        listWidget_side->setResizeMode(QListView::Fixed);
        listWidget_side->setViewMode(QListView::ListMode);
        listWidget_side->setBatchSize(100);
        listWidget_side->setSortingEnabled(false);
        horizontalSlider = new QSlider(MyMainDlg);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(570, 580, 195, 20));
        horizontalSlider->setStyleSheet(QStringLiteral("background:transparent;"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_exit = new QPushButton(MyMainDlg);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(970, 0, 25, 25));
        pushButton_exit->setAutoFillBackground(false);
        pushButton_exit->setIconSize(QSize(24, 24));
        pushButton_exit->setAutoDefault(true);
        pushButton_exit->setDefault(false);
        pushButton_exit->setFlat(true);
        pushButton_playpause = new QPushButton(MyMainDlg);
        pushButton_playpause->setObjectName(QStringLiteral("pushButton_playpause"));
        pushButton_playpause->setGeometry(QRect(478, 571, 40, 40));
        pushButton_playpause->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_playpause->setFocusPolicy(Qt::NoFocus);
        pushButton_playpause->setStyleSheet(QLatin1String("border-image: url(:/pause_hover.png);\n"
"border-image: url(:/pause_unhover.png);\n"
"border-image: url(:/play_hover.png);\n"
"border-image: url(:/play_unhover.png);"));
        pushButton_playpause->setIconSize(QSize(16, 16));
        pushButton_playpause->setFlat(true);
        line_borderleft = new QFrame(MyMainDlg);
        line_borderleft->setObjectName(QStringLiteral("line_borderleft"));
        line_borderleft->setGeometry(QRect(0, 0, 1, 620));
        line_borderleft->setStyleSheet(QStringLiteral(""));
        line_borderleft->setFrameShadow(QFrame::Plain);
        line_borderleft->setLineWidth(1);
        line_borderleft->setFrameShape(QFrame::VLine);
        pushButton_vol = new QPushButton(MyMainDlg);
        pushButton_vol->setObjectName(QStringLiteral("pushButton_vol"));
        pushButton_vol->setEnabled(true);
        pushButton_vol->setGeometry(QRect(865, 580, 18, 18));
        pushButton_vol->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_vol->setStyleSheet(QLatin1String("border-image: url(:image/volume.png);\n"
"border-image: url(:image/volume_step.png);\n"
"border-image: url(:image/volume_shut.png);"));
        pushButton_vol->setDefault(false);
        pushButton_vol->setFlat(true);
        label_title = new QLabel(MyMainDlg);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(40, -20, 181, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2"));
        font1.setPointSize(19);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_title->setFont(font1);
        label_title->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font:19pt \"\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2\";"));
        label_title->setTextFormat(Qt::RichText);
        label_title->setScaledContents(false);
        line_5 = new QFrame(MyMainDlg);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(0, -10, 331, 16));
        line_5->setStyleSheet(QStringLiteral("background:transparent;"));
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setFrameShape(QFrame::HLine);
        pushButton_location = new QPushButton(MyMainDlg);
        pushButton_location->setObjectName(QStringLiteral("pushButton_location"));
        pushButton_location->setGeometry(QRect(140, 470, 30, 30));
        pushButton_location->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_location->setFlat(true);
        label_songscount = new QLabel(MyMainDlg);
        label_songscount->setObjectName(QStringLiteral("label_songscount"));
        label_songscount->setGeometry(QRect(150, 560, 171, 41));
        label_songscount->setCursor(QCursor(Qt::UpArrowCursor));
        label_songscount->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 18pt \"PingFang SC\";\n"
"background:transparent;"));
        label_songscount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_mini = new QPushButton(MyMainDlg);
        pushButton_mini->setObjectName(QStringLiteral("pushButton_mini"));
        pushButton_mini->setGeometry(QRect(940, 0, 25, 25));
        pushButton_mini->setFlat(true);
        label_musicicon = new QLabel(MyMainDlg);
        label_musicicon->setObjectName(QStringLiteral("label_musicicon"));
        label_musicicon->setGeometry(QRect(10, 0, 23, 23));
        label_musicicon->setAutoFillBackground(false);
        label_musicicon->setStyleSheet(QStringLiteral("border-image: url(:/image/music.png);"));
        label_musicicon->setTextFormat(Qt::RichText);
        label_musicicon->setPixmap(QPixmap(QString::fromUtf8(":/image/music.ico")));
        label_musicicon->setScaledContents(true);
        pushButton_up = new QPushButton(MyMainDlg);
        pushButton_up->setObjectName(QStringLiteral("pushButton_up"));
        pushButton_up->setGeometry(QRect(270, 430, 30, 30));
        pushButton_up->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_up->setStyleSheet(QStringLiteral("border-image: url(:/1111.png);"));
        pushButton_up->setFlat(true);
        pushButton_down = new QPushButton(MyMainDlg);
        pushButton_down->setObjectName(QStringLiteral("pushButton_down"));
        pushButton_down->setGeometry(QRect(270, 480, 30, 30));
        pushButton_down->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_down->setStyleSheet(QStringLiteral("border-image: url(:/2222.png);"));
        pushButton_down->setFlat(true);
        pushButton_webplayer = new QPushButton(MyMainDlg);
        pushButton_webplayer->setObjectName(QStringLiteral("pushButton_webplayer"));
        pushButton_webplayer->setGeometry(QRect(40, 230, 80, 80));
        pushButton_webplayer->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_webplayer->setStyleSheet(QStringLiteral("border-image: url(:/1.png);"));
        pushButton_webplayer->setFlat(true);
        pushButton_fmradio = new QPushButton(MyMainDlg);
        pushButton_fmradio->setObjectName(QStringLiteral("pushButton_fmradio"));
        pushButton_fmradio->setGeometry(QRect(140, 230, 80, 80));
        pushButton_fmradio->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_fmradio->setStyleSheet(QStringLiteral("border-image: url(:/2.png);"));
        pushButton_fmradio->setFlat(true);
        pushButton_videoplayer = new QPushButton(MyMainDlg);
        pushButton_videoplayer->setObjectName(QStringLiteral("pushButton_videoplayer"));
        pushButton_videoplayer->setGeometry(QRect(40, 330, 80, 80));
        pushButton_videoplayer->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_videoplayer->setStyleSheet(QStringLiteral("border-image: url(:/4.png);"));
        pushButton_videoplayer->setFlat(true);
        pushButton_minesweeping = new QPushButton(MyMainDlg);
        pushButton_minesweeping->setObjectName(QStringLiteral("pushButton_minesweeping"));
        pushButton_minesweeping->setGeometry(QRect(140, 330, 80, 80));
        pushButton_minesweeping->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_minesweeping->setStyleSheet(QStringLiteral("border-image: url(:/3.png);"));
        pushButton_minesweeping->setFlat(true);
        line_3 = new QFrame(MyMainDlg);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 540, 1021, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(MyMainDlg);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(247, 79, 31, 470));
        line_4->setStyleSheet(QStringLiteral(""));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line = new QFrame(MyMainDlg);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 72, 261, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(MyMainDlg);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 135, 261, 41));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(MyMainDlg);

        QMetaObject::connectSlotsByName(MyMainDlg);
    } // setupUi

    void retranslateUi(QDialog *MyMainDlg)
    {
        MyMainDlg->setWindowTitle(QApplication::translate("MyMainDlg", "MyMainDlg", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_next->setToolTip(QApplication::translate("MyMainDlg", "\344\270\213\344\270\200\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        pushButton_next->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_backward->setToolTip(QApplication::translate("MyMainDlg", "\344\270\212\344\270\200\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        pushButton_backward->setText(QString());
        label_playtime->setText(QApplication::translate("MyMainDlg", "00:00/00:00", 0));
        label_search->setText(QString());
#ifndef QT_NO_TOOLTIP
        lineEdit_search->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lineEdit_search->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        lineEdit_search->setInputMask(QString());
        lineEdit_search->setText(QString());
        lineEdit_search->setPlaceholderText(QApplication::translate("MyMainDlg", "\346\237\245\346\211\276\345\210\227\350\241\250\346\255\214\346\233\262", 0));
        pushButton_searchclose->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_skinbox->setToolTip(QApplication::translate("MyMainDlg", "\347\232\256\350\202\244", 0));
#endif // QT_NO_TOOLTIP
        pushButton_skinbox->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_add->setToolTip(QApplication::translate("MyMainDlg", "\346\267\273\345\212\240\346\255\214\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        pushButton_add->setText(QString());
        checkBox->setText(QApplication::translate("MyMainDlg", "\346\255\214\350\257\215", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_playmode->setToolTip(QApplication::translate("MyMainDlg", "\346\222\255\346\224\276\346\250\241\345\274\217", 0));
#endif // QT_NO_TOOLTIP
        pushButton_playmode->setText(QString());
        label_pic->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_search->setToolTip(QApplication::translate("MyMainDlg", "\346\237\245\346\211\276\346\255\214\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        pushButton_search->setText(QString());

        const bool __sortingEnabled = listWidget_side->isSortingEnabled();
        listWidget_side->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_side->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MyMainDlg", "           \346\255\214\350\257\215", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_side->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MyMainDlg", "          \346\234\254\345\234\260\345\210\227\350\241\250", 0));
        listWidget_side->setSortingEnabled(__sortingEnabled);

        pushButton_exit->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_playpause->setToolTip(QApplication::translate("MyMainDlg", "\346\222\255\346\224\276", 0));
#endif // QT_NO_TOOLTIP
        pushButton_playpause->setText(QString());
        pushButton_vol->setText(QString());
        label_title->setText(QApplication::translate("MyMainDlg", "zeusplayer", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_location->setToolTip(QApplication::translate("MyMainDlg", "\346\255\214\346\233\262\345\256\232\344\275\215", 0));
#endif // QT_NO_TOOLTIP
        pushButton_location->setText(QString());
        label_songscount->setText(QApplication::translate("MyMainDlg", "\346\255\214\346\233\262\346\225\260:0", 0));
        pushButton_mini->setText(QString());
        label_musicicon->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_up->setToolTip(QApplication::translate("MyMainDlg", "up", 0));
#endif // QT_NO_TOOLTIP
        pushButton_up->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_down->setToolTip(QApplication::translate("MyMainDlg", "down", 0));
#endif // QT_NO_TOOLTIP
        pushButton_down->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_webplayer->setToolTip(QApplication::translate("MyMainDlg", "\347\275\221\347\273\234\346\222\255\346\224\276\345\231\250", 0));
#endif // QT_NO_TOOLTIP
        pushButton_webplayer->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_fmradio->setToolTip(QApplication::translate("MyMainDlg", "\351\232\217\344\276\277\345\220\254\345\220\254\346\255\214\345\220\247", 0));
#endif // QT_NO_TOOLTIP
        pushButton_fmradio->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_videoplayer->setToolTip(QApplication::translate("MyMainDlg", "\347\210\261\350\247\206\351\242\221", 0));
#endif // QT_NO_TOOLTIP
        pushButton_videoplayer->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_minesweeping->setToolTip(QApplication::translate("MyMainDlg", "\345\260\217\346\270\270\346\210\217\342\200\224\342\200\224\346\211\253\351\233\267", 0));
#endif // QT_NO_TOOLTIP
        pushButton_minesweeping->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyMainDlg: public Ui_MyMainDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINDLG_H
