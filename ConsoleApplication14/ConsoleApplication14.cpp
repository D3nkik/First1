#include <iostream>
#include <utility>//Для pair
#include <windows.h>
#include <conio.h>// изменяем цвет и считываем действие с клавиш
#include <fstream>//работа с файлами
#include <string>
#define X 10
#define Y 10

using namespace std;

const int xField = X;//ширина 
const int yField = Y;//длина
char field[xField][yField];
bool won = false;

struct Map {
	pair< int, int> start_pos;
	pair< int, int> end_pos; //основная инфа по карте
	pair< int, int> player_pos;
};
Map map;
void pobeda() {
	system("cls");
	system("color 2F");
	cout << "Вы выиграли" << endl;
	cin.get(); //ждем нажатия клавиши
	exit (0);
}

void proigrish() {
	system("cls");
	system("color 4F");
	cout << "Вы проиграли" << endl;
	cin.get();
	exit(0);
}

void zapolnenie_poly() {
	system("cls");
	field[map.player_pos.first][map.player_pos.second] = '@';
	for (int i = 0; i < xField; i++) {                                  // рисуем поле
		for (int j = 0; j < yField; j++) {
			if (field[j][i] == '#' || field[j][i] == '@') {
				cout << field[j][i];
			}
			else {
				cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

void update() {
	if(_kbhit()){
		switch (_getch()) {
		case 'w':
			if (field[map.player_pos.first][map.player_pos.second - 1] != '#') {
				field[map.player_pos.first][map.player_pos.second] = '#';
				map.player_pos.second--;
			}
			break;
		case 'a':
			if (field[map.player_pos.first - 1][map.player_pos.second] != '#') {
				field[map.player_pos.first][map.player_pos.second] = '#';
				map.player_pos.first--;
			}
			break;                                                              //управление игроком
		case 's':
			if (field[map.player_pos.first][map.player_pos.second + 1] != '#') {
				field[map.player_pos.first][map.player_pos.second] = '#';
				map.player_pos.second++;
			}
			break;
		case 'd':
			if (field[map.player_pos.first + 1][map.player_pos.second] != '#') {
				field[map.player_pos.first][map.player_pos.second] = '#';
				map.player_pos.first++;
			}
			break;
	}
		if (map.player_pos.first == map.end_pos.first && map.player_pos.second == map.end_pos.second) {
			won = true;    //для выигрыша
			pobeda();
		}
		if (field[map.player_pos.first + 1][map.player_pos.second] == '#' && field[map.player_pos.first][map.player_pos.second + 1] == '#') {
			proigrish();
			
		}
		zapolnenie_poly();
	}
}
//sfml - болчный интерфейс 

void initialize() {
	//SetConsoleTitle("Labirint C++");
	system("color 06");
	system("cls");
	cout << "[Игра в лабиринте]" << endl;
	cout << "Напишите play для того чтобы начать игру, или exit чтобы закрыть окно" << endl;
}

int main(void) {
	string path = "level.txt";
	ifstream fin(path);
	if (fin.is_open()) {
		cout << "file is open";
	}
	setlocale(LC_ALL, "Russian");
	initialize();
	string cmd = "";
	getline(cin, cmd);
	if (cmd == "play") {
		ifstream file("level.txt");
		string srs = "";
		int counter = 0;
		while (counter < yField) {
			getline(file, srs);
			cout << srs << endl;
			for (int i = 0; i < xField; i++) {
				field[i][counter] = char(srs[i]);
				if (field[i][counter] == 'e') {
					map.start_pos.first = i;
					map.start_pos.second = counter;
					map.player_pos.first = map.start_pos.first;
					map.player_pos.second = map.start_pos.second;
				}
				if (field[i][counter] == 's') {
					map.end_pos.first = i;
					map.end_pos.second = counter;
				}
			}
			counter++;
		}
		system("cls");
		zapolnenie_poly();
		while (!won) {
			update();
		}
	}
	else if (cmd == "exit") {
		exit(0);
	}
	else {
		cout << "Неизвестная команда, нажмите любую кнопку для выхода" << endl;
	}
	return 0;
}