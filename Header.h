//header
#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include <clocale>
#include <fstream>
#include <string>
#include <time.h> 
#include <vector>
#include <cstdlib>
#include <regex>

using namespace std;

class CAR {
public:
	string year;
	string month;
	string day;
	string number;

public:

	CAR() {};

	CAR(string newyear, string newmonth, string newday, string newnumber);
	int totalday();

};

std::vector <CAR> load_txt(ifstream &ist, std::vector <CAR> &data);
void print_all_cars(const std::vector <CAR> &data);
void validate_date(const std::string& day, const std::string& month, const std::string& year);
void validate_number(const std::string& number);
void car_sort(std::vector <CAR> &data);
void find_car(const std::vector <CAR> &data, string num);