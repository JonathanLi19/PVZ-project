#include"shop.h"
void shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-200, -90, 800, 180),QImage("D:/QtProjects/images/shop.png"));
}
QRectF shop::boundingRect() const
{
    return QRectF(-250, -50, 500, 100);
}
