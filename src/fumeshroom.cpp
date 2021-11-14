#include"fumeshroom.h"
#include"shroombullet.h"
#include<QGraphicsScene>
extern QGraphicsScene* scene2;
const int attack_time1 = 50;
QRectF FumeShroom::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}
void FumeShroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -50, 100, 100),QImage("D:/QtProjects/images/Plants/FumeShroom/FumeShroom.gif"));
}
FumeShroom::FumeShroom()
{
    hp = 20;
    hurt = 100;
    cost = 50;
    state = 1;
    plant_type = 1;//远战
    hold_back = 0;//一次阻拦0个僵尸
    cur_hold = 0;
    counter = 0;
}
FumeShroom::~FumeShroom()
{}
void FumeShroom::advance(int phase)
{
    if(!phase)
        return;
    counter++;
    if(counter>=attack_time1)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
              shroombullet *pea = new shroombullet(hurt);
              pea->setX(x() + 32);
              pea->setY(y());
              scene2->addItem(pea);
              return;
        }

    }
}
bool FumeShroom::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != Zombie::Type)
        return false;
    Zombie *zombie = (Zombie *)(other);
    return zombie->zombie_type == 0 && qAbs(other->y() - y()) < 5 && qAbs(other->x() - x()) < 1800;
}
