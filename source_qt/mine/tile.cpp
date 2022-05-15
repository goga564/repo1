// painter
#include <QPainter>
// handler
#include <QMouseEvent>

#include "tile.h"

Tile::Tile(QWidget *parent) : QPushButton(parent) {
    y = x = 0;
}
Tile::Tile(int X, int Y, QWidget *parent) : QPushButton(parent) {
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setFixedSize(20,20);
    x = X; y = Y;
    cState = 0;
    inVicinity = 0;
    minePres = 0;
    texId = 1;
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
void Tile::setOpen(){
    if (texId == 1){
        cState = 0;
        texId = 0;
        repaint();
    }
}
bool Tile::isMined(){
    return minePres;
}
void Tile::setMine(){
    minePres = 1;
}
void Tile::changeTexSt(){ //an RMB signal use this
    if (cState == 1){
        return;
    }
    if (texId == 3){
        texId = 1;
        repaint();
        return;
    }
    ++texId;
    repaint();
    // change tile texture here
}
void Tile::setTex(QPaintEvent *event){ // using qpixmap
    if(!cState){
        return;
    }
    QPushButton::paintEvent(event);
    QPainter drawer(this);
}
void Tile::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit LMBsignal();
    }
    if (event->button() == Qt::RightButton){
        emit RMBsignal();
    }
}
