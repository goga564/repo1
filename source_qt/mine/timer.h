#ifndef TIMER_H
#define TIMER_H
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QPainter>
class SessionTimer : public QLCDNumber{
        Q_OBJECT
    public:
        SessionTimer(QWidget *parent = NULL);
        QTime sessionTime;
        QTimer* sessionTimer;
    public slots:
        void upd();
        void slstart();
        void slstop();
        void setzero();
};
#endif
