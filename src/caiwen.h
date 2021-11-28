#ifndef CAIWEN_H
#define CAIWEN_H
#include"plant.h"
#include"zombie.h"
class CaiWen:public Plant
{
public:
    QRectF boundingRect() const override;
    CaiWen();
    ~CaiWen()override;
    void advance(int phase) override;
};
#endif // CAIWEN_H
