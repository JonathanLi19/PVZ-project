#ifndef ZOMBIE_H
#define ZOMBIE_H
#include<QGraphicsItem>
#include<QPainter>
#include<QList>
class Zombie:public QGraphicsItem
{
public:
    int hp;
    int hurt;
    double speed;
    int state;//在走还是在攻击
    int path_num;
    int nextpos_x;//下一个节点的坐标
    int nextpos_y;
    void advance(int phase) override;
    Zombie();
    ~Zombie()override;
    enum{Type = UserType + 2};
    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
};
extern int game_end_signal;
#endif // ZOMBIE_H
