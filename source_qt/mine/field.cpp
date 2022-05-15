#include "tile.h"
#include "field.h"
#include "mainwindow.h"

#include <ctime>
#include <cstdlib>
#include <random>
#include <QPixmap>
#include <QRandomGenerator>
#include <QMessageBox>

using namespace std;

Field::Field(QWidget *parent) : QWidget(parent){
    //fX = Settings.getW();fY = Settings.getH(); SETTINGS.H
    //mines = Settings.getM(); SETTINGS.H
    fX = 15; fY = 30; // example of getW(),getH()
    mines = 99; // example of mines
    status = 1; // field is clickable
    Tiles = new Tile* [fX];
    for (int i = 0; i < fX; ++i){
        Tiles[i] = new Tile [fY];
    }
    //QPixmap *tex = new QPixmap(":/textures/0.png");
    //tex->
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j] = Tile(i, j, this);
            Tiles[i][j].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            Tiles[i][j].setFixedSize(22, 22);
            Tiles[i][j].setStyleSheet(QString("background-color: white"));
            connect(&Tiles[i][j], SIGNAL(LMBsignal()), this, SLOT(onLMB()));
            connect(&Tiles[i][j], SIGNAL(RMBsignal()), this, SLOT(onRMB()));
        }
    }/*
    for (int i = 0, temp1, temp2; i < mines; ++i){
        temp1 = genrIndex(fX); temp2 = genrIndex(fY);
        if (!(Tiles[temp1][temp2].isMined())){
            Tiles[temp1][temp2].setMine();
        }
        else{
            --i;
        }
    }*/
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
}
Field::~Field(){
    for (int i = 0; i < fX; i++){
        delete[] Tiles[i];
    }
    delete[] Tiles;
}
bool Field::exists(int x, int y){
    return x >= 0 && y >= 0 && x < fX && y < fY;
}
void Field::open(int x, int y){
    if (!exists(x, y)){
        return;
    }
    if (Tiles[x][y].getState()){ // if opened
        return;
    }
    Tiles[x][y].setOpen();
    if ((Tiles[x][y].inVicinity) == 0){ // if there is no at least 1 mine in surrounding area
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
    return n == 0;
}
/*void Field::changeTex(int x, int y, int to){
    if (Tiles[x][y].getState()){
        return;
    }
    Tiles[x][y].changeTex();
    // redraw (x,y) texture
}*/

void Field::onLMB(){
    if (status){
        Tile* tileptr = reinterpret_cast<Tile*>(sender());
        if (tileptr->getState()){ // if tile is opened do nothing
            return;
        }
        if (tileptr->isMined()){
            status = 0;
            emit finish();
            QMessageBox::information(NULL, "Status", "You have lost!");
            openAll();
            return;
        }
        open(tileptr->x, tileptr->y);
        if (checkWin()){
            status = 0;
            emit finish();
            QMessageBox::information(NULL, "Status", "You have won!");
            openAll();
        }
    }
}
void Field::onRMB(){
    if (status){
        Tile* tileptr = reinterpret_cast<Tile*>(sender()); // pointer to object that sent signal
        if (tileptr->getState()){ // if tile is opened do nothing
            return;
        }
        tileptr->changeTexSt(); // flag or question mark
    }
}
int Field::genrIndex(int upper){
    std::random_device engine;
    std::mt19937 gen(engine());
    std::uniform_int_distribution<> dist(0, upper-1);
    return dist(gen);
}

