//Patryk Kapusto

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>

#define closed 0 //lista zamkniêtych
#define opened 1 //lista otwartych

#define G 0 //koszt g
#define H 1 //koszt h
#define F 2 //koszt f

#define X 0 // Rodzic X
#define Y 1 //Rodzic Y

void loadMap();
void printMap();
void hValue();
void drawMap(int, int);
void setPoint();
void fMin();
void toClosed();
void explore();
void konflikt(int, int);

using namespace std;
//pozycja startowa
int start_x;
int start_y;
//poycja obecna
int poz_x;
int poz_y;
//pozycja koncowa
int cel_x;
int cel_y;
//pozycja fMin
int min_x;
int min_y;

int map[20][20];
bool list[2][20][20] = { false };
int cost[3][20][20] = { 0 };
int parent[2][20][20];



int main() {
	loadMap();
	printMap();
	for (int y = 0; y <= 19; y++) {
		for (int x = 0; x <= 19; x++) {
			//ustalamy ze nikt nie ma rodzica, wa¿ne by wywo³aæ przed podaniem punktó
			parent[X][x][y] = -1;
			parent[Y][x][y] = -1;
		}
	}
	setPoint();
	hValue(); //niezmienna dla danego pola


	bool check;


	while (poz_x != cel_x || poz_y != cel_y) {
		check = false;
		for (int y = 0; y <= 19; y++) {
			for (int x = 0; x <= 19; x++) {
				if (list[opened][x][y] == true) {
					check = true;
				}
			}
		}
		if (!check && cel_x != poz_x && cel_y != poz_y) {
			cout << endl << "Nie znaleziono trasy";
			break;
		}
		toClosed();
	}
	drawMap(cel_x, cel_y);
	printMap();


	cin.get();
	cin.get();
	return 0;
}
void explore() {
	//zgodnie ze wskazówkami zegara od 12

	//12
	if (poz_y != 19 && map[poz_x][poz_y + 1] != 5 && !list[closed][poz_x][poz_y + 1]) {
		if (!list[opened][poz_x][poz_y + 1]) {
			list[opened][poz_x][poz_y + 1] = true;
			parent[X][poz_x][poz_y + 1] = poz_x;
			parent[Y][poz_x][poz_y + 1] = poz_y;
			cost[G][poz_x][poz_y + 1] = cost[G][poz_x][poz_y] + 1;
			cost[F][poz_x][poz_y + 1] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y + 1];
		}
		else {
			if ((cost[F][poz_x][poz_y + 1]) > (cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y + 1])) {
				parent[X][poz_x][poz_y + 1] = poz_x;
				parent[Y][poz_x][poz_y + 1] = poz_y;
				cost[G][poz_x][poz_y + 1] = cost[G][poz_x][poz_y] + 1;
				cost[F][poz_x][poz_y + 1] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y + 1];
			}
		}
	}
	//3
	if (poz_x != 19 && map[poz_x + 1][poz_y] != 5 && !list[closed][poz_x + 1][poz_y]) {
		if (!list[opened][poz_x + 1][poz_y]) {
			list[opened][poz_x + 1][poz_y] = true;
			parent[X][poz_x + 1][poz_y] = poz_x;
			parent[Y][poz_x + 1][poz_y] = poz_y;
			cost[G][poz_x + 1][poz_y] = cost[G][poz_x][poz_y] + 1;
			cost[F][poz_x + 1][poz_y] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x + 1][poz_y];
		}
		else {
			if ((cost[F][poz_x + 1][poz_y]) > (cost[G][poz_x][poz_y] + 1 + cost[H][poz_x + 1][poz_y])) {
				parent[X][poz_x + 1][poz_y] = poz_x;
				parent[Y][poz_x + 1][poz_y] = poz_y;
				cost[G][poz_x + 1][poz_y] = cost[G][poz_x][poz_y] + 1;
				cost[F][poz_x + 1][poz_y] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x + 1][poz_y];
			}

		}
	}
	//6
	if (poz_y != 0 && map[poz_x][poz_y - 1] != 5 && !list[closed][poz_x][poz_y - 1]) {
		if (!list[opened][poz_x][poz_y - 1]) {
			list[opened][poz_x][poz_y - 1] = true;
			parent[X][poz_x][poz_y - 1] = poz_x;
			parent[Y][poz_x][poz_y - 1] = poz_y;
			cost[G][poz_x][poz_y - 1] = cost[G][poz_x][poz_y] + 1;
			cost[F][poz_x][poz_y - 1] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y - 1];
		}
		else {
			if ((cost[F][poz_x][poz_y - 1]) > (cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y - 1])) {
				parent[X][poz_x][poz_y - 1] = poz_x;
				parent[Y][poz_x][poz_y - 1] = poz_y;
				cost[G][poz_x][poz_y - 1] = cost[G][poz_x][poz_y] + 1;
				cost[F][poz_x][poz_y - 1] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x][poz_y - 1];
			}

		}
	}
	//9
	if (poz_x != 0 && map[poz_x - 1][poz_y] != 5 && !list[closed][poz_x - 1][poz_y]) {
		if (!list[opened][poz_x - 1][poz_y]) {
			list[opened][poz_x - 1][poz_y] = true;
			parent[X][poz_x - 1][poz_y] = poz_x;
			parent[Y][poz_x - 1][poz_y] = poz_y;
			cost[G][poz_x - 1][poz_y] = cost[G][poz_x][poz_y] + 1;
			cost[F][poz_x - 1][poz_y] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x - 1][poz_y];
		}
		else {
			if ((cost[F][poz_x - 1][poz_y]) > (cost[G][poz_x][poz_y] + 1 + cost[H][poz_x - 1][poz_y])) {
				parent[X][poz_x - 1][poz_y] = poz_x;
				parent[Y][poz_x - 1][poz_y] = poz_y;
				cost[G][poz_x - 1][poz_y] = cost[G][poz_x][poz_y] + 1;
				cost[F][poz_x - 1][poz_y] = cost[G][poz_x][poz_y] + 1 + cost[H][poz_x - 1][poz_y];
			}

		}
	}
}
void toClosed() {

	fMin();
	if (list[opened][min_x][min_y]) {
		list[opened][min_x][min_y] = false;
		list[closed][min_x][min_y] = true;
	}
	poz_x = min_x;
	poz_y = min_y;
	explore();
}
void fMin() {
	int min = 12345;
	for (int y = 0; y <= 19; y++) {
		for (int x = 0; x <= 19; x++) {
			if (list[opened][x][y] && cost[F][x][y] < min) {
				min = cost[F][x][y];
				min_x = x;
				min_y = y;
			}
		}
	}
}
void hValue() {
	//niezmienna
	for (int y = 0; y <= 19; y++) {
		for (int x = 0; x <= 19; x++) {
			cost[H][x][y] = abs(x - cel_x) + abs(y - cel_y);
		}
	}
}
void drawMap(int x, int y) {
	int x1 = x;
	int y1 = y;

	while (map[start_x][start_y] != 3) {
		map[x1][y1] = 3;
		x1 = parent[X][x1][y1];
		y1 = parent[Y][x1][y1];
	}
}
void printMap() {
	//przejœcie po wierszach (kolumny od do³u by zachowaæ kolejnoœæ uk³adu wsp.)
	for (int y = 19; y >= 0; y--) {
		cout << endl;
		//przejœcie po kolumnach
		for (int x = 0; x <= 19; x++) {
			cout << map[x][y] << " ";
		}
	}
}
void loadMap() {
	string napis;
	fstream file;
	file.open("grid.txt", ios::in);
	if (file.good()) {
		//przejscie po wierszu
		for (int y = 19; y >= 0; y--) {
			//wczytanie wiersza kolumnowo
			getline(file, napis);
			for (int x = 0; x <= 19; x++) {
				map[x][y] = (int)napis[x * 2] - 48; //konwersja na kod ASCII, 48 w ASCII to 0
			}
		}
		file.close();
	}
	else
		cout << "Nie udalo sie wczytac pliku";
}
void setPoint() {
	cout << endl << "Start X [0..19]:" << endl;
	cin >> start_x;
	cout << "Start Y [0..19]:" << endl;
	cin >> start_y;
	cout << "End X [0..19]:" << endl;
	cin >> cel_x;
	cout << "End Y [0..19]:" << endl;
	cin >> cel_y;
	poz_x = start_x;
	poz_y = start_y;
	cost[F][poz_x][poz_y] = -1;
	cost[G][poz_x][poz_y] = 0;
	list[opened][poz_x][poz_y] = true;
	parent[X][poz_x][poz_x] = poz_x;
	parent[Y][poz_x][poz_y] = poz_y;

}
