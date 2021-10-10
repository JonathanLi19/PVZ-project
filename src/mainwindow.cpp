#include"mainwindow.h"
#include"zombie.h"
#include"plant.h"
#include<QDebug>
#include"normalzombie.h"
#include"caiwen.h"
int MainWindow::ZOMBIE_GEN_TIMES_NOW=0;
int now_plantpos_x = 0;
int now_plantpos_y = 0;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    life = 10;
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150,0,1800,1000);
    view = new QGraphicsView(scene,this);
    view->resize(1802,1002);//为啥要+2？？
    view->setRenderHint(QPainter::Antialiasing);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//If your scene uses many animations and you are experiencing slowness, you can disable indexing by calling setItemIndexMethod(NoIndex).
    scene->setBackgroundBrush(QPixmap("D:/QtProjects/images/background5.png"));
    addPaths();addShop();addCard();
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);//为啥不用多线程的就不行
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    timer->start(50);   
    view->show();
}
MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete timer;
}
void MainWindow::check()
{
    if(game_end_signal == 1)
    {
        timer->stop();
        QList<QGraphicsItem*>list = scene->items();
        foreach(QGraphicsItem* item, list)
        {
            scene->removeItem(item);
        }
        //删除scene中所有item
        QGraphicsScene* scene1 = new QGraphicsScene(this);
        scene1->setSceneRect(0,0,560,480);
        scene1->setBackgroundBrush(QPixmap("D:/QtProjects/images/Lose.png"));
        view->resize(562,482);
        view->setScene(scene1);
    }
    if(ZOMBIE_GEN_TIMES_NOW == ZOMBIE_TOTAL)
    {
        bool flag = true;//所有僵尸都被打死了
        QList<QGraphicsItem*>list = scene->items();
        foreach(QGraphicsItem* item, list)
        {
            if(item->type() == Zombie::Type)
            {
                flag = false;
                break;
            }
        }
        if(flag == true)
        {
            foreach(QGraphicsItem* item, list)
            {
                scene->removeItem(item);
            }
            QGraphicsScene* scene1 = new QGraphicsScene(this);
            scene1->setBackgroundBrush(QPixmap("D:/QtProjects/images/interface/trophy.png"));
            view->setScene(scene1);
        }
    }
    QList<QGraphicsItem*>list = scene->items();
    foreach(QGraphicsItem* item, list)
    {
        if(item->type() == QGraphicsTextItem::Type)
        {
            scene->removeItem(item);
            break;
        }
    }
    QString cur_src = QString::number(CUR_SRC);
    QGraphicsTextItem *txtitem = new QGraphicsTextItem(cur_src);
    txtitem->setPos(450,75);
    scene->addItem(txtitem);
}
void MainWindow::addZombie()
{
    static int time = GEN_ONE_TIME;
    static int counter = 0;
    if(ZOMBIE_GEN_TIMES_NOW < ZOMBIE_TOTAL)
    {
        counter++;
        if(counter>=time)
        {

            int i = qrand() % start_points.size();
            normalZombie* zombie = new normalZombie(i);
            //unsigned int i = qrand() % 5;
            zombie->setPos(1628, start_points[i]->pos.y());
            scene->addItem(zombie);
            ZOMBIE_GEN_TIMES_NOW++;
            counter = 0;
        }
    }
    else
        return;
}
void MainWindow::addPlant()
{
    QTransform transform;
    Plant* plant;
    int type;
    if(now_plant == "Chomper")
        type = 1;
    if(type == 1)
        plant = new CaiWen;
    if(CUR_SRC >= plant->cost && (scene->itemAt(now_plantpos_x,now_plantpos_y,transform) == nullptr || scene->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == Zombie::Type || scene->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == QGraphicsRectItem::Type || scene->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == QGraphicsLineItem::Type))//默认不能一个格子放两个植物
    {//注意：我现在这里没法放植物，因为我这里绘画格子之后，itemAt返回值不是nullptr了
        plant->setPos(now_plantpos_x,now_plantpos_y);
        scene->addItem(plant);
        CUR_SRC -= plant->cost;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        int x = pos.x();int y = pos.y();
        int i=0;int j=0;
        for(;i<9;i++)
        {
            if(x>=290+140*i && x<290+140*(i+1))
            {
                x = 290+140*i+70;
                break;
            }
        }
        for(;j<5;j++)
        {
            if(y>=140+j*165 && y<140+165*(j+1))
            {
                y = 140+j*165+82;
                break;
            }
        }
        x = x+150;

        //addPlant(1,x,y);//第一个是植物种类，第二个是放在scene的哪个位置
        qDebug()<<event->pos();
        if(i==9 || j==5)
            return;
        now_plantpos_x = x;
        now_plantpos_y = y;
        if(put_signal == 1)
        {
            addPlant();
            put_signal = 0;
        }
    }
}
void MainWindow::addPaths()
{
    Pathpoint* point1 = new Pathpoint(QPoint(1540,230));
    Pathpoint* point2 = new Pathpoint(QPoint(920,230));
    Pathpoint* point3 = new Pathpoint(QPoint(920,390));
    Pathpoint* point4 = new Pathpoint(QPoint(150,390));
    point1->nextpoint = point2;
    point2->nextpoint = point3;
    point3->nextpoint = point4;
    point4->nextpoint = nullptr;
    start_points.push_back(point1);
    int x1 = point1->pos.x()+150;int x2 = point2->pos.x()+150; int y1 = point1->pos.y();int y2 = point2->pos.y();
    int x3 = point3->pos.x()+150; int y3 = point3->pos.y();
    int x4 = point4->pos.x()+150; int y4 = point4->pos.y();
    scene->addLine(x1,y1,x2,y2);
    scene->addLine(x2,y2,x3,y3);
    scene->addLine(x3,y3,x4,y4);
    scene->addRect(x1-4,y1-4,8,8);
    scene->addRect(x2-4,y2-4,8,8);
    scene->addRect(x3-4,y3-4,8,8);
    scene->addRect(x4-4,y4-4,8,8);
}
void MainWindow::addShop()
{
    shop* shop1 = new shop;
    shop1->setPos(600,30);
    scene->addItem(shop1);
}
void MainWindow::addCard()
{
    card* card1 = new card("Chomper");
    card1->setPos(575,60);//这个是基于本来的图片的坐标，需要加150，变成场景中的坐标
    scene->addItem(card1);
}
