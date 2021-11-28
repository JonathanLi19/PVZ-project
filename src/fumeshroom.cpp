#include"fumeshroom.h"
#include"shroombullet.h"
#include<QGraphicsScene>
extern QGraphicsScene* scene2;
QRectF FumeShroom::boundingRect() const
{
    return QRectF(-50, -80, 120, 120);
}
/*void FumeShroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    item->rate = rate;
    item->setPos(this->pos());
    scene2->addItem(item);
    QFont font;
    QString str;
    str.setNum(hp);
    font.setPixelSize(10);
    painter->setFont(font);
    painter->drawText(this->pos().x() - 50,this->pos().y()-50,str);
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}*/
FumeShroom::FumeShroom()
{
    hp = 20;
    total_hp = 20;
    hurt = 100;
    cost = 50;
    state = 1;
    plant_type = 1;//远战
    hold_back = 1000000;
    cur_hold = 0;
    counter = 0;
    attack_time = 100;
    setMovie("D:/QtProjects/images/Plants/FumeShroom/FumeShroom.gif");
}
FumeShroom::~FumeShroom()
{
}
void FumeShroom::advance(int phase)
{
    if(!phase)
        return;
    update();
    counter++;
    if(counter>=attack_time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
                    state = 2;
                    setMovie("D:/QtProjects/images/Plants/FumeShroom/FumeShroomAttack.gif");
              shroombullet *pea = new shroombullet(hurt);
              pea->setX(x() + 32);
              pea->setY(y());
              scene2->addItem(pea);
              return;
        }

    }
    else
    {
        if(state != 1)
        {
            state = 1;
            setMovie("D:/QtProjects/images/Plants/FumeShroom/FumeShroom.gif");
        }
    }
}
bool FumeShroom::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != Zombie::Type)
        return false;
    Zombie *zombie = (Zombie *)(other);
    return zombie->zombie_type == 0 && qAbs(other->y() - y()) < 5;
}
