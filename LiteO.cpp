#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

/*
Anggota Kelompok:
Angelique Gabriel
Bintang Rahmadi
Hudayullah Ayasya Khoirizal

Credit:
Main Program:
Void TitleCard: Hudayulah
void printBoard: Hudayullah
*/

void titleCard();
void printBoard(char board[21][51]);

int main()
{

    titleCard();

    char mainBoard[21][51];

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 51; j++)
        {
        }
    }

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

void printBoard(char board[21][51])
{
}
