#include"boxzombie_bullet.h"
#include<QDebug>
QRectF boxzombie_bullet::boundingRect() const
{
    return QRectF(-30, -30, 60, 60);
}
void boxzombie_bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-12, -28, 40, 20),QImage("D:/QtProjects/images/Plants/PB10.gif"));
}
boxzombie_bullet::boxzombie_bullet(int attack,QPointF dest1,Zombie* parent1,QPointF start1)
{
    atk = attack;
    speed = 0.05;
    dest = dest1;
    parent = parent1;
    start = start1;
}
boxzombie_bullet::~boxzombie_bullet()
{}
void boxzombie_bullet::advance(int phase)
{
    if(!phase)
        return;
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
           Plant *plant = qgraphicsitem_cast<Plant *>(items[qrand() % items.size()]);
           plant->hp -= atk;
           if(plant->hp <= 0)
           {
              // plant->~Plant();
               delete plant;
               //parent->state = 1;
               //parent->setMovie("D:/QtProjects/images/Zombies/JackinTheBoxZombie/Walk.gif");
           }
           delete this;
           return;
    }

    setX(x() + speed*(- start.x() + dest.x()));
    setY(y() + speed*(- start.y() + dest.y()));
    if(x() < 100 || y() < 150)//飞离画面？
        delete this;
}
bool boxzombie_bullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y()- y())<50 && qAbs(other->x() - x()) < 50;
}
