#include "tile.h"
#include "field.h"
Field::Field(){
    Tiles=static_cast<Tile**>(operator new[](fX*sizeof(Tile))); //wrong
    /*for(int i=0;i<fX;i++){
        Tiles[i]=new Tile(i,fY);
        for(int j=0;j<fY;j++){

        }
    }*/
    /*
    */
}
void Field::openTile(int x,int y){
    if(exists(x,y)==false){
        return;
    }
    // ...request to an object

}
bool Field::exists(int x,int y){
    return x>=0&&y>=0&&x<=fX&&y<=fY;
}
bool Field::checkWin(){
    int n=(fX*fY)-mAmount;
    for(int i=0;i<fX;i++){
        for(int j=0;j<fX;j++){
            //n-=(Tiles[i][j].getState()); //wrong
        }
    }
    return (0==n);
}