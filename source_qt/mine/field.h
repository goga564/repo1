#ifndef FIELD_H
#define FIELD_H
#include "tile.h"
class Field : public QWidget{
        Q_OBJECT;
        bool status;
    public:
        Field(QWidget *parent = NULL);
        ~Field();
        /*const static*/ int fX,fY; // size of field
        //
        int mines; // number of mines in field
        bool exists(int x, int y); // checks whether cell(x,y) exists or not; used for recursive call/when checking on edge
        void open(int x, int y); // opens current Tiles[x][y]
        void openAll(); // used if player has lost
        bool checkWin(); // determines whether all empty cells are opened or not
    // random index generator
        int genrIndex(int upper);
        Tile** Tiles;
    // signal handlers
    protected slots:
        void onLMB();
        void onRMB();
    signals:
        void finish(); // block interaction with game field
};
#endif
