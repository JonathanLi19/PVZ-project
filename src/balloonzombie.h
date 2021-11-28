#ifndef BALLOONZOMBIE_H
#define BALLOONZOMBIE_H
#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
//辅助的僵尸
class balloonzombie:public Zombie
{
public:
    balloonzombie(int path_num);
    ~balloonzombie()override;
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
};
#endif // BALLOONZOMBIE_H
