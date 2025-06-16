#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <iomanip>
using namespace std;

/*
Anggota Kelompok:
1. Angelique Gabriel
2. Bintang Rahmadi
3. Hudayullah Ayasya Khoirizal

credit:
struct coordinates: Huda
struct Hadiah     : Bintang
vector listHadiah : Angel
void titlecard    : Huda
void PrintBoard   : Huda
void topBottom    : Huda
void menu         : Huda
void wait         : Bintang
void importtgerak : Huda
void animation    : Huda
void editTgerak   : Huda
void bacaHadiah   : Angel
void simpanHadiah : Angel
void tambahHadiah : Bintang

Main Program      : Angel, Bintang,& Huda

*/

typedef struct
{
    string x;
    string y;
} coordinates;

struct Hadiah
{
    int x, y;
    string nama;
    int skor;
};

vector<Hadiah> listHadiah;

void titleCard();
void topBottomBoard();
void printBoard(string board[21][51], int score);
void menu(char &choice);
void wait(float x);
void importtgerak(vector<coordinates> &tampungan);
void animation(vector<coordinates> &tampungan, string mainBoard[21][51], int score);
void editTgerak();
void bacaHadiah();
void simpanHadiah(Hadiah &h);
void tambahHadiah();

int main()
{
    bool infLoop = true;
    string mainBoard[21][51];
    int score = 0;
    char choice;

    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 51; j++)
            mainBoard[i][j] = " ";

    bacaHadiah(); // load hadiah on startup

    while (infLoop)
    {
        vector<coordinates> tampungan;
        importtgerak(tampungan);

        titleCard();
        printBoard(mainBoard, score);

        do
        {
            menu(choice);
            switch (choice)
            {
            case '1':
                tambahHadiah();
                break;
            case '2':
                editTgerak();
                break;
            case '3':
                animation(tampungan, mainBoard, score);
                break;
            case '4':
                cout << "Exiting Program..." << endl;
                return 0;
                break;
            default:
                cout << "\nERROR! Input tidak Valid! Coba Lagi:\n\n";
            }
        } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
    }
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
    // Generated using https://patorjk.com/software/taag/#p=display&f=Sub-Zero&t=Lite-O with the font Doom
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

void menu(char &choice)
{
    cout << R"(
Menu: 
1. Tambah Hadiah
2. Tambah gerak O
3. Simulasi Lite O
4. Keluar
Masukkan Menu: )";

    cin >> choice;
}

void wait(float x)
{
    time_t start, current;
    time(&start);
    do
        time(&current);
    while (difftime(current, start) < x);
}

void importtgerak(vector<coordinates> &tampungan)
{
    coordinates data;

    fstream gerak("tgerak.txt", ios::in);
    if (!gerak)
    {
        cout << "Gagal membuka file.\n";
        return;
    }

    gerak >> data.x >> data.y;
    if (data.x == "##")
    {
        cout << "Arsip kosong." << endl;
    }
    else
    {
        do
        {
            tampungan.push_back(data);
            gerak >> data.x >> data.y;
        } while (data.x != "##");

        gerak.close();
    }
}

void animation(vector<coordinates> &tampungan, string mainBoard[21][51], int score)
{
    for (const auto &coord : tampungan)
    {
        int x = stoi(coord.x);
        int y = stoi(coord.y);

        titleCard();

        for (int i = 0; i < 21; i++)
            for (int j = 0; j < 51; j++)
                mainBoard[i][j] = " ";

        mainBoard[y][x] = "O";
        printBoard(mainBoard, score);
        wait(1);
        system("cls");
    }
}

void editTgerak()
{
    vector<string> isidata;
    string baris;
    int x, y;

    cout << "\nInputkan koordinat gerak O: \n";
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;

    string stringX = to_string(x);
    string stringY = to_string(y);

    fstream gerak("tgerak.txt", ios::in);
    if (!gerak)
    {
        cout << "Gagal membuka file.\n";
        return;
    }

    while (getline(gerak, baris))
    {
        if (baris == "## ##")
        {
            break;
        }
        isidata.push_back(baris);
    }
    gerak.close();

    isidata.push_back(stringX + " " + stringY);

    fstream putUpdated("tgerak.txt", ios::out);
    for (const string &line : isidata)
    {
        putUpdated << line << endl;
    }

    putUpdated << "## ##\n";
    putUpdated.close();

    cout << "\nPergerakkan Koordinat sudah diperbarui.\n";
}

void bacaHadiah()
{
    ifstream file("thadiah.txt");

    if (!file)
    {
        cout << "File tidak ditemukan atau gagal dibuka.\n";
        return;
    }

    Hadiah h;
    while (file >> h.x >> h.y >> h.nama >> h.skor)
    {
        listHadiah.push_back(h);
    }
    file.close();
}

void simpanHadiah(Hadiah &h)
{
    ofstream file("thadiah.txt", ios::app);
    if (!file)
    {
        cout << "Gagal menyimpan ke file.\n";
        return;
    }

    file << h.x << " " << h.y << " " << h.nama << " " << h.skor << endl;
    file.close();
}

void tambahHadiah()
{
    cout << "Isi hadiah saat ini:\n";
    cout << "-------------------------------\n";
    cout << left << setw(6) << "|x" << setw(6) << "|y" << setw(10) << "|nama" << setw(6) << "|skor|\n";
    cout << "-------------------------------\n";

    for (auto &h : listHadiah)
    {
        cout << "|" << setw(5) << h.x
             << "|" << setw(5) << h.y
             << "|" << setw(9) << h.nama
             << "|" << setw(5) << h.skor << "|\n";
    }

    cout << "-------------------------------\n";

    char lanjut;
    cout << "Ingin mengisi? (Y/T): ";
    cin >> lanjut;

    if (lanjut == 'Y' || lanjut == 'y')
    {
        Hadiah h;
        cout << "x: ";
        cin >> h.x;
        cout << "y: ";
        cin >> h.y;
        cout << "nama: ";
        cin >> h.nama;
        cout << "skor: ";
        cin >> h.skor;

        listHadiah.push_back(h);
        simpanHadiah(h);
    }
}
/*
BackUp incase anything goes wrong:

tgerak:
0 0
0 1
0 2
0 3
0 4
0 5
1 5
2 5
3 5
4 5
5 5
6 5
7 5
8 5
9 5
10 5
10 6
10 7
## ##

thadiah:
5 5 aa 5
10 5 ab 10
25 10 ac 5
15 15 ad 10
30 15 ae 5
40 17 af 20
## ## ## ##

 */

