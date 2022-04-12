#ifndef FIELD_H
#define FIELD_H
#include "tile.h"
#include <vector>
class Field{  // determines game status
    public: // temporarily used as
        int fX, fY;
        int mines; // number of mines in field
        //int status; // game status: whether is on session or not
        bool exists(int x, int y); // checks whether cell(x,y) exists or not; used for recursive call/when checking on edge
        void open(int x, int y); // opens current Tiles[x][y]
        void openAll(); // used if player has lo
        bool checkWin(); // determines whether all empty cells are opened or not
        void changeTex(int x, int y, int to); // tex replacement helper function when RMB clicked
        // number generator
        int genrIndex(int upper);
        // signal handlers
        void onLMB();
        void onRMB();
            /* for console test */
        void conDraw(); // console function for drawing tile-like symbols
        void conOpen(int x, int y);
        void forceOpen(); // shows all mines
    //public:
        Field();
        ~Field(); // temporarily unused
        char** conTiles;
        Tile** Tiles; //2d array
};
#endif
