// painter
//#include <QApplication>
#include <QPainter>
// handler
#include <QMouseEvent>
#include "tile.h"
#include "field.h"
#include <QDebug>
Tile::Tile(QWidget *parent) : QPushButton(parent) {
    y = x = 0;
}
Tile::Tile(int X, int Y, QWidget *parent) : QPushButton(parent) {
    x = X; y = Y;
    cState = 0;
    inVicinity = 0;
    minePres = 0;
    texId = 1;
}
Tile::~Tile(){}
Tile &Tile::operator =(const Tile &tile){ // assignment operator definition
    if (this != &tile){ // avoid self-assignment
        x = tile.x;
        y = tile.y;
        cState = tile.cState;
        inVicinity = tile.inVicinity;
        minePres = tile.minePres;
        texId = tile.texId;
    }
    return *this;
}
int Tile::getX(){
    return x;
}
int Tile::getY(){
    return y;
}
bool Tile::getState(){
    return cState;
}
int Tile::getTexId(){
    return texId;
}
void Tile::setOpen(){
    cState = 1;
    texId = 0;
    update();
}
int Tile::isMined(){
    return minePres;
}
void Tile::setMine(){
    minePres = 1;
}
void Tile::setMineRed(){
    minePres = 2;
}
void Tile::unsetMine(){
    minePres = 0;
    update();
}
void Tile::changeTexRMB(){ // RMB SIGNAL
    if (cState){
        return;
    }
    if (texId == 3){
        texId = 1;
        update();
        return;
    }
    ++texId;
    update();
}
void Tile::changeTexToOpen(){
    switch (texId){
        case 0:
        case 1:
            texId = 0;
            break;
        case 3:
            texId = 5;
            break;
    }
    update();
}
void Tile::changeTexToWrong(){ // GAME RESULTS
    texId = 4;
    update();
}
void Tile::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter painter(this);
    if (!cState){
       switch (this->getTexId()){
           case 0:
               painter.drawPixmap(0, 0, *sprite, 17, 0, 16, 16);
               break;
           case 1:
               painter.drawPixmap(0, 0, *sprite, 0, 0, 16, 16);
               break;
           case 2:
               painter.drawPixmap(0, 0, *sprite, 34, 0, 16, 16);
               break;
           case 3:
               painter.drawPixmap(0, 0, *sprite, 51, 0, 16, 16);
               break;
           case 4:
               painter.drawPixmap(0, 0, *sprite, 119, 0, 16, 16);
               break;
           case 5:
               painter.drawPixmap(0, 0, *sprite, 68, 0, 16, 16);
               break;
       }
       return;
    }
    else{
        if (this->isMined()){
            if (this->isMined() == 1){
                painter.drawPixmap(0, 0, *sprite, 85, 0, 16, 16);
            }
            else if (this->isMined() == 2){
                painter.drawPixmap(0, 0, *sprite, 102, 0, 16, 16);
            }
            return;
        }
        else{
            switch (this->inVicinity){
                case 0:
                    painter.drawPixmap(0, 0, *sprite, 17, 0, 16, 16);
                    break;
                case 1:
                    painter.drawPixmap(0, 0, *sprite, 0, 17, 16, 16);
                    break;
                case 2:
                    painter.drawPixmap(0, 0, *sprite, 17, 17, 16, 16);
                    break;
                case 3:
                    painter.drawPixmap(0, 0, *sprite, 34, 17, 16, 16);
                    break;
                case 4:
                    painter.drawPixmap(0, 0, *sprite, 51, 17, 16, 16);
                    break;
                case 5:
                    painter.drawPixmap(0, 0, *sprite, 68, 17, 16, 16);
                    break;
                case 6:
                    painter.drawPixmap(0, 0, *sprite, 85, 17, 16, 16);
                    break;
                case 7:
                    painter.drawPixmap(0, 0, *sprite, 102, 17, 16, 16);
                    break;
                case 8:
                    painter.drawPixmap(0, 0, *sprite, 119, 17, 16, 16);
                    break;
            }
        }
    }
}
void Tile::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBpressed();
    }
    if (event->button() == Qt::RightButton){
        emit RMBpressed();
    }
}
void Tile::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBreleased();
    }
}
