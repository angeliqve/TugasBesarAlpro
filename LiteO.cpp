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
void topBottom: Hudayullah
void printBoard: Hudayullah
*/

void titleCard();
void topBottomBoard();
void printBoard(string board[21][51], int score);
void SwitchChoice(int choice);

int main()
{

    int choice, score;

    titleCard();
    string mainBoard[21][51];

    /*
        Di modul tugas, disuruh untuk tabel berukuran 20, dan 50.
        Tapi di contoh tabel terhitung panjang 21, dan lebar 51.
        Jadi Diasumsikan bahwa tabel dihitung dimulai dari 0.
        jadi panjangnya adalah 0-20, dan lebarnya berukuran 0-50.
    */

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            mainBoard[i][j] = " ";
        }
    }

    printBoard(mainBoard, choice);

    cout << R"(

Menu: 
1. Tambah Hadiah
2. Tambah gerak O
3. Simulasi Lite O
4. Keluar
Masukkan Menu: )";

    cin >> choice;
    SwitchChoice(choice);
    if (choice == 4)
    {
        return 0;
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

void topBottomBoard()
{
    cout << "|";
    for (int i = 0; i < 51; i++)
        cout << "-";
    cout << "|" << endl;
}

void printBoard(string board[21][51], int score)
{
    topBottomBoard();

    for (int i = 0; i < 21; i++)
    {
        cout << "|";
        for (int j = 0; j < 51; j++)
        {
            cout << board[i][j];
        }
        cout << "|" << endl;
    }

    topBottomBoard();
    cout << "\nSkor O: " << score << endl;
}

void SwitchChoice(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "ADD GIFT";
        break;
    case 2:
        cout << "ADD MOVEMENT";
        break;
    case 3:
        cout << "SIMULATION";
        break;
    case 4:
        cout << "Exiting Program...";
        break;
    default:
        cout << "ERROR! input tidak valid, coba lagi!";
        SwitchChoice(choice);
    }
}

/*
 */
