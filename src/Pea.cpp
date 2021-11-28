#include"Pea.h"
QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 40, 20);
}
void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-12, -28, 40, 20),QImage("D:/QtProjects/images/Plants/PB00.gif"));
}
Pea::Pea(int attack)
{
    atk = attack;
    speed = 360.0 * 33 / 500;
}
Pea::~Pea()
{}
void Pea::advance(int phase)
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
               if(zombie->target != nullptr)
               {
                   for(int i=0;i<zombie->target->zombies.size();i++)
                   {
                       if(zombie->target->zombies[i] == zombie)
                       {
                           zombie->target->zombies.erase(zombie->target->zombies.begin()+i);
                           break;
                       }
                   }
               }
           }
           delete this;
           return;
    }
    //飞离画面？
    setX(x() + speed);
    if(x()>1800)
        delete this;
}
bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y()- y())<5 && qAbs(other->x() - x()) < 30;
}
