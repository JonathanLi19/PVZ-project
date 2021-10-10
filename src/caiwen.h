#ifndef CAIWEN_H
#define CAIWEN_H
#include"plant.h"
class CaiWen:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    CaiWen();
    ~CaiWen()override;
};
#endif // CAIWEN_H
