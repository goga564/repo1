#include "tile.h"
#include "field.h"
#include <cstdlib>
#include <ctime>
Field::Field(){
    ///Tiles=static_cast<Tile**>(operator new[](fX*sizeof(Tile))); // wrong
    //fX=Settings.getW();fY=Settings.getH(); SETTINGS.H
    //mines=Settings.getM(); SETTINGS.H
    fX=20;fY=30; //example of getW(),getH()
    Tiles=new Tile*[fX];
    for(int i=0;i<fX;i++){
        Tiles[i]=new Tile[fY];
    }
    for(int i=0;i<fX;i++){
        for(int j=0;j<fY;j++){
            Tiles[i][j]=Tile(i,j);
        }
    }
    srand(time(NULL));
    for(int i=0;i<mines;i++){
        Tiles[rand()%fX][rand()%fY].setMine();
    }
    for(int x=0;x<fX;x++){
        for(int y=0;y<fY;y++){
            if(Tiles[x][y].isMined()){
                if(exists(x-1,y+1)){
                    Tiles[x-1][y+1].inVicinity++;
                }
                if(exists(x-1,y)){
                    Tiles[x-1][y].inVicinity++;
                }
                if(exists(x-1,y-1)){
                    Tiles[x-1][y-1].inVicinity++;
                }
                if(exists(x,y-1)){
                    Tiles[x][y-1].inVicinity++;
                }
                if(exists(x+1,y-1)){
                    Tiles[x+1][y-1].inVicinity++;
                }
                if(exists(x+1,y)){
                    Tiles[x+1][y].inVicinity++;
                }
                if(exists(x+1,y+1)){
                    Tiles[x+1][y+1].inVicinity++;
                }
                if(exists(x,y+1)){
                    Tiles[x][y+1].inVicinity++;
                }
            }
        }
    }
}
Field::~Field(){
    for(int i=0;i<fX;i++){
        delete[] Tiles[i];
    }
    delete[] Tiles;
}
bool Field::exists(int x,int y){
    return x>=0&&y>=0&&x<fX&&y<fY;
}
void Field::open(int x,int y){
    if(!exists(x,y)){
        return;
    }
    if(Tiles[x][y].getState()){ //if opened
        return;
    }
    Tiles[x][y].setOpen();
    if((Tiles[x][y].counter())==0){ //if there is no at least 1 mine in surrounding area
        open(x-1,y+1);
        open(x-1,y);
        open(x-1,y-1);     // opening order in case ==0
        open(x,y-1);       // 3 4 5
        open(x+1,y-1);     // 2 _ 6
        open(x+1,y);       // 1 8 7
        open(x+1,y+1);
        open(x,y+1);
    }
}
void Field::openAll(){
    for(int i=0;i<fX;i++){
        for(int j=0;j<fY;j++){
            if(!(Tiles[i][j].getState())){
                Tiles[i][j].setOpen();
            }
        }
    }
}
bool Field::checkWin(){
    int n=(fX*fY)-mines; //common case of check
    for(int i=0;i<fX;i++){
        for(int j=0;j<fX;j++){
            n-=Tiles[i][j].getState(); //common case of check
        }
    }
    return (n==0);
}
void Field::changeTex(int x,int y,int to){
    if(Tiles[x][y].getState()){
        return;
    }
    Tiles[x][y].changeTex();
    /*redraw (x,y) texture*/
}
void onLMB(){
}
void onRMB(){
}
