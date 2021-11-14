#ifndef SHROOMBULLET_H
#define SHROOMBULLET_H
#include"plant.h"
#include"zombie.h"
#include<QGraphicsItem>
class shroombullet:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    shroombullet(int attack);
    ~shroombullet()override;
    void advance(int phase) override;
    int atk;
    qreal speed;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};
#endif // SHROOMBULLET_H
