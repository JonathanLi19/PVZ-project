#include"card.h"
QString now_plant;//现在要被安放的植物
int put_signal = 0;
const QMap<QString, int> card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},
                                      {"Chomper", 4}, {"PotatoMine", 5}, {"Repeater", 6}};

const QVector<QString> card::name = {"SunFlower", "Peashooter", "CherryBomb", "WallNut",
                                     "Chomper", "PotatoMine", "Repeater"};
//价格
const QVector<int> card::cost = {50, 100, 150, 50, 50, 25, 200};
void card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-35, -55, 70, 100),QImage("D:/QtProjects/images/card.png"));
    painter->drawPixmap(QRect(-35, -55, 80, 80), QPixmap("D:/QtProjects/images/Plants/" + text +"/"+text+ ".gif"));
    QFont font;
    font.setPointSizeF(10);
    painter->setFont(font);
    painter->drawText(-40, 45, QString().sprintf("%3d", cost[map[text]]));
}
QRectF card::boundingRect() const
{
    return QRectF(-35, -65, 70, 100);
}
card::card(QString s)
{
    text = s;//文本内容（用于图片文件名）
}
void card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        now_plant = text;
        put_signal = 1;
    }
}
