#ifndef PEA_H
#define PEA_H
#include"plant.h"
#include"zombie.h"
#include<QGraphicsItem>
class Pea:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    Pea(int attack);
    ~Pea()override;
    void advance(int phase) override;
    //bool snow;
    int atk;
    qreal speed;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};
#endif // PEA_H
