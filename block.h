#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>

class Block : public QLabel
{
    Q_OBJECT

public:

    bool mine_Flag;         //雷的标记
    int mine_Num;           //雷的数目
    bool visible_Flag;      //可见标记      //槽
    bool mark_Flag;         //插旗标记      //槽

    Block(QWidget *parent = 0);
    ~Block();


    void setMine_Flag(bool flag);       //设置是否为雷
    void setMine_Num(int num);       //计算并设置周围雷的数目
    void GameOver();

private slots:
    void setVisible_Flag(void);       //设置是否可见
    void setMark_Flag(void);       //设置是否插旗
protected:
    void mousePressEvent(QMouseEvent* event);

private:

signals:
    void Restart();
    void FlagChange();

};

#endif // BLOCK_H
