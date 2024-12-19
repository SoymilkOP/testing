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
	if (!ist.is_open()) cout << "�� ������� ������� ���� 'ist.txt' !";
	std::vector <CAR> data;
	load_txt(ist, data);
	ist.close();
	ifstream ist2("ist2.txt");
	if (!ist2.is_open()) cout << "�� ������� ������� ���� 'ist2.txt' !";
	load_txt(ist2, data);
	ist2.close();
	cout << "�������� ����� ������: " << endl << "1 - ������� ��� ������ ����� � ������ �� ������� + ������������ ����������" << endl << "2 - ����� ���� ������� ������ �� � ������" << endl;
	cin >> buf;
	switch (buf) {
	case 1:
		cout << "��������� ���������� �� �����?" << endl << "1 - ��, 2 - ���" << endl;
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
		cout << "������� ����� ������" << endl;
		cin >> num;
		find_car(data, num);
		break;
	}
}
