#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include"plant.h"
#include"zombie.h"
//可以攻击飞行单位的远程植物
class PeaShooter:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    PeaShooter();
    ~PeaShooter()override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int counter;
};
extern const int attack_time;//豌豆攻击时间的间隔
#endif // PEASHOOTER_H
