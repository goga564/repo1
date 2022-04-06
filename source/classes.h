#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include "tile.h"
#include "field.h"
/*class MineCount{
    public:
        MineCount(){};
        ~MineCount(){};
        int mineleftfunc();
};*/
class Time{
    public:
        Time(){};
        ~Time(){};
        float sessiontime;
};
class Settings{
    public:
        Settings(){};
        ~Settings(){};
        int gamemode;
        int windowmode;
};
/*class Stats{       //currently unused
    public:
        Stats(){};
        ~Stats(){};
        int wins;
        int loses;
        int laps;
};*/
class Game{
    Field *objfield;
    //MineCount *objmine;
    Time *objtime;
    Settings *objsets;
    //Stats *objstats;
    Game(){
        objfield=new Field;
        //objmine=new MineCount;
        objtime=new Time;
        objsets=new Settings;
        //objstats=new Stats;
    };
    ~Game(){};
    //bool is_end;
    //int mineleft;
};
#endif // CLASSES_H_INCLUDED
