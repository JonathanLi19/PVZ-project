#include"normalzombie.h"
#include"Pathpoint.h"
normalZombie::normalZombie(int path_num1)
{
    hp = 1000;
    total_hp = 1000;
    hurt = 10;
    state = 1;
    speed = 3;//gif里速度为0.56
    path_num = path_num1;
    zombie_type = 0;//陆地
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
    setMovie("D:/QtProjects/images/Zombies/Zombie/Zombie.gif");
}
normalZombie::~normalZombie()
{
}
QRectF normalZombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
void normalZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state != 0)
        {
            state = 0;
            setMovie("D:/QtProjects/images/Zombies/Zombie/ZombieDie.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    if(state == 1)//如果在走路的话
    {
        //setMovie("D:/QtProjects/images/Zombies/Zombie/Zombie.gif");
        if(MAP_NUM == "默认地图")
        {
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
                if(point == nullptr)//到终点了
                {
                    game_end_signal = 1;
                    return;
                }
            }
            int width = nextpos_x - x();
            int height = nextpos_y - y();
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
    if(x()<0)
        game_end_signal = 1;
    //如果碰撞，那么就把state变成攻击,并且attack
    QList<QGraphicsItem *>  list = collidingItems();
    if(list.size()==0 && state == 2)
    {
        state = 1;
        setMovie("D:/QtProjects/images/Zombies/Zombie/Zombie.gif");
        return;
    }
    foreach(QGraphicsItem * item, list)//只攻击一个植物
    {
            if(item->type() == Plant::Type)//如果是植物
            {
                Plant* plant = qgraphicsitem_cast<Plant*>(item);
                if(plant->hold_back > plant->zombies.size() || plant->plant_type == 1)//攻击当前可以阻拦僵尸的植物
                {
                    if(state == 1)
                    {
                        state = 2;//改成攻击模式
                        setMovie("D:/QtProjects/images/Zombies/Zombie/ZombieAttack.gif");
                        movie->setSpeed(50);
                    }
                    target = plant;
                    bool attacking = false;
                    for(int i=0;i<plant->zombies.size();i++)
                    {
                        if(plant->zombies[i] == this)
                        {
                            attacking = true;
                            break;
                        }
                    }
                    if(!attacking)
                    {
                        plant->zombies.push_back(this);
                    }
                    plant->hp -= hurt;
                    if(plant->hp <= 0)
                    {
                        plant->~Plant();
                        target = nullptr;
                        state = 1;//植物死去后继续恢复走路模式
                        setMovie("D:/QtProjects/images/Zombies/Zombie/Zombie.gif");
                    }
                    break;
                }
            }
    }
}
