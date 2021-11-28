#include"plant_range.h"
#include<QGraphicsScene>
QRectF plant_range::boundingRect() const
{
    return size;
}
//coffeebean等远程单位的攻击范围只能在mainwindow里画
void plant_range::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(QPen(Qt::yellow,2));
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawRect(size);
}
plant_range::plant_range(QRectF size1)
{
    size = size1;
}
plant_range::~plant_range()
{}
