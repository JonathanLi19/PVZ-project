#include"zombie.h"
#include"plant.h"
#include"Pathpoint.h"
#include<QDebug>
#include<QGraphicsScene>
extern QGraphicsScene* scene2;
const int blood_length = 150;
const int blood_height = 20;
Zombie::Zombie()
{
    hp = 0;
    hurt = 0;
    speed = 0.0;
    state = 1;
    path_num = 0;
    nextpos_x=0;
    nextpos_y = 0;
    movie = nullptr;
    target = nullptr;
}
Zombie::~Zombie()
{
    delete movie;
}
bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 30;
}
void Zombie::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-30,-80,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-30,-80,rate*100,10);
    /*item->rate = rate;
    item->setPos(this->pos());
    scene2->addItem(item);*/
    movie->setSpeed(535);
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);

}
