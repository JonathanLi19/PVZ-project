#include"plant.h"
#include"zombie.h"
int CUR_SRC = INITIAL_RESOURCE;
Plant::Plant()
{
    hp = 0;//project1的近战菜花
    hurt = 0;
    cost = 0;
    state = 1;//静止
}
Plant::~Plant()
{}
void Plant::advance(int phase)
{
    if(!phase)
        return;
    QList<QGraphicsItem *>  list = collidingItems();//Returns a list of all items that collide with this item.
    foreach(QGraphicsItem * item, list)//只攻击一个植物
    {
        if(item->type() == Zombie::Type)//如果是僵尸,写完之后把scene和view都变成全局的
        {
            state = 2;//改成攻击模式
            Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
            zombie->hp -= hurt;
            if(zombie->hp <= 0)
            {
                zombie->~Zombie();
                state = 1;//恢复静止
            }
            break;
        }
    }
}
bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 30;
}
