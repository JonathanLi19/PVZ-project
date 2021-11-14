#ifndef WALLNUT_H
#define WALLNUT_H
#include"plant.h"
#include"zombie.h"
class wallnut:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    wallnut();
    ~wallnut()override;
};
#endif // WALLNUT_H
