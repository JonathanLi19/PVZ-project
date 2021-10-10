#include"caiwen.h"
QRectF CaiWen::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}
void CaiWen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -50, 100, 100),QImage("D:/QtProjects/images/Plants/Chomper/Chomper.gif"));
}
CaiWen::CaiWen()
{
    hp = 500;
    hurt = 20;
    cost = 50;
    state = 1;
}
CaiWen::~CaiWen()
{}
