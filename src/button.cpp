#include"button.h"
void button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-250, -100, 500, 200),QImage("D:/QtProjects/images/button.png"));
    QFont font;//设置字体
    font.setPointSizeF(40);
    painter->setFont(font);
    painter->drawText(-200,30,text);
}
QRectF button::boundingRect() const
{
    return QRectF(-250, -100, 500, 200);
}
button::button(QString s)
{
    text = s;//文本内容（用于图片文件名）
}
void button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        MAP_NUM = text;
    }
}
