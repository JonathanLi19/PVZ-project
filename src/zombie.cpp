#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
Zombie::Zombie()
{
    hp = 0;
    hurt = 0;
    speed = 0.0;
    state = 1;
    path_num = 0;
    nextpos_x=0;
    nextpos_y = 0;
}
Zombie::~Zombie()
{}
void Zombie::advance(int phase)
{
    if(!phase)
        return;
    if(state == 1)//如果在走路的话
    {
        if(qAbs(x() - 150 -nextpos_x)< 5 && qAbs(y() -nextpos_y)< 5)//如果到了下一个节点
        {
            Pathpoint* point = start_points[path_num];
            while(!(qAbs(point->pos.x() - x() + 150) < 5 && qAbs(point->pos.y() - y()) < 5))
            {
                point = point->nextpoint;
            }
            point = point->nextpoint;
            if(point != nullptr)
            {
                nextpos_x = point->pos.x();
                nextpos_y = point->pos.y();
            }
            if(point == nullptr)//到终点了
            {
                game_end_signal = 1;
                return;
            }
        }
        int width = nextpos_x - x() + 150;
        int height = nextpos_y - y();
        if(qAbs(width) < 5)
        {
            if(height>0)
                setY(y() + speed);
            else
                setY(y() - speed);
        }
        else if(qAbs(height) < 5)
        {
            setX(x() - speed);
        }
    }
    if(x()<150)
        game_end_signal = 1;
    //如果碰撞，那么就把state变成攻击,并且attack
    QList<QGraphicsItem *>  list = collidingItems();
    foreach(QGraphicsItem * item, list)//只攻击一个植物
    {
        if(item->type() == Plant::Type)//如果是植物
        {
            state = 2;//改成攻击模式
            Plant* plant = qgraphicsitem_cast<Plant*>(item);
            plant->hp -= hurt;
            if(plant->hp <= 0)
            {
                plant->~Plant();
                state = 1;//植物死去后继续恢复走路模式
            }
            break;
        }
    }
}
bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 30;
}
