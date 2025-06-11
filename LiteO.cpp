#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

/*
Credit:
Main Program:
Void TitleCard: Hudayulah
void printBoard: Hudayullah
*/


void titleCard();
void printBoard();


int main()
{

    titleCard();

    char mainBoard [21][51] = {
        
    };



    return 0;
}

void titleCard()
{
    cout << R"(
 _     _ _              _____ 
| |   (_) |            |  _  |
| |    _| |_ ___ ______| | | |
| |   | | __/ _ \______| | | |
| |___| | ||  __/      \ \_/ /
\_____/_|\__\___|       \___/ 
                


)";

    // menggunakan https://patorjk.com/software/taag/#p=display&f=Sub-Zero&t=Lite-O dengan font DOOM
}

void printBoard(){
    
}
