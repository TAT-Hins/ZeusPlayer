#include "fmradiowindow.h"
#include "ui_fmradiowindow.h"
#include <QDebug>
FMRadioWindow::FMRadioWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FMRadioWindow)
{
    ui->setupUi(this);
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->webView->setStyleSheet("background-color:rgb(150,147,88); padding: 7px ; color:rgb(255,255,255)");
    QUrl url("http://fm.baidu.com/");
    ui->webView->load(url);
}

FMRadioWindow::~FMRadioWindow()
{
    delete ui;
}

void FMRadioWindow::on_webView_linkClicked(QUrl url)
{
    ui->webView->load(url);
    ui->lineEdit->setText(url.toString());
}

