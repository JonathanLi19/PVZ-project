#ifndef COFFEEBEAN_BUTTON_H
#define COFFEEBEAN_BUTTON_H
#include<QGraphicsItem>
#include<QPainter>
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QFont>
#include"coffeebean.h"
class coffeebean_button:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QString text;
    coffeebean_button(QString s,CoffeeBean* parent);
    ~coffeebean_button()override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    CoffeeBean* parent;
};
#endif // COFFEEBEAN_BUTTON_H
