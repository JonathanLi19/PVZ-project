#ifndef COFFEEBEAN_H
#define COFFEEBEAN_H
#include"plant.h"
#include"zombie.h"
class CoffeeBean:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;
    CoffeeBean();
    ~CoffeeBean()override;
    bool could_place_potato(int x,int y);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    int prefer;//偏好设置，0从上往下，1从下往上
};
#endif // COFFEEBEAN_H
