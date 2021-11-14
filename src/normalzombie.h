#ifndef NORMALZOMBIE_H
#define NORMALZOMBIE_H
#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
class normalZombie:public Zombie
{
public:
    normalZombie(int path_num);
    ~normalZombie()override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
#endif // NORMALZOMBIE_H
