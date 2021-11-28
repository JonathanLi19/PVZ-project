#include"Boxzombie.h"
#include"Pathpoint.h"
#include"boxzombie_bullet.h"
#include<QGraphicsScene>
extern QGraphicsScene* scene2;
boxzombie::boxzombie(int path_num1)
{
    hp = 500;
    total_hp = 500;
    hurt = 100;
    state = 1;
    speed = 5.0;
    path_num = path_num1;
    zombie_type = 0;//陆地
    target = nullptr;
    counter = 0;
    attack_time = 10;
    nextpos_x = start_points[path_num1]->nextpoint->pos.x();
    nextpos_y = start_points[path_num1]->nextpoint->pos.y();
    setMovie("D:/QtProjects/images/Zombies/JackinTheBoxZombie/Walk.gif");
}
QRectF boxzombie::boundingRect() const
{
    return QRectF(-70, -100, 140, 140);
}
void boxzombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state != 0)
        {
            state = 0;
            setMovie("D:/QtProjects/images/Zombies/JackinTheBoxZombie/Die.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    if(state == 1)//如果在走路的话
    {
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
        setMovie("D:/QtProjects/images/Zombies/JackinTheBoxZombie/Walk.gif");
        return;
    }
    if(list.size()==0)
        target = nullptr;
    counter++;
    if(counter>=attack_time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
            foreach(QGraphicsItem * item, list)//只攻击一个植物
            {
                    if(item->type() == Plant::Type)//如果是植物
                    {
                        Plant* plant = qgraphicsitem_cast<Plant*>(item);
                        bool flag = false;
                        for(int i=0;i<plant->zombies.size();i++)
                        {
                            if(plant->zombies[i] == this)
                            {
                                flag = true;
                                break;
                            }
                        }
                        if(plant->hold_back > plant->zombies.size() || flag)
                        {
                            if(state == 1)
                            {
                                state = 2;//改成攻击模式
                                setMovie("D:/QtProjects/images/Zombies/JackinTheBoxZombie/Attack.gif");
                                movie->setSpeed(25);
                            }
                            target = plant;
                            boxzombie_bullet *pea = new boxzombie_bullet(hurt,target->pos(),this,this->pos());
                            pea->setX(x() - 32);
                            pea->setY(y());
                            scene2->addItem(pea);
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
                            return;
                        }
                    }
            }

        }

    }
}
bool boxzombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y() - y()) < 150 && qAbs(other->x() - x()) < 150;//攻击范围是一个正方形，边长是300
}
void boxzombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        Q_UNUSED(option)
        Q_UNUSED(widget)
        float rate = (float)hp/total_hp;
        painter->setPen(QPen(Qt::black,1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(-30,-80,100,10);
        painter->setBrush(QBrush(Qt::green));
        painter->drawRect(-30,-80,rate*100,10);
        movie->setSpeed(535);
        QImage image = movie->currentImage();
        painter->drawImage(boundingRect(), image);

}
boxzombie::~boxzombie()
{
}
