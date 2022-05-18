#ifndef FIELD_H
#define FIELD_H
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include "tile.h"
#include "gbutton.h"
class Field : public QWidget{
        Q_OBJECT;
        bool status;
        bool started; // whether first tile is opened or not
    public:
        Field(int fX, int fY, int mines, QWidget *parent = NULL);
        ~Field();
        int fX, fY; // size of field
        int mines; // number of mines in field
        bool exists(int x, int y); // checks whether cell(x,y) exists or not; used for recursive call/when checking on edge
        void open(int x, int y); // opens current Tiles[x][y]
        void openAll(); // used if player has lost
        bool checkWin(); // determines whether all empty cells are opened or not
        void setMines();
        Tile** Tiles;
        GameMainButton *gmbutton;
    // paint event
        //virtual void paintEvent(QPaintEvent *event) override;
    // signal handlers
    protected slots:
        void onTileLMBreleased();
        void onTileLMBpressed();
        void onTileRMBreleased();
        void ongmButtonLMBpressed();
        void ongmButtonLMBreleased();
    //signals:
        //void start();
        //void finish(); // for external use
};
#endif
