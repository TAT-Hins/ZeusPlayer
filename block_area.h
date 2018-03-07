  #ifndef BLOCK_AREA_H
#define BLOCK_AREA_H

#include <QWidget>
#include "block.h"
#include <QGridLayout>

class Block_Area : public QWidget
{
    Q_OBJECT

public:
    int row;        //行
    int column;     //列
    QList<Block *> MineBlock;
    //QList<Block> MineBlock;
    explicit Block_Area(int Trow, int Tcolumn, int Tmine);
    //Block_Area(QWidget *parent = 0,int Trow,int Tcolumn,int Tmine);

    void setAreaAttr(int mycolumn, int myrow, int mines);     //设置方格属性
    void setMineCount(int index);
    int getBlockMineNum(int x,int y);
    int cal_flag(int trow, int tcolumn);                //计算当前area中标记数量
private:

    int mine_count; //雷的总数
    QGridLayout *mainLayout;

signals:
    void sgn_restart();
    void sgn_flagChang();
public slots:
    void slt_restart();
    void slt_flagChange();
};

#endif // BLOCK_AREA_H
