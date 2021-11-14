#include"spikeweed.h"
QRectF Spikeweed::boundingRect() const
{
    return QRectF(-70, 20, 140, 50);
}
void Spikeweed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-70, 20, 140, 50),QImage("D:/QtProjects/images/Plants/Spikeweed/Spikeweed.gif"));
}
Spikeweed::Spikeweed()
{
    hp = 100;
    hurt = 500;
    cost = 150;
    state = 1;
    plant_type = 0;//近战
    hold_back = 0;
}
Spikeweed::~Spikeweed()
{}
void Spikeweed::advance(int phase)
{
    if(!phase)
        return;
    QList<QGraphicsItem *>  list = collidingItems();//Returns a list of all items that collide with this item.
    foreach(QGraphicsItem * item, list)//只攻击一个僵尸
    {
        if(item->type() == Zombie::Type)//如果是僵尸,写完之后把scene和view都变成全局的
        {
            state = 2;//改成攻击模式
            Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
            if(zombie->zombie_type == 1)//无法攻击飞行僵尸
                return;
            zombie->hp -= hurt;
            if(zombie->hp <= 0)
            {
                zombie->~Zombie();
                state = 1;//恢复静止
            }
            break;
        }
    }
}
