#include <tile.h>
Tile::Tile(int X,int Y){
    x=X;y=Y;
    cState=0;
    inVicinity=0;
    minePres=0;
    texId=1;
    //common tile texture(closed) initializes
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
    if(texId==1){
        cState=1;
        texId=0;
        return 1;
        //change tile texture here
    }
    return 0; //no permission for signal LMB
}
int Tile::counter(){
    return inVicinity;
}
void Tile::incCounter(){
    inVicinity++;
}
bool Tile::isMined(){
    return minePres;
}
void Tile::setMine(){
    minePres=1;
    //set texture here
}
void Tile::changeTex(){ //an RMB signal use this
    if(cState==1){
        return;
    }
    if(texId==3){
        texId=1;
    }
    else texId++;
    //change tile texture here
}
