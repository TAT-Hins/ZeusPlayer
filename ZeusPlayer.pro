#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T20:53:35
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       += network
QT       += webkitwidgets
QT       += script
QT       += core gui network multimedia script winextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZeusPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mymaindlg.cpp \
    downloadinfodlg.cpp \
    mylrc.cpp \
    mymaintablewidget.cpp \
    mynetwork.cpp \
    myplaylist.cpp \
    qsingleapplication.cpp \
    searchlrcdlg.cpp \
    skinbox.cpp \
    musicmarqueewidget.cpp \
    mybutton.cpp \
    fmradiowindow.cpp \
    videoplayer.cpp \
    block_area.cpp \
    block.cpp \
    myui.cpp \
    widget.cpp \
    qvolumnbutton.cpp

HEADERS  += mymaindlg.h \
    downloadinfodlg.h \
    mylrc.h \
    mymaintablewidget.h \
    mynetwork.h \
    myplaylist.h \
    qsingleapplication.h \
    searchlrcdlg.h \
    skinbox.h \
    musicmarqueewidget.h \
    mybutton.h \
    fmradiowindow.h \
    videoplayer.h \
    block_area.h \
    block.h \
    myui.h \
    widget.h \
    qvolumnbutton.h

FORMS    += mymaindlg.ui \
    downloadinfodlg.ui \
    searchlrcdlg.ui \
    skinbox.ui \
    fmradiowindow.ui \
    widget.ui

RESOURCES += \
    resource.qrc
RC_FILE = image/sysicon.rc
