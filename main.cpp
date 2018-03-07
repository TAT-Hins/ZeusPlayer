#include "mymaindlg.h"
#include "QIcon"
#include "qsingleapplication.h"
#include "QMessageBox"
#include "qdesktopwidget.h"
int main(int argc, char *argv[])
{
    QSingleApplication app(argc, argv);
    if(!app.isRunning())
    {
        app.setWindowIcon(QIcon(":/image/sysicon.ico"));
        app.setStyleSheet("QMenu{background-color: white;}"
                        "QMenu{font-size : 12px;color: rgb(63, 65, 67);font-family: 微软雅黑;}"
                        "QMenu{border: 1px solid gray;}"
                        "QMenu::item{padding: 2px 25px 2px 20px;}"
                        "QMenu::item:focus{padding: -1;}"
                        "QMenu::item{height: 22px;}"
                        "QMenu::item:selected{color: white;}"
                        "QMenu::item:!enabled{color:gray;}"
                        "QMenu::item:selected{background-color: rgb(15, 170, 255);}"

                        "QTableWidget{outline:0px;}"
                        "QTableWidget::item{outline:0px;}"
                        "QPushButton:focus{padding: -1;}");
        MyMainDlg dialog;
        app.w=&dialog;
        dialog.show();

        dialog.setGeometry(QApplication::desktop()->width()/2 - dialog.width(),(QApplication::desktop()->height() - dialog.height())/2,250,620);//居中显示
        return app.exec();
    }
    return 0;
}
