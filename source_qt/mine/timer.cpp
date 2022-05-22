#include "timer.h"
SessionTimer::SessionTimer(QWidget *parent) : QLCDNumber(parent){
    this->setStyleSheet(QString("color: #ff0000; background-color: #000000"));
    setSegmentStyle(Flat);
    setFixedSize(65, 24);
    sessionTime.setHMS(0, 0, 0);
    sessionTimer = new QTimer(this);
    sessionTimer->setTimerType(Qt::PreciseTimer);
    connect(sessionTimer, SIGNAL(timeout()), SLOT(upd()));
    display(sessionTime.toString("mm:ss"));
}
void SessionTimer::upd(){
    sessionTime = sessionTime.addMSecs(1000);
    display(sessionTime.toString("mm:ss"));
}
void SessionTimer::slstart(){
    sessionTime.setHMS(0, 0, 0);
    sessionTime = sessionTime.addMSecs(1000);
    display(sessionTime.toString("mm:ss"));
    sessionTimer->start(1000);
}
void SessionTimer::slstop(){
    sessionTimer->stop();
    display(sessionTime.toString("mm:ss"));
}
void SessionTimer::setzero(){
    sessionTime.setHMS(0, 0, 0);
    display(sessionTime.toString("mm:ss"));
}
