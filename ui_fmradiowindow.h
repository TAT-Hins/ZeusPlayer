/********************************************************************************
** Form generated from reading UI file 'fmradiowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FMRADIOWINDOW_H
#define UI_FMRADIOWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FMRadioWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWebView *webView;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FMRadioWindow)
    {
        if (FMRadioWindow->objectName().isEmpty())
            FMRadioWindow->setObjectName(QStringLiteral("FMRadioWindow"));
        FMRadioWindow->resize(993, 697);
        centralWidget = new QWidget(FMRadioWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        FMRadioWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FMRadioWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 993, 26));
        FMRadioWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FMRadioWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FMRadioWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FMRadioWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FMRadioWindow->setStatusBar(statusBar);

        retranslateUi(FMRadioWindow);

        QMetaObject::connectSlotsByName(FMRadioWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FMRadioWindow)
    {
        FMRadioWindow->setWindowTitle(QApplication::translate("FMRadioWindow", "FMRadioWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class FMRadioWindow: public Ui_FMRadioWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FMRADIOWINDOW_H
