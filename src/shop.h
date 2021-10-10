#ifndef SHOP_H
#define SHOP_H
#include<QGraphicsItem>
#include<QPainter>
class shop:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
#endif // SHOP_H
