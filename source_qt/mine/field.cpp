#include "tile.h"
#include "gbutton.h"
#include "field.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
Field::Field(int fX, int fY, int mines, QWidget *parent) : QWidget(parent){
    this->fX = fX; this->fY = fY;
    this->mines = mines;
    status = 1; // field is clickable
    themeId = 0;
    spr = new QPixmap(QString(":/images/source.png")); spr2 = new QPixmap(QString(":/images/source2.png"));
    spr3 = new QPixmap(QString(":/images/source3.png"));
    gmbutton = new GameMainButton(parent); tbutton = new ThemeButton(parent);
    gmbutton->sprite = spr2; tbutton->sprite = spr3;
    connect(gmbutton, SIGNAL(LMBpressed()), SLOT(ongmButtonLMBpressed()), Qt::DirectConnection);
    connect(gmbutton, SIGNAL(LMBreleased()), SLOT(ongmButtonLMBreleased()), Qt::DirectConnection);
    connect(tbutton, SIGNAL(LMBpressed()), SLOT(ontButtonLMBpressed()), Qt::DirectConnection);
    connect(tbutton, SIGNAL(LMBreleased()), SLOT(ontButtonLMBreleased()), Qt::DirectConnection);
    Tiles = new Tile* [fX];
    for (int i = 0; i < fX; ++i){
        Tiles[i] = new Tile [fY];
    }
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j] = Tile(i, j, parent);
            Tiles[i][j].setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            Tiles[i][j].setFixedSize(16, 16);
            Tiles[i][j].setStyleSheet(QString("background-color: black;"));
            Tiles[i][j].setMouseTracking(1);
            Tiles[i][j].sprite = spr;
            connect(&Tiles[i][j], SIGNAL(LMBreleased()), SLOT(onTileLMBreleased()), Qt::DirectConnection);
            connect(&Tiles[i][j], SIGNAL(LMBpressed()), SLOT(onTileLMBpressed()), Qt::DirectConnection);
            connect(&Tiles[i][j], SIGNAL(RMBpressed()), SLOT(onTileRMBreleased()), Qt::DirectConnection);
        }
    }
    setMines();
}
Field::~Field(){
    for (int i = 0; i < fX; i++){
        delete[] Tiles[i];
    }
    delete[] Tiles;
    delete gmbutton; delete tbutton;
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
    Tiles[x][y].setDown(1);
    Tiles[x][y].setEnabled(0);
    if ((Tiles[x][y].inVicinity) == 0){ // if there is no at least 1 mine in surrounding area
        open(x-1, y+1);
        open(x-1, y);
        open(x-1, y-1);     // opening order in case == 0
        open(x, y-1);       // 3 4 5
        open(x+1, y-1);     // 2 _ 6
        open(x+1, y);       // 1 8 7
        open(x+1, y+1);
        open(x, y+1);
    }
}
void Field::openAll(){
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j].setDown(1);
            Tiles[i][j].setEnabled(0);
            if ((Tiles[i][j].getTexId() == 2) && (!(Tiles[i][j].isMined()))){
                Tiles[i][j].changeTexToWrong(); // if there is no mine on this tile, but it is flagged
            }
            if (Tiles[i][j].isMined()){
                Tiles[i][j].setOpen();
            }
        }
    }
}
bool Field::checkWin(){
    int n = (fX * fY) - mines; // number of no mine tiles
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fX; ++j){
            n -= Tiles[i][j].getState();
        }
    }
    return n == 0;
}
void Field::setMines(){
    started = 0;
    for (int i = 0, t1, t2; i < mines;){
        t1 = QRandomGenerator::global()->bounded(0, fX) % fX; t2 = QRandomGenerator::global()->bounded(0, fY) % fY;
        if (!(Tiles[t1][t2].isMined())){
            Tiles[t1][t2].setMine();
            ++i;
        }
        else{
            continue;
        }
    }
    for (int x = 0; x < fX; ++x){
        for (int y = 0; y < fY; ++y){
            if (Tiles[x][y].isMined()){
                incVicinity(x,y);
            }
        }
    }
}
void Field::incVicinity(int x, int y){
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
void Field::onTileLMBreleased(){
    if (status){
        Tile* tileptr = static_cast<Tile*>(sender());
        if (!started){
            if (tileptr->isMined()){
                tileptr->unsetMine();
                tileptr->update();
                tileptr->changeTexToOpen();
                for (int t1, t2;;){ // bullshit
                    t1 = QRandomGenerator::global()->bounded(0, fX) % fX; t2 = QRandomGenerator::global()->bounded(0, fY) % fY;
                    if (!(Tiles[t1][t2].isMined())){
                        Tiles[t1][t2].setMine();
                        Tiles[t1][t2].update();
                        incVicinity(t1,t2);
                        break;
                    }
                    else{
                        continue;
                    }
                }
            }
            open(tileptr->getX(), tileptr->getY());
            gmbutton->setTexId(0);
            started = 1;
            emit start(); // for external use
            return;
        }
        else if (tileptr->getTexId() != 2){
            if (tileptr->getState()){ // if tile is opened do nothing
                return;
            }
            if (tileptr->isMined()){
                tileptr->setMineRed();
                gmbutton->setTexId(4);
                status = 0;
                emit finish(); // for external use
                openAll();
                return;
            }
            open(tileptr->getX(), tileptr->getY());
            if (checkWin()){
                gmbutton->setTexId(3);
                status = 0;
                emit finish(); // for external use
                openAll();
                return;
            }
            gmbutton->setTexId(0);
        }
    }
}
void Field::onTileLMBpressed(){
    if (status){
        Tile* tileptr = static_cast<Tile*>(sender());
        if (tileptr->getTexId() != 2){
            if (tileptr->getState()){
                return;
            }
            gmbutton->setTexId(2);
            tileptr->setDown(1);
            tileptr->changeTexToOpen();
        }
    }
}
void Field::onTileRMBreleased(){
    if (status){
        Tile* tileptr = static_cast<Tile*>(sender()); // tile pointer to pointer object that sent signal
        if (tileptr->getState()){ // if tile is opened do nothing
            return;
        }
        tileptr->changeTexRMB(); // flag or question mark
    }
}
void Field::ongmButtonLMBpressed(){
    GameMainButton* gmbptr = static_cast<GameMainButton*>(sender());
    gmbptr->setDown(1);
    gmbptr->setTexId(1);
}
void Field::ongmButtonLMBreleased(){
    GameMainButton* gmbptr = static_cast<GameMainButton*>(sender());
    gmbptr->setDown(0);
    gmbptr->setTexId(0);
    if (!status){
        status = 1;
    }
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j] = Tile(i, j, this);
            Tiles[i][j].setDown(0);
            Tiles[i][j].setEnabled(1);
            Tiles[i][j].update();
        }
    }
    setMines();
    emit finish();
    emit finishinst();
}
void Field::ontButtonLMBpressed(){
    tbutton->setDown(1);
    tbutton->setTexId(1);
}
void Field::ontButtonLMBreleased(){
    tbutton->setDown(0);
    tbutton->setTexId(0);
    themeId = tbutton->changeTheme(spr, spr2, spr3, ++themeId);
    gmbutton->update();
    for (int i = 0; i < fX; ++i){
        for (int j = 0; j < fY; ++j){
            Tiles[i][j].update();
        }
    }
}
