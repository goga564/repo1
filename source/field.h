#ifndef FIELD_H
#define FIELD_H
#include "tile.h"
class Field{  // determines game status
        int fX,fY;
        int mines; // number of mines in field
        bool exists(int x,int y); // checks whether cell(x,y) exists or not; used for recursive call/when checking on edge
        void open(int x,int y); // opens current Tiles[x][y]
        void openAll(); // used if player has lo
        bool checkWin(); // determines whether all empty cells are opened or not
        void changeTex(int x,int y,int to); // tex replacement helper function when RMB clicked
        //signal handlers
        void onLMB();
        void onRMB();
    public:
        Field();
        ~Field();
        Tile** Tiles; //2d array
        //int getH();int getW(); //sets height and width respectively , values are taken from settings box;  OBSOLETE

};
#endif
