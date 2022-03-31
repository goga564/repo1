//#include <iostream>
class Game{
    Game(){};
    ~Game(){};
    void init();
    bool is_end;
    int mineleft;

};
class Tile{
    Tile(){};
    ~Tile(){};
    bool cellstate;
    bool minepresence;
    bool LMBclicked(){

    }
    bool RMBclicked(){

    }
    int idtexture;
};
class Field{
    Field(){};
    ~Field(){};
};
class MineCount{
    MineCount(){};
    ~MineCount(){};
    int mineleftfunc();
};
class Time{
    Time(){};
    ~Time(){};
    float sessiontime;
};
class Settings{
    Settings(){};
    ~Settings(){};
    int gamemode;
    int windowmode;
};
class Stats{
    Stats(){};
    ~Stats(){};
    int wins;
    int loses;
    int laps;
};
int main()
{

    return 0;
}
