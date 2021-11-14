#include"Boxzombie.h"
#include"Pathpoint.h"
boxzombie::boxzombie(int path_num1)
{
    hp = 500;
    hurt = 10;
    state = 1;
    speed = 5.0;
    path_num = path_num1;
    zombie_type = 0;//陆地
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
}
void boxzombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-70, -100, 140, 140),QImage("D:/QtProjects/images/Zombies/JackinTheBoxZombie/0.gif"));
}
QRectF boxzombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
void boxzombie::advance(int phase)
{
    if(!phase)
        return;
if(state == 1)//如果在走路的话
{
    if(MAP_NUM == "默认地图")
    {
        qDebug()<<nextpos_x<<nextpos_y<<x()<<y();
        if(qAbs(x() -nextpos_x)< 5 && qAbs(y() -nextpos_y)< 5)//如果到了下一个节点
        {
            Pathpoint* point = start_points[path_num];
            while(!(qAbs(point->pos.x() - x()) < 5 && qAbs(point->pos.y() - y()) < 5))
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
        int width = nextpos_x - x();
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
    foreach(QGraphicsItem * item, list)//只攻击一个植物
    {
        if(item->type() == Plant::Type)//如果是植物
        {
            Plant* plant = qgraphicsitem_cast<Plant*>(item);
            if(plant->hold_back > 0 || plant->plant_type == 1)//不打地刺
            {
                state = 2;//改成攻击模式
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
}
bool boxzombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y() - y()) < 150 && qAbs(other->x() - x()) < 150;//攻击范围是一个正方形，边长是300
}
