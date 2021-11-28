#include"coffeebean_button.h"
#include<QList>
#include<QGraphicsScene>
extern QGraphicsScene* scene2;
void coffeebean_button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-25, -25, 50, 50),QImage("D:/QtProjects/images/button.png"));
    QFont font;//设置字体
    font.setPointSizeF(5);
    painter->setFont(font);
    painter->setPen(QPen(Qt::red,1));
    painter->drawText(-20,10,text);
}
QRectF coffeebean_button::boundingRect() const
{
    return QRectF(-25, -25, 50, 50);
}
coffeebean_button::coffeebean_button(QString s,CoffeeBean* parent1)
{
    text = s;//文本内容（用于图片文件名）
    parent = parent1;
}
void coffeebean_button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //删除所有button,并且设置这个coffeebean的偏好
        if(text == "从后到前")
            parent->prefer = 0;
        else
            parent->prefer = 1;
        QList<QGraphicsItem*> list = scene2->items();
        foreach(QGraphicsItem* item,list)
        {
            QRectF a(-25, -25, 50, 50);
            if(item->boundingRect() == a)
            {
                delete item;
            }
        }
    }
}
coffeebean_button::~coffeebean_button()
{
}
