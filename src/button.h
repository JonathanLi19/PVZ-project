#ifndef BUTTON_H
#define BUTTON_H
#include<QGraphicsItem>
#include<QPainter>
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QFont>
class button:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QString text;//地图编号
    button(QString s);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};
extern QString MAP_NUM;
#endif // BUTTON_H
