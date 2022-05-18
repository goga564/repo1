#include "gbutton.h"
#include <QPainter>
#include <QMouseEvent>
GameMainButton::GameMainButton(QWidget *parent) : QPushButton(parent){
    texId = 0;
    sprite = new QPixmap(QString(":/images/source2.png"));
}
GameMainButton::~GameMainButton(){
    delete sprite;
}
int GameMainButton::getTexId(){
    return texId;
}
void GameMainButton::setTexId(int texId){
    this->texId = texId;
    update();
}
void GameMainButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter painter(this);
    switch (this->getTexId()){
        case 0:
            painter.drawPixmap(0, 0, *sprite, 0, 0, 24, 23);
            break;
        case 1:
            painter.drawPixmap(0, 0, *sprite, 25, 0, 24, 23);
            break;
        case 2:
            painter.drawPixmap(0, 0, *sprite, 50, 0, 24, 23);
            break;
        case 3:
            painter.drawPixmap(0, 0, *sprite, 75, 0, 24, 23);
            break;
        case 4:
            painter.drawPixmap(0, 0, *sprite, 100, 0, 24, 23);
            break;
    }
}
void GameMainButton::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBpressed();
    }
}
void GameMainButton::mouseReleaseEvent(QMouseEvent *event){
    if (this->getTexId() == 1){
        if (event->button() == Qt::LeftButton){
            emit LMBreleased();
        }
    }
}
