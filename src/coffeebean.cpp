#include"coffeebean.h"
#include"coffeebean_button.h"
#include"wallnut.h"
#include<QGraphicsScene>
using namespace std;
extern QGraphicsScene* scene2;
extern vector<pair<int,int>> jinzhan;
const int width1 = 150;const int height1 = 150;//自建以及新建地图每一个格子竖直高度和宽度
extern int ROW;extern int COL;//新建和默认的地图的行数和列数
QRectF CoffeeBean::boundingRect() const
{
    return QRectF(-50, -20, 120, 120);
}
//coffeebean等远程单位的攻击范围只能在mainwindow里画
void CoffeeBean::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    float rate = (float)hp/total_hp;
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-30,-20,100,10);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(-30,-20,rate*100,10);
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}
CoffeeBean::CoffeeBean()
{
    hp = 50;
    total_hp = 50;
    hurt = 0;
    cost = 100;
    state = 1;
    plant_type = 1;//远战
    hold_back = 10000000;
    cur_hold = 0;
    counter = 0;
    attack_time = 100;
    name = "coffeebean";
    prefer = 1;//默认从后到前
    setMovie("D:/QtProjects/images/Plants/CoffeeBean/CoffeeBean.gif");
}
CoffeeBean::~CoffeeBean()
{
}
void CoffeeBean::advance(int phase)
{
//根据prefer安放坚果墙
    if(!phase)
        return;
    update();
    if(hp<=0)
    {
        delete this;
        return;
    }
    //要加坚果需要满足：那格子在规定范围，那个格子是近战的，那个格子上没有植物
    QTransform transform;
    static int counter = 0;
    counter++;
    if(counter>=attack_time)//默认时间间隔为100
    {
        counter = 0;
        int i1[3] = {-1,0,1};
        int j1[3] = {-1,0,1};
        int x = 0;int y = 0;
        int i = 0;int j = 0;
        if(prefer == 0)
        {
            for(int k=0;k<3;k++)
            {
                i = i1[k];
                for(int z=0;z<3;z++)
                {
                    j = j1[z];
                    x = this->pos().x()+i*width1;y = this->pos().y()+j*height1;
                    if(could_place_potato(x,y))
                        break;
                }
                if(could_place_potato(x,y))
                    break;
            }
            bool flag = could_place_potato(x,y);
            if(flag == true)
            {
                Plant* plant = new wallnut;
                plant->setPos(x,y);
                scene2->addItem(plant);
            }
        }
        else
        {
            for(int k=2;k>=0;k--)
            {
                i = i1[k];
                for(int z=0;z<3;z++)
                {
                    j = j1[z];
                    x = this->pos().x()+i*width1;y = this->pos().y()+j*height1;
                    if(could_place_potato(x,y))
                        break;
                }
                if(could_place_potato(x,y))
                    break;
            }
            bool flag = could_place_potato(x,y);
            if(flag == true)
            {
                Plant* plant = new wallnut;
                plant->setPos(x,y);
                scene2->addItem(plant);
            }
        }
   }
}
bool CoffeeBean::could_place_potato(int x,int y)
{
    int start_x = 100; int start_y = 150;//自建以及默认地图格子左上角的坐标
    QTransform transform;
    bool flag = true;//是否满足加坚果的条件

        int i=0;int j=0;
        for(;i<COL;i++)
        {
            if(x>=start_x+width1*i && x<start_x+width1*(i+1))
            {
                x = start_x+width1*i+width1/2;
                break;
            }
        }
        for(;j<ROW;j++)
        {
            if(y>=start_y+j*height1 && y<start_y+height1*(j+1))
            {
                y = start_y+j*height1+height1/2;
                break;
            }
        }
        if(i==9 || j==5)
            flag = false;
            int k=0;
            for(;k<jinzhan.size();k++)
            {
                if(j==jinzhan[k].first && i == jinzhan[k].second)
                {
                    break;
                }
            }
            if(k==jinzhan.size())
                flag = false;
            if(!(scene2->itemAt(x,y,transform)==NULL || scene2->itemAt(x,y,transform)->type() != Plant::Type))
                flag = false;
            return flag;
}
void CoffeeBean::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        coffeebean_button* button1 = new coffeebean_button(QString("从后到前"),this);
        coffeebean_button* button2 = new coffeebean_button(QString("从前到后"),this);
        button1->setPos(this->pos().x()-50,this->pos().y());
        button2->setPos(this->pos().x()+50,this->pos().y());
        scene2->addItem(button1);
        scene2->addItem(button2);
    }
}
