#ifndef PLANT_H
#define PLANT_H
#include<QGraphicsItem>
#include<QPainter>
#include<QMovie>
#include"zombie.h"
#include"plant_range.h"
#include<QGraphicsSceneMouseEvent>
using namespace std;
#define INITIAL_RESOURCE 1000
extern int CUR_SRC;
class Plant:public QGraphicsItem
{
public:
    int hp;
    int total_hp;
    int hurt;
    int cost;
    int state;//攻击还是静止
    int plant_type;//近战0还是远战1
    int hold_back;//阻拦数
    int cur_hold;//当前栏了几个
    int counter;
    int attack_time;
    vector<Zombie*> zombies;//记录攻击这个植物的zombie
    QString name;//植物名字
    QMovie* movie;
    plant_range* range;
    void attack();
    Plant();
    ~Plant()override;
    enum{Type = UserType + 1};
    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setMovie(QString path);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
};
#endif // PLANT_H
