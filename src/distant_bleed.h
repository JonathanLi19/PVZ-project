#ifndef DISTANT_BLEED_H
#define DISTANT_BLEED_H
#include<QGraphicsItem>
#include<QPainter>
class distant_bleed:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    distant_bleed();
    ~distant_bleed()override;
    double rate;
};
#endif // DISTANT_BLEED_H
