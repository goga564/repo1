#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
class Tile{
        int x,y; // x,y
        bool cState; // status of cell; 0-closed,1-opened
        bool minePres; // presence of mine; 0-no,1-in presence
        int inVicinity; // number of mines in surrounding area(8 cells) of current; used when placing mines
        int texId; // 0-opened,1-closed;2-flagged closed,3-marked closed
    public:
        Tile(int X,int Y); // init of object(X,Y)
        int getX();int getY(); // get x,y
        bool getState(); // whether is opened or closed
        bool setOpen(); // set open
        bool isMined(); // get minepres
        void setMine(); // sets mine to cell while init
        int counter(); // amount of mines in the vicinity
        void incCounter(); //increases counter
        void changeTex(); // put;
        // functions called by click used by field methods
        void LMBsignal();//...
        void RMBsignal();//...
};
#endif // TILE_H_INCLUDED
