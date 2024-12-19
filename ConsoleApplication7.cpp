//main
#include <iostream>
#include <cmath>
#include <iomanip>
#include <clocale>
#include <fstream>
#include <string>
#include <time.h> 
#include <vector>
#include <cstdlib>

#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int buf;
	string num;
	ifstream ist("ist.txt");
	if (!ist.is_open()) cout << "Не удалось открыть файл 'ist.txt' !";
	std::vector <CAR> data;
	load_txt(ist, data);
	ist.close();
	ifstream ist2("ist2.txt");
	if (!ist2.is_open()) cout << "Не удалось открыть файл 'ist2.txt' !";
	load_txt(ist2, data);
	ist2.close();
	cout << "Выберите режим работы: " << endl << "1 - Вывести все номера машин с датами их проезда + опциональная сортировка" << endl << "2 - Найти дату проезда машины по её номеру" << endl;
	cin >> buf;
	switch (buf) {
	case 1:
		cout << "Выполнить сортировку по датам?" << endl << "1 - Да, 2 - Нет" << endl;
		cin >> buf;
		switch (buf) {
		case 1:
			car_sort(data);
			print_all_cars(data);
			break;
		case 2:
			print_all_cars(data);
			break;
		}

		break;
	case 2:
		cout << "Введите номер машины" << endl;
		cin >> num;
		find_car(data, num);
		break;
	}
}
