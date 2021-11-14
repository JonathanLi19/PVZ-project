#ifndef SPIKEWEED_H
#define SPIKEWEED_H
#include"plant.h"
#include"zombie.h"
class Spikeweed:public Plant
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    Spikeweed();
    ~Spikeweed()override;
    void advance(int phase) override;
};
#endif // SPIKEWEED_H
