//#include "classes.h"
//#include "game.h"
#include <iostream>
#include <cstdlib>
#include "windows.h"
#include "field.h"
#include <random>
using namespace std;
int main()
{
    //console variant
    Field* A = new Field;
    cout << endl << endl << "Press any key to start . . .";
    system("pause>void");
    system("cls");
    int x, y, s;
    bool checklose = 0;
    do{
        cout << "X - closed tile, O - opened tile without number, 1..8 - opened tile with number of mines in vicinity, ! - flag, * - bomb" << endl << endl;
        cout << "Current Field: " << endl;
        A->conDraw();
        cout << endl << "Commands: " ;
        cout << "1. Open(x,y) 2. Set Flag 3. (algorithm work check) Show bomb pos 4. exit" << endl;
        cin >> s;
        switch(s){
            case 1:{
                cout << endl << "tile to open ( >> x >> y): ";
                cin >> y >> x; // y is x and x is y
                cout << endl;
                if (!(A->exists(x,y))){
                    system("cls");
                    cout << "MESSAGE FROM GAME SESSION: conTiles[" << y << "][" << x << "] does not exist" ;
                    break;
                }
                if (A->Tiles[x][y].getState()){
                    system("cls");
                    cout << "MESSAGE FROM GAME SESSION: conTiles[" << y << "][" << x << "] is already opened" ;
                    break;
                }
                if (A->Tiles[x][y].isMined()){
                    cout << "MESSAGE FROM GAME SESSION: conTiles[" << y << "][" << x << "] is mined, looks like you have lost . . ." ;
                    checklose = 1;
                }
                else{
                    system("cls");
                    A->conOpen(x,y);
                }
                break;
            }
            case 2:{
                cout << endl << "set flag to: ( >> x >> y): " ;
                cin >> y >> x; // y is x and x is y
                cout << endl;
                system("cls");
                if(!(A->exists(x,y))){
                    system("cls");
                    cout << "MESSAGE FROM GAME SESSION: conTiles[" << y << "][" << x << "] does not exist" ;
                    break;
                }
                if(A->Tiles[x][y].getState()){
                    system("cls");
                    cout << "MESSAGE FROM GAME SESSION: no need of it, conTiles[" << y << "][" << x << "] is opened. " ;
                    break;
                }
                else{
                    A->conTiles[x][y] = '!';
                }
                break;
            }
            case 3:
                system("cls");
                A->forceOpen();
                break;
            case 4:
                checklose = 1;
                //return 1;
                break;
        }
        cout << endl;
    }while(!(A->checkWin()) && !checklose);
    delete A;
    return 0;
}
