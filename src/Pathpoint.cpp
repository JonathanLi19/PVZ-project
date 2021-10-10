#include"Pathpoint.h"
vector<Pathpoint*> start_points;//存储一系列开始的节点
Pathpoint::Pathpoint(QPoint pos1)
{
    pos = pos1;
    nextpoint = nullptr;
}
Pathpoint::~Pathpoint()
{
}
