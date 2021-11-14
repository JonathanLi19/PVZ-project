#ifndef PLANT_H
#define PLANT_H
#include<QGraphicsItem>
#include<QPainter>
#define INITIAL_RESOURCE 1000
extern int CUR_SRC;
class Plant:public QGraphicsItem
{
public:
    int hp;
    int hurt;
    int cost;
    int state;//攻击还是静止
    int plant_type;//近战0还是远战1
    int hold_back;//阻拦数
    int cur_hold;//当前栏了几个
    QString name;//植物名字
    void attack();
    Plant();
    ~Plant()override;
    enum{Type = UserType + 1};
    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
    void advance(int phase) override;
};
#endif // PLANT_H
