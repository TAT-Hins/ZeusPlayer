/********************************************************************************
** Form generated from reading UI file 'searchlrcdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHLRCDLG_H
#define UI_SEARCHLRCDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchlrcdlg
{
public:
    QWidget *widget;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *pushButton_exit;
    QLabel *label_2;

    void setupUi(QDialog *searchlrcdlg)
    {
        if (searchlrcdlg->objectName().isEmpty())
            searchlrcdlg->setObjectName(QStringLiteral("searchlrcdlg"));
        searchlrcdlg->resize(281, 326);
        widget = new QWidget(searchlrcdlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(18, 25, 261, 301));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(5, 10, 60, 16));
        label->setStyleSheet(QString::fromUtf8("font: 13pt \"\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2\";"));
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(16, 40, 201, 221));
        pushButton_exit = new QPushButton(searchlrcdlg);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(229, 1, 21, 21));
        label_2 = new QLabel(searchlrcdlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(2, 0, 60, 25));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 10pt \"\345\217\266\346\240\271\345\217\213\345\217\244\345\210\273\344\275\2231.2\";"));

        retranslateUi(searchlrcdlg);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), searchlrcdlg, SLOT(close()));

        QMetaObject::connectSlotsByName(searchlrcdlg);
    } // setupUi

    void retranslateUi(QDialog *searchlrcdlg)
    {
        searchlrcdlg->setWindowTitle(QApplication::translate("searchlrcdlg", "Dialog", 0));
        label->setText(QApplication::translate("searchlrcdlg", "\346\255\214\346\233\262\345\220\215:", 0));
        pushButton_exit->setText(QString());
        label_2->setText(QApplication::translate("searchlrcdlg", "\346\255\214\350\257\215\346\220\234\347\264\242", 0));
    } // retranslateUi

};

namespace Ui {
    class searchlrcdlg: public Ui_searchlrcdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHLRCDLG_H
