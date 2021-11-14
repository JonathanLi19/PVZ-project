#ifndef COFFEEBEAN_H
#define COFFEEBEAN_H
#include"plant.h"
#include"zombie.h"
class CoffeeBean:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    CoffeeBean();
    ~CoffeeBean()override;
};
#endif // COFFEEBEAN_H
