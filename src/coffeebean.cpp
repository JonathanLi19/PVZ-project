#include"coffeebean.h"
QRectF CoffeeBean::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}
void CoffeeBean::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -50, 100, 100),QImage("D:/QtProjects/images/Plants/CoffeeBean/CoffeeBean.gif"));
}
CoffeeBean::CoffeeBean()
{
    hp = 0;
    hurt = 1;
    cost = 100;
    state = 1;
    plant_type = 1;//远战
    hold_back = 0;//一次阻拦1个僵尸
    cur_hold = 0;
    name = "coffeebean";
}
CoffeeBean::~CoffeeBean()
{}
