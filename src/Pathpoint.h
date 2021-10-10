#ifndef PATHPOINT_H
#define PATHPOINT_H
#include<QGraphicsItem>
#include<vector>
#include<QPainter>
using namespace std;
class Pathpoint
{
public:
    QPoint pos;
    Pathpoint* nextpoint;//指向下一个point
    Pathpoint(QPoint pos);
    ~Pathpoint();
};
extern vector<Pathpoint*> start_points;
#endif // PATHPOINT_H
