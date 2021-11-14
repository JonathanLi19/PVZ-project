#ifndef DANCINGZOMBIE_H
#define DANCINGZOMBIE_H
#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
//远程攻击的僵尸
class dancingzombie:public Zombie
{
public:
    dancingzombie(int path_num);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
};
#endif // DANCINGZOMBIE_H
