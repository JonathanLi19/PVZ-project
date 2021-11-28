#ifndef FIRELOCKZOMBIE_H
#define FIRELOCKZOMBIE_H
#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
//畏战的飞行僵尸
class firelockzombie:public Zombie
{
public:
    firelockzombie(int path_num);
    ~firelockzombie()override;
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
};
#endif // FIRELOCKZOMBIE_H
