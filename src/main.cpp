#include<QApplication>
#include"mainwindow.h"
int game_end_signal = 0;
int game_win_signal = 0;
int main(int argc,char*argv[])
{
    QApplication a(argc,argv);
    MainWindow w;
    w.setFixedSize(1800,1000);
    //w.setFixedSize(1500,1000);
    w.setWindowTitle("Plants VS Zombies");
    w.show();
    return a.exec();
}
