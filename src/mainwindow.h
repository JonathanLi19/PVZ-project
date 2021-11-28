#ifndef MAINWINDOOW_H
#define MAINWINDOOW_H
#include<QMainWindow>
#include<QGraphicsScene>
#include <QGraphicsView>
#include<QGraphicsSceneMouseEvent>
#include<QTimer>
#include<QList>
#include<QMouseEvent>
#include<QPoint>
#include<QString>
#include <QFile>
#include"Pathpoint.h"
#include"shop.h"
#include"card.h"
#include<QString>
#include"button.h"
#include "Boxzombie.h"
#include"zombie.h"
#include"plant.h"
#include<QDebug>
#include"normalzombie.h"
#include"caiwen.h"
#include"dancingzombie.h"
#include"balloonzombie.h"
#include"firelockzombie.h"
#include"wallnut.h"
#include"peashooter.h"
#include"spikeweed.h"
#include"blover.h"
#include"coffeebean.h"
#include"fumeshroom.h"
#define ZOMBIE_TOTAL 50
#define GEN_ONE_TIME 100
namespace Ui
{
    class MainWindow;
}
class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow()override;
    void mousePressEvent(QMouseEvent *event)override;
    void addPlant(int x,int y);
    void addPaths_default();

    void addCard();
    void choose();//先进入选择地图界面，然后可以设置一个全局变量看点的是第几个地图，然后再调用地图显示函数
    void addButton();
    void paint_grid(int pre_x,int pre_y,int x,int y);//对陆地路径的近战格子上色
    void paint_grid_2(int x,int y);//给远战格子上色
    void paint_grid_fly(int pre_x,int pre_y,int x,int y);//给飞行路径的近战格子上色
    //所有近战格子分布在路径之上（不管是哪种路径）
public slots:
    void addZombie();
    void check();
    void showmap();//显示第i个地图
    void addShop();
private:
    QTimer* timer;

    QGraphicsView* view;
    static int ZOMBIE_GEN_TIMES_NOW;
    int life;
    Ui::MainWindow *ui;
};
extern int game_end_signal;
extern int game_win_signal;//定义在main.cpp中
extern QString now_plant;//定义在card.cpp中
extern int now_plantpos_x;
extern int now_plantpos_y;//定义在mainwindow.cpp中
extern int put_signal;//要开始放植物的标志，定义在card.cpp中
extern QGraphicsScene* scene2;
#endif // MAINWINDOOW_H
