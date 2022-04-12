#include "tile.h"
#include "field.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;
Field::Field(){
    ///Tiles = static_cast<Tile**>(operator new[](fX*sizeof(Tile))); // wrong
    //fX = Settings.getW();fY = Settings.getH(); SETTINGS.H
    //mines = Settings.getM(); SETTINGS.H
    fX = 15; fY = 30; // example of getW(),getH()
    mines = 99; // example of mines
    Tiles = new Tile* [fX];
    for (int i = 0; i < fX; ++i){
        Tiles[i] = new Tile [fY];
    }
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j] = Tile(i,j);
        }
    }
    for (int i = 0, temp1, temp2; i < mines; ++i){   // yes, this way is not a good one, but it's temporarily (i guess)
        temp1 = genrIndex(fX); temp2 = genrIndex(fY);
        if (!(Tiles[temp1][temp2].isMined())){
            Tiles[temp1][temp2].setMine();
        }
        else {
            --i;
            cout << endl << "MESSAGE(while placing mines): [" << temp1 << "][" << temp2 << "]"<< " repeat detected, fixed" ; // just check
        }
    }
    for (int x = 0; x < fX; ++x){
        for (int y = 0; y < fY; ++y){
            if (Tiles[x][y].isMined()){
                if (exists(x-1,y+1)){
                    Tiles[x-1][y+1].inVicinity++;
                }
                if (exists(x-1,y)){
                    Tiles[x-1][y].inVicinity++;
                }
                if (exists(x-1,y-1)){
                    Tiles[x-1][y-1].inVicinity++;
                }
                if (exists(x,y-1)){
                    Tiles[x][y-1].inVicinity++;
                }
                if (exists(x+1,y-1)){
                    Tiles[x+1][y-1].inVicinity++;
                }
                if (exists(x+1,y)){
                    Tiles[x+1][y].inVicinity++;
                }
                if (exists(x+1,y+1)){
                    Tiles[x+1][y+1].inVicinity++;
                }
                if (exists(x,y+1)){
                    Tiles[x][y+1].inVicinity++;
                }
            }
        }
    }
    /* console */
    conTiles = new char* [fX];
    for(int i = 0; i < fX; ++i){
        conTiles[i] = new char [fY];
    }
    for(int i = 0; i < fX; ++i){
        for(int j = 0; j < fY; ++j){
            conTiles[i][j] = 'X';
        }
    }
}
Field::~Field(){
    for (int i = 0; i < fX; i++){
        delete[] Tiles[i];
    }
    delete[] Tiles;
}
bool Field::exists(int x, int y){
    return x>=0 && y>=0 && x<fX && y<fY;
}
void Field::open(int x, int y){
    if (!exists(x,y)){
        return;
    }
    if (Tiles[x][y].getState()){ // if opened
        return;
    }
    Tiles[x][y].setOpen();
    if ((Tiles[x][y].counter()) == 0){ // if there is no at least 1 mine in surrounding area
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
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            if (!(Tiles[i][j].getState())){
                Tiles[i][j].setOpen();
            }
        }
    }
}
bool Field::checkWin(){
    int n = (fX * fY) - mines; // common case of check
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fX; ++j){
            n -= Tiles[i][j].getState(); // common case of check
        }
    }
    return (n == 0);
}
void Field::changeTex(int x, int y, int to){
    if (Tiles[x][y].getState()){
        return;
    }
    Tiles[x][y].changeTex();
    /*redraw (x,y) texture*/
}
void Field::onLMB(){
}
void Field::onRMB(){
}
int Field::genrIndex(int upper){
    random_device engine;
    mt19937 gen(engine());
    uniform_int_distribution<> dist(0, upper-1);
    return dist(gen);
}
void Field::conDraw(){ //for console
    for (int i = 0; i < fY; ++i){
        if(i < 9){
            cout << i << "  " ;
        }
        if(i >= 9){
            cout << i << " " ;
        }
    }
    cout << endl << endl << endl;
    for (int i = 0, j2 = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            cout << conTiles[i][j]<<"  ";
        }
        cout << " " << j2;
        j2++;
        cout << endl << endl;
    }
}
void Field::conOpen(int x, int y){ //for console
    if (!exists(x,y)){
        return;
    }
    if (Tiles[x][y].getState()){
        return;
    }
    Tiles[x][y].setOpen();
    switch(Tiles[x][y].counter()){
        case 0:
            conTiles[x][y] = 'O';
            conOpen(x-1,y+1);
            conOpen(x-1,y);
            conOpen(x-1,y-1);
            conOpen(x,y-1);
            conOpen(x+1,y-1);
            conOpen(x+1,y);
            conOpen(x+1,y+1);
            conOpen(x,y+1);
            break;
        case 1:
            conTiles[x][y] = '31';
            break;
        case 2:
            conTiles[x][y] = '32';
            break;
        case 3:
            conTiles[x][y] = '33';
            break;
        case 4:
            conTiles[x][y] = '34';
            break;
        case 5:
            conTiles[x][y] = '35';
            break;
        case 6:
            conTiles[x][y] = '36';
            break;
        case 7:
            conTiles[x][y] = '37';
            break;
        case 8:
            conTiles[x][y] = '38';
            break;
    }
}
void Field::forceOpen(){
    for (int i = 0; i < fX; i++){
        for (int j = 0; j < fY; j++){
            if (Tiles[i][j].isMined()){
                conTiles[i][j] = '*';
            }
        }
    }
}
