#include"caiwen.h"
#include<QDebug>
QRectF CaiWen::boundingRect() const
{
    return QRectF(-50, -80, 120, 120);
}
CaiWen::CaiWen()
{
    hp = 150000;
    total_hp = 150000;
    hurt = 5000;
    cost = 50;
    state = 1;
    plant_type = 0;//近战
    hold_back = 1;//一次阻拦1个僵尸
    cur_hold = 0;
    counter =  0;
    attack_time = 10;
    setMovie("D:/QtProjects/images/Plants/Chomper/Chomper.gif");
}
CaiWen::~CaiWen()
{}
void CaiWen::advance(int phase)
{
    if(!phase)
        return;
    update();
    counter++;
    if(counter>=attack_time)
    {
        counter = 0;
        QList<QGraphicsItem *>  list = collidingItems();//Returns a list of all items that collide with this item.
        foreach(QGraphicsItem * item, list)//只攻击一个僵尸
        {
            if(item->type() == Zombie::Type)//如果是僵尸,写完之后把scene和view都变成全局的
            {

                Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
                if(zombie->zombie_type == 0)//只攻击地面僵尸
                {
                    state = 2;//改成攻击模式
                    setMovie("D:/QtProjects/images/Plants/Chomper/ChomperAttack.gif");
                    movie->setSpeed(200);
                    if(zombie->zombie_type == 1)//无法攻击飞行僵尸
                        return;
                    zombie->hp -= hurt;

                    if(zombie->hp <= 0)
                    {
                        state = 1;
                        setMovie("D:/QtProjects/images/Plants/Chomper/Chomper.gif");
                        //把这个zombie正在攻击的植物的attacklist更新
                        if(zombie->target != nullptr)
                        {

                            for(int i=0;i<zombie->target->zombies.size();i++)
                            {
                                if(zombie->target->zombies[i] == zombie)
                                {
                                    zombie->target->zombies.erase(zombie->target->zombies.begin()+i);

                                }
                            }
                        }
                    }

                    break;
                }
            }
        }
    }
}
