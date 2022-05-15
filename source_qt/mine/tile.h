#ifndef TILE_H
#define TILE_H
#include <QPushButton>
class Tile : public QPushButton {
        Q_OBJECT;
        bool cState; // status of cell; 0-closed,1-opened
        bool minePres; // presence of mine; 0-no,1-in presence
        int texId; // 0-opened,1-closed;2-flagged closed,3-marked closed - all states used to distinguish opened cell and
    public:
        Tile(QWidget *parent = NULL);
        Tile(int X, int Y, QWidget *parent = NULL);
        Tile& operator =(const Tile& tile){ // assignment
            if(this != &tile){ // self-assignment avoidance
                x = tile.x;
                y = tile.y;
                cState = tile.cState;
                inVicinity = tile.inVicinity;
                minePres = tile.minePres;
                texId = tile.texId;
            }
            return *this;
        }
        int x, y; // x,y
        int getX();int getY(); // get x, y
        void setOpen(); // set open
        bool getState(); // whether is opened or closed
        bool isMined(); // get minepresence
        void setMine(); // sets mine to cell while init;
        int inVicinity; // number of mines in surrounding area(8 cells) of current; used when placing mines
        void changeTexSt(); // put;
    // paint event
        virtual void setTex(QPaintEvent *event);
    // mouse event
        virtual void mouseReleaseEvent(QMouseEvent *event);
    // signals
    signals:
        void LMBsignal();
        void RMBsignal();
};
#endif
