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

struct Hadiah
{
    int x, y;
    string nama;
    int skor;
};

struct Gerak 
{
    int x, y;
};

int panjang, lebar;
vector<Hadiah> daftarHadiah;
vector<Gerak> daftarGerak;

void titleCard();
void batasPapan();
void tampilkanPapan(int x, int y, int skor, vector<Hadiah> adaHadiah);
void animasiLiteO();
void menu(int &pilihan);
void wait(float x);
void bacaHadiah();
void simpanHadiah(Hadiah &h);
void tambahHadiah();
void bacaGerak();
void simpanGerak();
void tambahGerak();

int main() 
{
    cout << "Masukkan panjang papan: ";
    cin >> panjang;
    cout << "Masukkan lebar papan: ";
    cin >> lebar;
    int pilihan;

    titleCard();

    do {
        menu(pilihan);
        switch (pilihan) 
        {
            case 1:
                tambahHadiah();
                break;
            case 2:
                tambahGerak();
                break;
            case 3:
                animasiLiteO();
                break;
            case 4:
                cout << "Exiting Program..." << endl;
                return 0;
                break;
            default:
                cout << "ERROR! Input tidak Valid! Coba Lagi.\n";
                break;
        }
    } while (true);
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
    // Generated using https://patorjk.com/software/taag/#p=display&f=Sub-Zero&t=Lite-O with the font Doom
}

void batasPapan()
{
    cout << "|";
    for (int i = 0; i < lebar; i++)
    {
        cout << "-";
    }
    cout << "|" << endl;
}

void tampilkanPapan(int x, int y, int skor, vector<Hadiah> adaHadiah) 
{
    batasPapan();

    for (int i = 0; i < panjang; i++) 
    {
        cout << "|";
        for (int j = 0; j < lebar; j++) 
        {
            bool adaIsi = false;

            if (i == y && j == x) {
                cout << "O";
                adaIsi = true;
            } else {
                for (auto &h : adaHadiah) 
                {
                    if (h.x == j && h.y == i) {
                        string isi = h.nama + to_string(h.skor);
                        cout << isi;
                        j += isi.length() - 1; 
                        adaIsi = true;
                        break;
                    }
                }
            }

            if (!adaIsi){
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    batasPapan();

    cout << "Skor O: " << skor << endl;
}

void animasiLiteO() 
{
    bacaHadiah();
    bacaGerak();
    int skor = 0;
    vector<Hadiah> aktif = daftarHadiah;
    for (auto &g : daftarGerak)
    {
        system("cls");
        for (auto it = aktif.begin(); it != aktif.end();) 
        {
            if (it->x == g.x && it->y == g.y) {
                skor += it->skor;
                it = aktif.erase(it);
            } else {
                ++it;
            }
        }
        tampilkanPapan(g.x, g.y, skor, aktif);
        wait(1);
    }
}

void menu(int &pilihan)
{
    cout << "\nMenu:\n1. Tambah Hadiah\n2. Tambah Gerak O\n3. Simulasi Lite O\n4. Keluar\nMasukkan Pilihan Menu: ";
    cin >> pilihan;
}

void wait(float x) 
{
    time_t start, current;
    time(&start);
    do 
    {
        time(&current);
    } while (difftime(current, start) < x);
}

void simpanHadiah() 
{
    ofstream update("thadiah.txt");
    if (!update){
        cout << "Gagal menyimpan ke file.\n";
        return;
    }

    for (auto &h : daftarHadiah) 
    {
        update << h.x << ' ' << h.y << ' ' << h.nama << ' ' << h.skor << endl;
    }

    update << "## ## ## ##\n";
    update.close();
}

void bacaHadiah() 
{
    daftarHadiah.clear();
    ifstream hadiah("thadiah.txt");
    if(!hadiah){
        cout << "File tidak ditemukan atau gagal dibuka.\n";
        return;
    }

    Hadiah h;
    while (hadiah >> h.x >> h.y >> h.nama >> h.skor) 
    {
        daftarHadiah.push_back(h);
    }
    hadiah.close();
}

void tambahHadiah() 
{
    bacaHadiah();
    cout << "Isi hadiah saat ini:\n";
    cout << "---------------------------\n";
    cout << "|  x  |  y  | nama | skor |\n";
    cout << "---------------------------\n";

    for (auto &h : daftarHadiah)
    {
        cout << "|" << left << setw(5) << h.x
             << "|" << left << setw(5) << h.y
             << "|" << left << setw(6) << h.nama
             << "|" << left << setw(6) << h.skor << "|\n";
    }

    cout << "---------------------------\n";

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

        daftarHadiah.push_back(h);
        simpanHadiah();
    }
}

void simpanGerak() 
{
    ofstream update("tgerak.txt");
    if (!update){
        cout << "Gagal menyimpan ke file.\n";
        return;
    }
    
    for (auto &g : daftarGerak) 
    {
        update << g.x << ' ' << g.y << endl;
    }
    update << "## ##\n";
    update.close();
}

void bacaGerak() 
{
    daftarGerak.clear();
    ifstream gerak("tgerak.txt");
    if (!gerak){
        cout << "Gagal membuka file.\n";
        return;
    }

    Gerak g;
    while (gerak >> g.x >> g.y) 
    {
        daftarGerak.push_back(g);
    }
    gerak.close();
}

void tambahGerak() 
{
    bacaGerak();
    cout << "Isi gerak saat ini:\n";
    cout << "-------------\n";
    cout << "|  x  |  y  |\n";
    cout << "-------------\n";
    for (auto &g : daftarGerak)
    {
        cout << "|" << setw(5) << g.x 
             << "|" << setw(5) << g.y << "|\n";
    }
    cout << "-------------\n";

    char lanjut;
    cout << "ingin mengisi? (Y/T): ";
    cin >> lanjut;
    while (lanjut == 'Y' || lanjut == 'y') 
    {
        Gerak g;
        cout << "x: "; 
        cin >> g.x;
        cout << "y: "; 
        cin >> g.y;
        daftarGerak.push_back(g);
        cout << "ingin mengisi lagi? (Y/T): ";
        cin >> lanjut;
    }
    simpanGerak();
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

