#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include "tile.h"
class Field{  // determines game status
        int fX,fY;
        Tile** Tiles; //2d array
        int mAmount; // number of mines in field
        void openTile(int x,int y); // opens current Tile
        bool exists(int x,int y); // checks whether cell(x,y) exists or not; used for recursive call/when checking on edge
        bool checkWin(); // determines whether all empty cells opened or not
    public:
        Field();
        //int getH();int getW(); //sets height and width respectively , values are taken from settings box;

};
#endif // FIELD_H_INCLUDED
