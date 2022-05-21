/* unfinished */
#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include "tile.h"
#include "field.h"
#include "gbutton.h"
class MainGame : public QWidget {
        Q_OBJECT
    public:
        MainGame(QWidget *parent = nullptr);
        Field* field;
        GameMainButton* gmbut;
    public slots:
        //reset();
};
#endif
