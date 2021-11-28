#include"distant_bleed.h"
#include"coffeebean_range.h"
#include<QGraphicsScene>
QRectF distant_bleed::boundingRect() const
{
    return QRectF(-30,-80,100,10);
}
//coffeebean等远程单位的攻击范围只能在mainwindow里画
void distant_bleed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-50,-80,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-30,-80,rate*100,10);
}
distant_bleed::distant_bleed()
{
    rate = 1;
}
distant_bleed::~distant_bleed()
{}
