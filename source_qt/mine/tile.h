#ifndef TILE_H
#define TILE_H
#include <QWidget>
#include <QPushButton>
class Tile : public QPushButton {
        Q_OBJECT;
        int x, y; // x,y
        bool cState; // status of cell; 0-closed, 1-opened
        int minePres; // presence of mine; 0-no, 1-mine, 2-red mine
        int texId; // 0-opened, 1-closed; 2-flagged closed, 3-marked closed, 4-flagged closed wrong, 5-marked opened
    public:
        Tile(QWidget *parent = NULL);
        Tile(int X, int Y, QWidget *parent = NULL);
        ~Tile();
        Tile& operator =(const Tile &tile);
        int getX(); int getY(); // get x, y
        void setOpen(); // set open
        bool getState(); // whether is opened or closed
        int getTexId(); // get texId
        int isMined(); // get minepresence
        void setMine(); // sets mine to cell while init;
        void setMineRed(); // highlight the mine you blew up
        void unsetMine(); // if tile were clicked for the first time
        int inVicinity; // number of mines in surrounding area(8 cells) of current
    // texture map
        QPixmap* sprite;
    // texture handlers
        void changeTexRMB(); // change state to flag or question mark
        void changeTexToOpen(); // preparation to opening
        void changeTexToWrong(); // wrong place to flag
    // paint event
        virtual void paintEvent(QPaintEvent *event) override;
    // mouse events
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
    // signals
    signals:
        void LMBreleased();
        void LMBpressed();
        void RMBpressed();
};
#endif
