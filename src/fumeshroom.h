#ifndef FUMESHROOM_H
#define FUMESHROOM_H
#include"plant.h"
#include"zombie.h"
#include"distant_bleed.h"
//只打地面的远程攻击植物
class FumeShroom:public Plant
{
public:
    QRectF boundingRect() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    FumeShroom();
    ~FumeShroom()override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    //distant_bleed* item;
};
#endif // FUMESHROOM_H
