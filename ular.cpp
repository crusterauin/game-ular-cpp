#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using namespace std;

const int panjang = 80;
const int lebar = 20;

int x, y;
int tikusX, tikusY;
int skor;
int ekorX[100], ekorY[100];
int panjangEkor;
enum gerak { STOP = 0, KIRI, KANAN, ATAS, BAWAH};
gerak grk;
bool isSelesai;
bool isPosisiEkor(int x, int y);

void mulai()
{
	isSelesai = false;
	grk = STOP;
	x = panjang / 2;
	y = lebar / 2;
	tikusX = rand() % panjang;
	tikusY = rand() % lebar;
	skor = 0;
}

void render(string namaPemain)
{
    system("cls");

    for (int i = 0; i < lebar + 2; i++) {
        for (int j = 0; j < panjang + 2; j++) {
            if (i == 0 || i == lebar + 1) {
                cout << "-";
            } else {
                if (j == 0 || j == panjang + 1) {
                    cout << "|";
                } else {
                    if (i == y && j == x) {
                        cout << "*";
                    } else if (i == tikusY && j == tikusX) {
                        cout << "#";
                    } else {
                        bool ekor = false;
                        for (int k = 0; k < panjangEkor; k++) {
                            if (ekorX[k] == j && ekorY[k] == i) {
                                cout << "0";
                                ekor = true;
                            }
                        }
                        if (!ekor) {
                            cout << " ";
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    cout << "Skor " << namaPemain << " : "<< skor << endl;
}

void update()
{
    int prevX = ekorX[0];
    int prevY = ekorY[0];
    int prev2X, prev2Y;
    ekorX[0] = x;
    ekorY[0] = y;

    for (int i = 1; i < panjangEkor; i++) {
        prev2X = ekorX[i];
        prev2Y = ekorY[i];
        ekorX[i] = prevX;
        ekorY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (grk) {
        case KIRI:
            x = (x - 1 + panjang) % panjang;
            break;
        case KANAN:
            x = (x + 1) % panjang;
            break;
        case ATAS:
            y = (y - 1 + lebar) % lebar;
            break;
        case BAWAH:
            y = (y + 1) % lebar;
            break;
    }

    if (isPosisiEkor(x, y)) {
        isSelesai = true;
    }

    if (x == tikusX && y == tikusY) {
        skor += 1;
        do {
            tikusX = rand() % panjang + 1;
            tikusY = rand() % lebar + 1;
        } while (isPosisiEkor(tikusX, tikusY));
        panjangEkor++;
    }
}


int levelGame()
{
    int level, pilih;
    cout << "PILIH LEVEL!\n1:Mudah\n2:Sedang\n3:Sulit\n";
    cin >> pilih;
    switch (pilih) {
        case 1:
            level = 100;
            break;
        case 2:
            level = 50;
            break;    
        case 3:
            level = 1;
            break;
        default:
            level = 50;
    }
    return level;    
}

void inputGerakan() {
	if (_kbhit()) {
		switch (_getch()) {
			case 'a':
				grk = KIRI;
				break;
			case 'd':
				grk = KANAN;
				break;
			case 'w':
				grk = ATAS;
				break;
			case 's':
				grk = BAWAH;
				break;
			case 'x':
				isSelesai = true;
				break;
		}
	}
}

bool isPosisiEkor(int x, int y)
{
    for (int i = 0; i < panjangEkor; i++) {
        if (ekorX[i] == x && ekorY[i] == y) {
            return true;
        }
    }
    return false;
}

int main()
{
    string namaPemain;
    cout << "Siapa namamu?\n";
    cin >> namaPemain;
    int level = levelGame();

    mulai();
    while (!isSelesai) {
        render(namaPemain);
        inputGerakan();
        update();
        Sleep(level);
    }

    cout << "Anda kalah!" << endl;

    return 0;
}

