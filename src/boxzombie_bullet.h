#ifndef BOXZOMBIE_BULLET_H
#define BOXZOMBIE_BULLET_H
#include"plant.h"
#include"zombie.h"
#include<QGraphicsItem>
class boxzombie_bullet:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    boxzombie_bullet(int attack,QPointF dest1,Zombie* parent1,QPointF start1);
    ~boxzombie_bullet()override;
    void advance(int phase) override;
    int atk;
    qreal speed;
    QPointF start;
    QPointF dest;
    Zombie* parent;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};
#endif // BOXZOMBIE_BULLET_H
