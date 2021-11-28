#ifndef PLANT_RANGE_H
#define PLANT_RANGE_H
#include<QGraphicsItem>
#include<QPainter>
class plant_range:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    plant_range(QRectF size1);
    ~plant_range()override;
    QRectF size;
};
#endif // PLANT_RANGE_H
