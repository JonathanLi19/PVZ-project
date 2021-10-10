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
#include"Pathpoint.h"
#include"shop.h"
#include"card.h"
#define ZOMBIE_TOTAL 50
#define GEN_ONE_TIME 100
class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow()override;
    void mousePressEvent(QMouseEvent *event)override;
    void addPlant();
    void addPaths();
    void addShop();
    void addCard();
public slots:
    void addZombie();
    void check();
private:
    QTimer* timer;
    QGraphicsScene* scene;
    QGraphicsView* view;
    static int ZOMBIE_GEN_TIMES_NOW;
    int life;
};
extern int game_end_signal;
extern int game_win_signal;//定义在main.cpp中
extern QString now_plant;//定义在card.cpp中
extern int now_plantpos_x;
extern int now_plantpos_y;//定义在mainwindow.cpp中
extern int put_signal;//要开始放植物的标志，定义在card.cpp中
#endif // MAINWINDOOW_H
