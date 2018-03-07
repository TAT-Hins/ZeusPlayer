#ifndef MYUI_H
#define MYUI_H

#include <QWidget>
#include "block_area.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MyUI : public QWidget
{
    Q_OBJECT
public:
    explicit MyUI(QWidget *parent = 0);
private:
    //设置布局
    QGridLayout *setingLayout;
    QLabel *rowLabel;
    QLineEdit *rowLineEdit;
    QLabel *columnLabel;
    QLineEdit *columnLineEdit;
    QLabel *mineLabel;
    QLineEdit *mineLineEdit;

    QPushButton *startBtn;

    QLabel *mineShowLabel;
    QLabel *mineNumLabel;
    QLabel *flagLabel;
    QLabel *flagNumLabel;

    //总布局
    QGridLayout *mainLayout;
    Block_Area *MineArea;

signals:

private slots:
    void restart();     //设置重启
    void updateflag();

public slots:
};

#endif // MYUI_H
