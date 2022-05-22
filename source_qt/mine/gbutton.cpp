#include "gbutton.h"
#include <QPainter>
#include <QMouseEvent>
// main game button
GameMainButton::GameMainButton(QWidget *parent) : QPushButton(parent){
    texId = 0;
    setFixedSize(24, 24);
    setStyleSheet(QString("background-color: black;"));
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
    switch (this->texId){
        case 0:
            painter.drawPixmap(0, 0, *sprite, 0, 0, 24, 24);
            break;
        case 1:
            painter.drawPixmap(0, 0, *sprite, 25, 0, 24, 24);
            break;
        case 2:
            painter.drawPixmap(0, 0, *sprite, 50, 0, 24, 24);
            break;
        case 3:
            painter.drawPixmap(0, 0, *sprite, 75, 0, 24, 24);
            break;
        case 4:
            painter.drawPixmap(0, 0, *sprite, 100, 0, 24, 24);
            break;
    }
}
void GameMainButton::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBpressed();
    }
}
void GameMainButton::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBreleased();
    }
}

// theme button
ThemeButton::ThemeButton(QWidget *parent) : QPushButton(parent){
    texId = 0;
    setFixedSize(24, 24);
    setStyleSheet(QString("background-color: black;"));
}
ThemeButton::~ThemeButton(){
    delete sprite;
}
void ThemeButton::setTexId(int texId){
    this->texId = texId;
    update();
}
int ThemeButton::getTexId(){
    return texId;
}
int ThemeButton::changeTheme(QPixmap* spr1, QPixmap *spr2, QPixmap *spr3, int themeId){
    switch(themeId){
        case 2:
            themeId = 0;
        case 0:
            *spr1 = QPixmap(QString(":/images/source.png"));
            *spr2 = QPixmap(QString(":/images/source2.png"));
            *spr3 = QPixmap(QString(":/images/source3.png"));
            break;
        case 1:
            *spr1 = QPixmap(QString(":/images/source_v2.png"));
            *spr2 = QPixmap(QString(":/images/source2_v2.png"));
            *spr3 = QPixmap(QString(":/images/source3_v2.png"));
            break;
    }
    return themeId;
}
void ThemeButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter painter(this);
    switch (this->texId){
        case 0:
            painter.drawPixmap(0, 0, *sprite, 0, 0, 24, 24);
            break;
        case 1:
            painter.drawPixmap(0, 0, *sprite, 25, 0, 24, 24);
            break;
    }
}
void ThemeButton::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBpressed();
    }
}
void ThemeButton::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBreleased();
    }
}
