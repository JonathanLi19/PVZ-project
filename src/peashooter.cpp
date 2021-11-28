#include"peashooter.h"
#include"Pea.h"
#include<QGraphicsScene>
#include<QDebug>
extern QGraphicsScene* scene2;
QRectF PeaShooter::boundingRect() const
{
    return QRectF(-50, -80, 120, 120);
}
PeaShooter::PeaShooter()
{
    hp = 100;
    total_hp = 100;
    hurt = 100;
    cost = 100;
    state = 1;
    plant_type = 1;//远战
    hold_back = 1000000;
    counter = 0;
    attack_time = 100;
    setMovie("D:/QtProjects/images/Plants/Peashooter/Peashooter.gif");
}
PeaShooter::~PeaShooter()
{}
void PeaShooter::advance(int phase)
{
    if(!phase)
        return;
    update();
    counter++;
    if(counter>=attack_time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
              Pea *pea = new Pea(hurt);
              pea->setX(x() + 32);
              pea->setY(y());
              scene2->addItem(pea);
              return;
        }

    }
}
bool PeaShooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    //向前方攻击
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 5;
}
