#ifndef CARD_H
#define CARD_H
#include<QGraphicsItem>
#include<QPainter>
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QFont>
class card:public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QString text;//植物种类
    card(QString s);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    const static QMap<QString, int> map;
    const static QVector<QString> name;
    const static QVector<int> cost;
};
extern QString now_plant;//现在被安放的植物
extern int put_signal;
#endif // CARD_H
