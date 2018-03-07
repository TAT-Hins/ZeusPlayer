#ifndef DOWNLOADINFODLG_H
#define DOWNLOADINFODLG_H
#include <QDialog>
#include<QLabel>
#include<QTableWidget>
namespace Ui {
class downloadinfodlg;
}

class downloadinfodlg : public QDialog
{
    Q_OBJECT

public:
    explicit downloadinfodlg(QWidget *parent = 0);
    QLabel *nowdownlabel;
    QTableWidget *tablewid;
    ~downloadinfodlg();
public slots:
    void setbk(QString);
signals:
    void downbtninfo(int tablerow,QString songinfo);
private slots:
    void on_pushButton_exit_clicked();
    void on_pushButton_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::downloadinfodlg *ui;
    bool    m_MousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;
};

#endif // DOWNLOADINFODLG_H
