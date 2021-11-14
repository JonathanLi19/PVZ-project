#include"dancingzombie.h"
#include"Pathpoint.h"
dancingzombie::dancingzombie(int path_num1)
{
    hp = 500;
    hurt = 100;
    state = 1;
    speed = 1.0;
    path_num = path_num1;
    zombie_type = 0;//陆地
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
}
void dancingzombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-70, -100, 140, 140),QImage("D:/QtProjects/images/Zombies/DancingZombie/DancingZombie.gif"));
}
QRectF dancingzombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
void dancingzombie::advance(int phase)
{
    if(!phase)
        return;
    if(state == 1)//如果在走路的话
    {
        if(MAP_NUM == "默认地图")
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
        else
        {
            if(qAbs(x() -nextpos_x)<= 5 && qAbs(y() -nextpos_y)<= 5)//如果到了下一个节点
            {
                //qDebug()<<nextpos_x<<nextpos_y;
                Pathpoint* point = start_points[path_num];
                while(!(qAbs(point->pos.x() - x()) <= 5 && qAbs(point->pos.y() - y()) <= 5))
                {
                    point = point->nextpoint;
                }
                point = point->nextpoint;
                if(point != nullptr)
                {
                    nextpos_x = point->pos.x();
                    nextpos_y = point->pos.y();
                }
                //qDebug()<<nextpos_x<<nextpos_y;
                if(point == nullptr)//到终点了
                {
                    game_end_signal = 1;
                    return;
                }
            }
            int width = nextpos_x - x();
            int height = nextpos_y - y();
            //qDebug()<<width<<height;
            if(qAbs(width) <= 5)
            {
                if(height>0)
                    setY(y() + speed);
                else
                    setY(y() - speed);
            }
            else if(qAbs(height) <= 5)
            {
                setX(x() - speed);
            }
          }
    }
/*if(x()<150 && MAP_NUM == "默认地图")
    game_end_signal = 1;*/
if(x()<0)
    game_end_signal = 1;
    //如果碰撞，那么就把state变成攻击,并且attack
    QList<QGraphicsItem *>  list = collidingItems();
    if(list.size()==0 && state == 2)
    {
        state = 1;
        return;
    }
    //qDebug()<<list;
    foreach(QGraphicsItem * item, list)//给所有范围之内的队友加生命,不攻击植物
    {
        if(item->type() == Zombie::Type)//如果是僵尸
        {
            state = 2;//改成攻击模式
            Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
            if(zombie->hp < 500)
                zombie->hp += hurt;
            state = 1;//加完buff之后恢复成走路模式
            qDebug()<<"yeah"<<zombie->hp;
            break;
        }
    }
}
bool dancingzombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 3 && qAbs(other->x() - x()) < 3;//攻击范围是一个正方形
}
