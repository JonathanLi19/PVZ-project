#include"normalzombie.h"
#include"Pathpoint.h"
normalZombie::normalZombie(int path_num1)
{
    hp = 500;
    hurt = 10;
    state = 1;
    speed = 10.0;
    path_num = path_num1;
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
}
normalZombie::~normalZombie()
{}
void normalZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-70, -100, 140, 140),QImage("D:/QtProjects/images/ZombieWalk1.gif"));
}
QRectF normalZombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
