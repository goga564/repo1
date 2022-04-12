#include <tile.h>
Tile::Tile(){
    y = x = 0;
}
Tile::Tile(int X, int Y){
    x = X; y = Y;
    cState = 0;
    inVicinity = 0;
    minePres = 0;
    texId = 1;
    /* draw tile texture */
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
bool Tile::setOpen(){
    if (texId == 1){
        cState = 1;
        texId = 0;
        return 1;
        //change tile texture here to opened one (number is overlay)
        //or to opened one with number
    }
    return 0; //
}
int Tile::counter(){
    return inVicinity;
}
bool Tile::isMined(){
    return minePres;
}
void Tile::setMine(){
    minePres = 1;
}
void Tile::changeTex(){ //an RMB signal use this
    if (cState == 1){
        return;
    }
    if (texId == 3){
        texId = 1;
    }
    else texId++;
    //change tile texture here
}
