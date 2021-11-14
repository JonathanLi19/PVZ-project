#include"shroombullet.h"
QRectF shroombullet::boundingRect() const
{
    return QRectF(-12, -28, 40, 20);
}
void shroombullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-12, -28, 40, 20),QImage("D:/QtProjects/images/Plants/ShroomBullet.gif"));
}
shroombullet::shroombullet(int attack)
{
    atk = attack;
    speed = 360.0 * 33 / 500;
}
shroombullet::~shroombullet()
{}
void shroombullet::advance(int phase)
{
    if(!phase)
        return;
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
           Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[qrand() % items.size()]);
           zombie->hp -= atk;
           if(zombie->hp <= 0)
           {
               zombie->~Zombie();
           }
           delete this;
           return;
    }
    //飞离画面？
    setX(x() + speed);
    if(x()>1800)
        delete this;
}
bool shroombullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != Zombie::Type)
        return false;
    Zombie *zombie = (Zombie *)(other);
    return zombie->zombie_type == 0 && qAbs(other->y()- y())<5 && qAbs(other->x() - x()) < 30;//只与地面僵尸碰撞
}
