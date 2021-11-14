#ifndef BLOVER_H
#define BLOVER_H
#include"plant.h"
#include"zombie.h"
//可以打地面也可以打飞行
class Blover:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    Blover();
    ~Blover()override;
    void advance(int phase) override;
};
#endif // BLOVER_H
