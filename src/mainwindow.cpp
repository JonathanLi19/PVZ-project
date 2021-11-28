#include"mainwindow.h"
QGraphicsScene* scene2 = NULL;
int MainWindow::ZOMBIE_GEN_TIMES_NOW=0;
int now_plantpos_x = 0;
int now_plantpos_y = 0;
QString MAP_NUM;//选择第几个地图
const int start_x = 100; const int start_y = 150;//自建以及默认地图格子左上角的坐标
const int width1 = 150;const int height1 = 150;//自建以及新建地图每一个格子竖直高度和宽度
int ROW;int COL;//新建和默认的地图的行数和列数
vector<pair<int,int>> jinzhan;
vector<pair<int,int>> distant;//存放了自建地图的近战和远战的格子
vector<int> paths_type;//地图每条路径的种类
//别忘了在默认地图中paint出这两种格子！
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    choose();
}
void MainWindow::choose()//显示出第一步的界面
{
    timer = new QTimer;
    QGraphicsScene* scene1 = new QGraphicsScene(this);
    scene1->setSceneRect(0,0,1800,1200);
    view = new QGraphicsView(scene1,this);
    view->resize(1802,1202);//为啥要+2？？
    view->setRenderHint(QPainter::Antialiasing);
    scene1->setItemIndexMethod(QGraphicsScene::NoIndex);//If your scene uses many animations and you are experiencing slowness, you can disable indexing by calling setItemIndexMethod(NoIndex).
    scene1->setBackgroundBrush(QPixmap("D:/QtProjects/images/surface1.png"));
    button* button1 = new button("默认地图");
    button1->setPos(1305,250);//这个是基于本来的图片的坐标，需要加150，变成场景中的坐标
    scene1->addItem(button1);
    button* button2 = new button("自建地图");
    button2->setPos(1305,500);//这个是基于本来的图片的坐标，需要加150，变成场景中的坐标
    scene1->addItem(button2);
    connect(timer, &QTimer::timeout, this, &MainWindow::showmap);
    timer->start(50);
    view->show();
}
void MainWindow::showmap()
{
    if(MAP_NUM == "默认地图")
    {
        /*life = 10;
        timer->stop();
        timer = new QTimer;
        scene = new QGraphicsScene(this);
        scene->setSceneRect(150,0,1800,1000);
        view->setScene(scene);
        view->resize(1802,1002);//为啥要+2？？
        view->setRenderHint(QPainter::Antialiasing);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);//If your scene uses many animations and you are experiencing slowness, you can disable indexing by calling setItemIndexMethod(NoIndex).
        scene->setBackgroundBrush(QPixmap("D:/QtProjects/images/background5.png"));
        addPaths_default();addShop();addCard();//addButton();
        connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);//为啥不用多线程的就不行
        connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
        connect(timer, &QTimer::timeout, this, &MainWindow::check);
        timer->start(50);
        view->show();*/
        life = 10;
        timer->stop();
        timer = new QTimer;
        scene2 = new QGraphicsScene(this);
        scene2->setSceneRect(0,0,1800,1000);
        view->setScene(scene2);
        view->resize(1802,1002);//为啥要+2？？
        view->setRenderHint(QPainter::Antialiasing);
        scene2->setItemIndexMethod(QGraphicsScene::NoIndex);
        ROW = 5;COL = 9;
        for(int i=0;i<=ROW;i++)
        {
            scene2->addLine(start_x,start_y+i*height1,COL*width1+start_x,start_y+i*height1);
        }

        for(int i=0;i<=COL;i++)
        {
            scene2->addLine(start_x+i*width1,start_y,start_x+i*width1,start_y+ROW*height1);
        }
        addPaths_default(); addShop();addCard();
        connect(timer, &QTimer::timeout, scene2, &QGraphicsScene::advance);//为啥不用多线程的就不行
        connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
        connect(timer, &QTimer::timeout, this, &MainWindow::check);
        timer->start(50);
        view->show();
    }
    else if(MAP_NUM == "自建地图")
    {
        //从指定的地址读取自建的地图的信息，然后设置新的地图

        life = 10;
        timer->stop();
        timer = new QTimer;
        scene2 = new QGraphicsScene(this);
        scene2->setSceneRect(0,0,1800,1000);
        view->setScene(scene2);
        view->resize(1802,1002);//为啥要+2？？
        view->setRenderHint(QPainter::Antialiasing);
        scene2->setItemIndexMethod(QGraphicsScene::NoIndex);//If your scene uses many animations and you are experiencing slowness, you can disable indexing by calling setItemIndexMethod(NoIndex).
        QFile file("C:/Users/quanh/nju-documents/AdvancedProgramming-2021/homework/project-quanhaoli/src/map_self_build.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
        QTextStream in(&file);
        in>>ROW>>COL;
        if(ROW>5)
            ROW=5;
        if(COL>10)
            COL=10;
        //绘制表格

        for(int i=0;i<=ROW;i++)
        {
            scene2->addLine(start_x,start_y+i*height1,COL*width1+start_x,start_y+i*height1);
        }

        for(int i=0;i<=COL;i++)
        {
            scene2->addLine(start_x+i*width1,start_y,start_x+i*width1,start_y+ROW*height1);
        }
        int path_num;//有几条路径
        in>>path_num;
        for(int j=0;j<path_num;j++)
        {
            int path_type;//路径的种类：是0陆地还是1飞行
            in>>path_type;
            paths_type.push_back(path_type);
            int num;//拐点个数
            in>>num;
            int x;int y;//注意这里是格子数不是坐标！！
            in>>x>>y;
            Pathpoint* point1 = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
            point1->nextpoint = nullptr;
            start_points.push_back(point1);
            int pre_x = x;int pre_y = y;//上一个拐点的x,y
            in>>x>>y;
            Pathpoint* point = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
            point1->nextpoint = point;
            point->nextpoint = nullptr;
            int x1 = point1->pos.x();int y1 = point1->pos.y();int x2 = point->pos.x(); int y2 = point->pos.y();
            scene2->addLine(x1,y1,x2,y2);
            scene2->addRect(x1-4,y1-4,8,8);
            scene2->addRect(x2-4,y2-4,8,8);
            //qDebug()<<pre_x<<pre_y<<x<<y;
            if(path_type == 0)//如果是地面路径
                paint_grid(pre_x,pre_y,x,y);
            else if(path_type == 1)//如果是飞行路径
                paint_grid_fly(pre_x,pre_y,x,y);
            pre_x= x;pre_y=y;
            for(int i=0;i<num - 2;i++)
            {
                //创建拐点
                in>>x>>y;
                Pathpoint* point2 = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
                point->nextpoint = point2;
                point2->nextpoint = nullptr;
                scene2->addLine(point->pos.x(),point->pos.y(),point2->pos.x(),point2->pos.y());
                scene2->addRect(point2->pos.x()-4,point2->pos.y()-4,8,8);
                point = point2;
                if(path_type == 0)//如果是地面路径
                    paint_grid(pre_x,pre_y,x,y);
                else if(path_type == 1)//如果是飞行路径
                    paint_grid_fly(pre_x,pre_y,x,y);
                pre_x = x;pre_y = y;
             }
            Pathpoint* point2 = new Pathpoint(QPoint(0,start_y+height1/2+x*height1));
            point->nextpoint = point2;
            point2->nextpoint = nullptr;
            scene2->addLine(point->pos.x(),point->pos.y(),point2->pos.x(),point2->pos.y());
            scene2->addRect(point2->pos.x()-4,point2->pos.y()-4,8,8);
            point = point2;
        }
        int distant_num;//远战格子数目
        in>>distant_num;
        for(int j=0;j<distant_num*2;j++)
        {
            int x,y;
            in>>x>>y;
            paint_grid_2(x,y);//绘制远战绿色格子
            pair<int,int> cur;
            cur.first = x;
            cur.second = y;
            distant.push_back(cur);
        }
        addShop();addCard();
        connect(timer, &QTimer::timeout, scene2, &QGraphicsScene::advance);//为啥不用多线程的就不行
        connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
        connect(timer, &QTimer::timeout, this, &MainWindow::check);
        timer->start(50);
        view->show();
    }
}
MainWindow::~MainWindow()
{
    delete scene2;
    delete view;
    delete timer;
}
void MainWindow::check()
{
    if(game_end_signal == 1)
    {
        timer->stop();
        QList<QGraphicsItem*>list = scene2->items();
        foreach(QGraphicsItem* item, list)
        {
            scene2->removeItem(item);
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
        QList<QGraphicsItem*>list = scene2->items();
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
                scene2->removeItem(item);
            }
            QGraphicsScene* scene1 = new QGraphicsScene(this);
            scene1->setBackgroundBrush(QPixmap("D:/QtProjects/images/interface/trophy.png"));
            view->setScene(scene1);
        }
    }
    QList<QGraphicsItem*>list = scene2->items();
    foreach(QGraphicsItem* item, list)
    {
        if(item->type() == QGraphicsTextItem::Type)
        {
            scene2->removeItem(item);
            break;
        }
    }
    QString cur_src = QString::number(CUR_SRC);
    QGraphicsTextItem *txtitem = new QGraphicsTextItem(cur_src);
    txtitem->setPos(450,75);
    scene2->addItem(txtitem);
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
            int q = qrand() % 5;//目前僵尸种类
            q=1;
                if(q==0)
                {
                    while(true)
                    {
                        normalZombie* zombie = new normalZombie(i);
                        if(zombie->zombie_type == paths_type[i])
                        {
                            zombie->setPos(start_points[i]->pos.x() + width1/2, start_points[i]->pos.y());
                            scene2->addItem(zombie);
                            ZOMBIE_GEN_TIMES_NOW++;
                            counter = 0;
                            break;
                        }
                        else
                        {
                            i = qrand() % start_points.size();
                        }
                    }
                }
                else if(q==1)
                {
                    while(true)
                    {
                        boxzombie* zombie = new boxzombie(i);
                        if(zombie->zombie_type == paths_type[i])
                        {
                            zombie->setPos(start_points[i]->pos.x() + width1/2, start_points[i]->pos.y());
                            scene2->addItem(zombie);
                            ZOMBIE_GEN_TIMES_NOW++;
                            counter = 0;
                            break;
                        }
                        else
                        {
                            i = qrand() % start_points.size();
                        }
                    }
                }
                else if(q ==2)
                {
                    while(true)
                    {
                        dancingzombie* zombie = new dancingzombie(i);
                        if(zombie->zombie_type == paths_type[i])
                        {
                            zombie->setPos(start_points[i]->pos.x() + width1/2, start_points[i]->pos.y());
                            scene2->addItem(zombie);
                            ZOMBIE_GEN_TIMES_NOW++;
                            counter = 0;
                            break;
                        }
                        else
                        {
                            i = qrand() % start_points.size();
                        }
                    }
                }
                else if(q==3)
                {
                    while(true)
                    {
                        balloonzombie* zombie = new balloonzombie(i);
                        if(zombie->zombie_type == paths_type[i])
                        {
                            zombie->setPos(start_points[i]->pos.x() + width1/2, start_points[i]->pos.y());
                            scene2->addItem(zombie);
                            ZOMBIE_GEN_TIMES_NOW++;
                            counter = 0;
                            break;
                        }
                        else
                        {
                            i = qrand() % start_points.size();
                        }
                    }
                }
                else if(q==4)
                {
                    while(true)
                    {
                        firelockzombie* zombie = new firelockzombie(i);
                        if(zombie->zombie_type == paths_type[i])
                        {
                            zombie->setPos(start_points[i]->pos.x() + width1/2, start_points[i]->pos.y());
                            scene2->addItem(zombie);
                            ZOMBIE_GEN_TIMES_NOW++;
                            counter = 0;
                            break;
                        }
                        else
                        {
                            i = qrand() % start_points.size();
                        }
                    }
                }
        }
    }
    else
        return;
}
void MainWindow::addPlant(int x,int y)
{
    //qDebug()<<x<<y;
    QTransform transform;
    Plant* plant = nullptr;
    if(now_plant == "Chomper")
       plant = new CaiWen;
    else if(now_plant == "WallNut")
        plant = new wallnut;
    else if(now_plant == "Peashooter")
        plant = new PeaShooter;
    else if(now_plant == "Spikeweed")
        plant = new Spikeweed;
    else if(now_plant == "Blover")
        plant = new Blover;
    else if(now_plant == "CoffeeBean")
        plant = new CoffeeBean;
    else if(now_plant == "FumeShroom")
        plant = new FumeShroom;
    if(CUR_SRC >= plant->cost && (scene2->itemAt(now_plantpos_x,now_plantpos_y,transform) == nullptr || scene2->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == Zombie::Type || scene2->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == QGraphicsRectItem::Type || scene2->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == QGraphicsLineItem::Type || scene2->itemAt(now_plantpos_x,now_plantpos_y,transform)->type() == QGraphicsPathItem::Type))//默认不能一个格子放两个植物
    {//注意：我现在这里没法放植物，因为我这里绘画格子之后，itemAt返回值不是nullptr了
        //这里要判断加的格子是在近战还是远战的格子
        int grid_type;//要放入的格子的种类，0近战，1远战，2不能放
        if(MAP_NUM == "默认地图")
        {
            //qDebug()<<x<<y;
            if((x==0&&y<=8&&y>=0) || (x==4&&y<=8&&y>=0))
                grid_type = 0;
            else if(x==1 && y==0)
                grid_type = 1;
            else
                 grid_type = 2;
            if(plant->plant_type == grid_type)
            {
                //qDebug()<<"yes";
                plant->setPos(now_plantpos_x,now_plantpos_y);
                scene2->addItem(plant);
                CUR_SRC -= plant->cost;
            }
            else
                return;
        }
        else if(MAP_NUM == "自建地图")
        {
            int i=0;int j=0;
            //qDebug()<<jinzhan;
            for(;i<jinzhan.size();i++)
            {
                //qDebug()<<jinzhan[i];
                if(x==jinzhan[i].first && y == jinzhan[i].second)
                {
                    grid_type = 0;
                    break;
                }
            }
            for(;j<distant.size();j++)
            {
                if(x==distant[j].first && y == distant[j].second)
                {
                    grid_type = 1;
                    break;
                }
            }
            if(i == jinzhan.size() && j == distant.size())
                grid_type = 2;
            if(plant->plant_type == grid_type)
            {
                plant->setPos(now_plantpos_x,now_plantpos_y);
                scene2->addItem(plant);
                CUR_SRC -= plant->cost;
            }
            else
                return;
        }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
            QPoint pos = event->pos();
            int x = pos.x();int y = pos.y();
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
            qDebug()<<event->pos();
            if(i==COL || j==ROW)
                return;
            now_plantpos_x = x;
            now_plantpos_y = y;
            if(put_signal == 1)
            {
                addPlant(j,i);
                put_signal = 0;
            }
    }
}
void MainWindow::addPaths_default()
{
    //第一条路径
    int path_type = 0;//路径的种类：是0陆地还是1飞行
    paths_type.push_back(path_type);
    int x = 0;int y = 8;//注意这里是格子数不是坐标！！
    Pathpoint* point1 = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
    point1->nextpoint = nullptr;
    start_points.push_back(point1);
    pair<int,int> cur;
    for(int i=8;i>=0;i--)
    {
        cur.first = 0;
        cur.second = i;
        jinzhan.push_back(cur);
    }
    int pre_x = x;int pre_y = y;//上一个拐点的x,y
    x = 0;y=0;
    Pathpoint* point = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
    point1->nextpoint = point;
    point->nextpoint = nullptr;

    int x1 = point1->pos.x();int y1 = point1->pos.y();int x2 = point->pos.x(); int y2 = point->pos.y();
    scene2->addLine(x1,y1,x2,y2);
    scene2->addRect(x1-4,y1-4,8,8);
    scene2->addRect(x2-4,y2-4,8,8);
    if(path_type == 0)//如果是地面路径
        paint_grid(pre_x,pre_y,x,y);
    else if(path_type == 1)//如果是飞行路径
        paint_grid_fly(pre_x,pre_y,x,y);
    //第二条路径
    path_type = 1;//路径的种类：是0陆地还是1飞行
    paths_type.push_back(path_type);
    x = 4;y = 8;//注意这里是格子数不是坐标！！
    for(int i=8;i>=0;i--)
    {
        cur.first = 4;
        cur.second = i;
        jinzhan.push_back(cur);
    }
    Pathpoint* point2 = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
    point2->nextpoint = nullptr;
    start_points.push_back(point2);
    pre_x = x;pre_y = y;//上一个拐点的x,y
    x = 4;y=0;
    Pathpoint* point3 = new Pathpoint(QPoint(start_x+width1/2+y*width1,start_y+height1/2+x*height1));
    point2->nextpoint = point3;
    point3->nextpoint = nullptr;
    x1 = point2->pos.x();y1 = point2->pos.y();x2 = point3->pos.x(); y2 = point3->pos.y();
    scene2->addLine(x1,y1,x2,y2);
    scene2->addRect(x1-4,y1-4,8,8);
    scene2->addRect(x2-4,y2-4,8,8);
    if(path_type == 0)//如果是地面路径
        paint_grid(pre_x,pre_y,x,y);
    else if(path_type == 1)//如果是飞行路径
        paint_grid_fly(pre_x,pre_y,x,y);
    int distant_num = 1;//远战格子数目
    x = 1;y = 0;
    cur.first = x;cur.second = y;
    distant.push_back(cur);
    paint_grid_2(x,y);//绘制远战绿色格子
}
void MainWindow::addShop()
{
    shop* shop1 = new shop;
    shop1->setPos(600,30);
    scene2->addItem(shop1);
}
void MainWindow::addCard()
{
    card* card1 = new card("Chomper");
    card1->setPos(575,60);//这个是基于本来的图片的坐标，需要加150，变成场景中的坐标
    scene2->addItem(card1);
    card* card2 = new card("WallNut");
    card2->setPos(645,60);
    scene2->addItem(card2);
    card* card3 = new card("Peashooter");
    card3->setPos(715,60);
    scene2->addItem(card3);
    card* card4 = new card("Spikeweed");
    card4->setPos(785,60);
    scene2->addItem(card4);
    card* card5 = new card("Blover");
    card5->setPos(855,60);
    scene2->addItem(card5);
    card* card6 = new card("CoffeeBean");
    card6->setPos(925,60);
    scene2->addItem(card6);
    card* card7 = new card("FumeShroom");
    card7->setPos(995,60);
    scene2->addItem(card7);
}
void MainWindow::paint_grid(int pre_x, int pre_y, int x, int y)
{
    QPainterPath path;
    if(pre_x == x)//水平移动
    {
        for(int k=pre_y;k>=y;k--)
        {
            path.moveTo(start_x+k*width1,start_y+x*height1);
            path.addRect(start_x+k*width1,start_y+x*height1,width1,height1);
            scene2->addPath(path,QPen(Qt::black),QBrush(QColor(255,0,0,50)));//把近战的格子涂成红色
            pair<int,int> cur;
            cur.first = x;
            cur.second = k;
            jinzhan.push_back(cur);
        }
    }
    else if(pre_y == y)
    {
        if(pre_x < x)//向下动
        {
            for(int k=pre_x;k<=x;k++)
            {
                path.moveTo(start_x+y*width1,start_y+k*height1);
                path.addRect(start_x+y*width1,start_y+k*height1,width1,height1);
                scene2->addPath(path,QPen(Qt::black),QBrush(QColor(255,0,0,50)));//把近战的格子涂成红色
                pair<int,int> cur;
                cur.first = k;
                cur.second = y;
                jinzhan.push_back(cur);
            }
        }
        else//向上动
        {
            for(int k=pre_x;k>=x;k--)
            {
                path.moveTo(start_x+y*width1,start_y+k*height1);
                path.addRect(start_x+y*width1,start_y+k*height1,width1,height1);
                scene2->addPath(path,QPen(Qt::black),QBrush(QColor(255,0,0,50)));//把近战的格子涂成红色
                pair<int,int> cur;
                cur.first = k;
                cur.second = y;
                jinzhan.push_back(cur);
            }
        }
    }
}
void MainWindow::paint_grid_2(int x, int y)
{
    QPainterPath path;
    path.moveTo(start_x+y*width1,start_y+x*height1);
    path.addRect(start_x+y*width1,start_y+x*height1,width1,height1);
    scene2->addPath(path,QPen(Qt::black),QBrush(QColor(Qt::green)));//把近战的格子涂成红色
}
void MainWindow::paint_grid_fly(int pre_x, int pre_y, int x, int y)
{
    QPainterPath path;
    if(pre_x == x)//水平移动
    {
        for(int k=pre_y;k>=y;k--)
        {
            path.moveTo(start_x+k*width1,start_y+x*height1);
            path.addRect(start_x+k*width1,start_y+x*height1,width1,height1);
            scene2->addPath(path,QPen(Qt::black),QBrush(QColor(0,0,225,50)));//把近战的格子涂成红色
            pair<int,int> cur;
            cur.first = x;
            cur.second = k;
            jinzhan.push_back(cur);
        }
    }
    else if(pre_y == y)
    {
        if(pre_x < x)//向下动
        {
            for(int k=pre_x;k<=x;k++)
            {
                path.moveTo(start_x+y*width1,start_y+k*height1);
                path.addRect(start_x+y*width1,start_y+k*height1,width1,height1);
                scene2->addPath(path,QPen(Qt::black),QBrush(QColor(0,0,225,50)));//把近战的格子涂成红色
                pair<int,int> cur;
                cur.first = k;
                cur.second = y;
                jinzhan.push_back(cur);
            }
        }
        else//向上动
        {
            for(int k=pre_x;k>=x;k--)
            {
                path.moveTo(start_x+y*width1,start_y+k*height1);
                path.addRect(start_x+y*width1,start_y+k*height1,width1,height1);
                scene2->addPath(path,QPen(Qt::black),QBrush(QColor(0,0,225,50)));//把近战的格子涂成红色
                pair<int,int> cur;
                cur.first = k;
                cur.second = y;
                jinzhan.push_back(cur);
            }
        }
    }
}
