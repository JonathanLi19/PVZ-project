#include"balloonzombie.h"
#include"Pathpoint.h"
balloonzombie::balloonzombie(int path_num1)
{
    hp = 200;
    hurt = 10;
    state = 1;
    speed = 1.0;
    path_num = path_num1;
    zombie_type = 1;//飞行
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
}
void balloonzombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-70, -100, 140, 140),QImage("D:/QtProjects/images/balloonzombie.png"));
}
QRectF balloonzombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
void balloonzombie::advance(int phase)
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
    foreach(QGraphicsItem * item, list)//只攻击一个植物
    {
        if(item->type() == Plant::Type)//如果是植物
        {
            Plant* plant = qgraphicsitem_cast<Plant*>(item);
            if(plant->hold_back >plant->cur_hold)//攻击当前可以阻拦僵尸的植物
            {
                plant->cur_hold++;
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
bool balloonzombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 30;//攻击范围是一个正方形，边长是300
}
balloonzombie::~balloonzombie()
{}
