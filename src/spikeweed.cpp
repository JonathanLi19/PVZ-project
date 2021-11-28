#include"spikeweed.h"
QRectF Spikeweed::boundingRect() const
{
    return QRectF(-70, 20, 140, 50);
}
Spikeweed::Spikeweed()
{
    hp = 100;
    total_hp = 100;
    hurt = 50;
    cost = 150;
    state = 1;
    plant_type = 0;//近战
    hold_back = 0;
    cur_hold = 0;
    counter =  0;
    attack_time = 10;
    setMovie("D:/QtProjects/images/Plants/Spikeweed/Spikeweed.gif");
}
Spikeweed::~Spikeweed()
{}
void Spikeweed::advance(int phase)
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
                state = 2;//改成攻击模式
                Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
                if(zombie->zombie_type == 1)//无法攻击飞行僵尸
                    return;
                zombie->hp -= hurt;
                if(zombie->hp <= 0)
                {
                    state = 1;//恢复静止
                    if(zombie->target != nullptr)
                    {
                        for(int i=0;i<zombie->target->zombies.size();i++)
                        {
                            if(zombie->target->zombies[i] == zombie)
                            {
                                zombie->target->zombies.erase(zombie->target->zombies.begin()+i);
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}
void Spikeweed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-50,20,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-50,20,rate*100,10);
    /*painter->setPen(QPen(Qt::yellow,1));
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawRect(-15,20,30,30);*/
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}
