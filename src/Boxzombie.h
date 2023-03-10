#ifndef BOXZOMBIE_H
#define BOXZOMBIE_H
#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
//辅助的僵尸
class boxzombie:public Zombie
{
public:
    boxzombie(int path_num);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
    int counter;
    int attack_time;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    ~boxzombie()override;
};
#endif // BOXZOMBIE_H
