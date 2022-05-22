#include "mainwindow.h"
//#include "Windows.h"
#include <QtGui>
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.timer->startTimer(1000, Qt::CoarseTimer);
    w.setStyleSheet(QString("background-color: grey"));
    //w.setWindowFlag(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
