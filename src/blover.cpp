#include"blover.h"
#include<QDebug>
QRectF Blover::boundingRect() const
{
    return QRectF(-50, -80, 120, 120);
}
Blover::Blover()
{
    hp = 2000;
    total_hp = 2000;
    hurt = 100000000;
    cost = 50;
    state = 1;
    plant_type = 0;//近战
    hold_back = 1;//一次阻拦1个僵尸
    cur_hold = 0;
    counter =  0;
    attack_time = 50;
    setMovie("D:/QtProjects/images/Plants/Blover/Blover.gif");
}
Blover::~Blover()
{}
void Blover::advance(int phase)
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
                setMovie("D:/QtProjects/images/Plants/Blover/0.gif");
                Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
                zombie->hp -= hurt;
                qDebug()<<"yeah"<<zombie->hp;
                if(zombie->hp <= 0)
                {
                    state = 1;
                    setMovie("D:/QtProjects/images/Plants/Blover/Blover.gif");
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
/*void Blover::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-30,-80,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-30,-80,rate*100,10);
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}*/
