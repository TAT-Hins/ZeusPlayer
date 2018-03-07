#ifndef FMRADIOWINDOW_H
#define FMRADIOWINDOW_H

#include <QMainWindow>
#include <QtWebKitWidgets/QWebView>

namespace Ui {
class FMRadioWindow;
}

class FMRadioWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FMRadioWindow(QWidget *parent = 0);
    ~FMRadioWindow();

private slots:

    void on_webView_linkClicked(QUrl url);

private:
    Ui::FMRadioWindow *ui;

};

#endif // FMRADIOWINDOW_H
