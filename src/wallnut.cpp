#include"wallnut.h"
QRectF wallnut::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}
void wallnut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -50, 100, 100),QImage("D:/QtProjects/images/Plants/WallNut/WallNut.gif"));
}
wallnut::wallnut()
{
    hp = 5000;
    hurt = 0;
    cost = 50;
    state = 1;
    plant_type = 0;//近战
}
wallnut::~wallnut()
{}
