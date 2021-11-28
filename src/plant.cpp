#include"plant.h"
#include"zombie.h"
#include<QGraphicsScene>
#include<QDebug>
extern QGraphicsScene* scene2;
int CUR_SRC = INITIAL_RESOURCE;
Plant::Plant()
{
    hp = 0;
    total_hp = 0;
    hurt = 0;
    cost = 0;
    state = 1;//静止
    hold_back = 100000;
    cur_hold = 0;
    name = "不是coffeebean";
    movie = nullptr;
    counter = 0;
    attack_time = 0;
    range = nullptr;
}
Plant::~Plant()
{
    delete movie;
    delete range;
}
void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-30,-80,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-30,-80,rate*100,10);
    /*painter->setPen(QPen(Qt::yellow,1));
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawRect(-15,-15,30,30);*/
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}
bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 30;
}
void Plant::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
void Plant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(plant_type == 0)//近战
            range = new plant_range(this->boundingRect());
        else if(name != "coffeebean")
        {
            QRectF a(-30,-45,1800-this->pos().x(),90);
            range = new plant_range(a);
        }
        else
        {
            QRectF a(-225, -225, 450, 450);
            range = new plant_range(a);

        }
        range->setPos(this->pos());
        scene2->addItem(range);
    }
}
void Plant::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(range != nullptr)
            delete range;
    }
}
