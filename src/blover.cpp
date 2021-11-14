#include"blover.h"
QRectF Blover::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}
void Blover::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -50, 100, 100),QImage("D:/QtProjects/images/Plants/Blover/Blover.gif"));
}
Blover::Blover()
{
    hp = 2000000;
    hurt = 1000000;
    cost = 50;
    state = 1;
    plant_type = 0;//近战
    hold_back = 1;//一次阻拦1个僵尸
    cur_hold = 0;
}
Blover::~Blover()
{}
void Blover::advance(int phase)
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
            zombie->hp -= hurt;
            //qDebug()<<zombie->hp;
            if(zombie->hp <= 0)
            {
                zombie->~Zombie();
                state = 1;//恢复静止
            }
            break;
        }
    }

}
