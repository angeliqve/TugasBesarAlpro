#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>
using namespace std;

/*
Anggota Kelompok:
1. Angelique Gabriel
2. Bintang Rahmadi
3. Hudayullah Ayasya Khoirizal
*/

typedef struct
{
    string x;
    string y;
} coordinates;

struct Hadiah{
    int x, y;
    string nama;
    int skor;
};

void titleCard();
void topBottomBoard(string board[21][51]);
void printBoard(string board[21][51], int score);
void menu(char &choice);
void SwitchChoice(char &choice);
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
    /*
        Di modul tugas, disuruh untuk tabel berukuran 20, dan 50.
        Tapi di contoh tabel terhitung panjang 21, dan lebar 51.
        Jadi Diasumsikan bahwa tabel dihitung dimulai dari 0.
        jadi panjangnya adalah 0-20, dan lebarnya berukuran 0-50.
    */

    int score = 0;
    coordinates movement[100];
    char choice;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            mainBoard[i][j] = " ";
        }
    }

    while (infLoop)
    {
        vector<coordinates> tampungan;

        importtgerak(tampungan);

        titleCard();

        printBoard(mainBoard, score);
        menu(choice);

        if (choice == '3')
        {
            animation(tampungan, mainBoard, score);
        }
        else if (choice == '4')
        {
            return 0;
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
    SwitchChoice(choice);
}

void SwitchChoice(char &choice)
{
    switch (choice)
    {
    case '1':
        cout << "ADD GIFT";
        break;
    case '2':
        cout << "ADD MOVEMENT";
        break;
    case '3':
        break;
    case '4':
        cout << "Exiting Program...";
        break;
    default:
        cout << "ERROR! input tidak valid, coba lagi!";
        menu(choice);
    }
}

void wait(float x)
{
    time_t start;
    time_t current;
    time(&start);
    do
        time(&current);
    while (difftime(current, start) < x);
}

void importtgerak(vector<coordinates> &tampungan)
{
    coordinates data;
    int jumlahData = 0;

    fstream gerak("tgerak.txt", ios::in);
    if (!gerak)
    {
        cout << "Gagal membuka file.\n";
        return;
    }
    gerak >> data.x >> data.y;
    if (data.x == "##")
    {
        cout << "arsip kosong" << endl;
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
        // cout << "X: " << coord.x << "\tY: " << coord.y << endl;
        int x = stoi(coord.x);
        int y = stoi(coord.y);

        titleCard();

        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 51; j++)
            {
                mainBoard[i][j] = " ";
            }
        }

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
        isidata.push_back(baris);
    }
}

vector<Hadiah> listHadiah;

void bacaHadiah(){
    ifstream file("thadiah.txt");

    if(!file){
        cout << "File tidak ditemukan atau gagal dibuka.\n";
        return;
    }

    Hadiah h;
    while(file >> h.x >> h.y >> h.nama >> h.skor){
        listHadiah.push_back(h);
    }
    file.close();
}

void simpanHadiah(Hadiah &h){
    ofstream file("thadiah.txt", ios::app); // append mode
    if (!file){
        cout << "Gagal menyimpan ke file.\n";
        return;
    }
    file << h.x << " " << h.y << " " << h.nama << " " << h.skor << endl;

    file << "## ## ## ##" << endl;
    file.close();
}

void tambahHadiah(){
    cout << "Isi hadiah saat ini:" << endl;
    cout << "---------------------------" << endl;
    cout << "|x    |y    |nama  |skor  |" << endl;
    cout << "---------------------------" << endl;
    for (auto &h : listHadiah) {
        cout << "|" << h.x << "    |" << h.y << "    |" << h.nama << "  |" << h.skor << "  |" << endl;
    }
    cout << "---------------------------" << endl;

    char lanjut;
    cout << "ingin mengisi: (Y/T) ";
    cin >> lanjut;
    if (lanjut == 'Y' || lanjut == 'y') {
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
