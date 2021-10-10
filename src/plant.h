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
    void attack();
    Plant();
    ~Plant()override;
    void advance(int phase) override;
    enum{Type = UserType + 1};
    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
};
#endif // PLANT_H
