#include"wallnut.h"
QRectF wallnut::boundingRect() const
{
    return QRectF(-60, -80, 120, 120);
}
wallnut::wallnut()
{
    hp = 50;
    total_hp = 50;
    hurt = 0;
    cost = 50;
    state = 1;
    plant_type = 0;//近战
    hold_back = 100000;
    cur_hold = 0;
    setMovie("D:/QtProjects/images/Plants/WallNut/WallNut.gif");
}
wallnut::~wallnut()
{}
void wallnut::advance(int phase)
{
    if(!phase)
        return;
    update();
}
void wallnut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-50,-80,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-50,-80,rate*100,10);
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}
