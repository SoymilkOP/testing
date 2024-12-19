//cpp
#include <regex>
#include "Header.h"

CAR::CAR(string newyear, string newmonth, string newday, string newnumber) {
	validate_date(newday, newmonth, newyear);
	validate_number(newnumber);

	year = newyear;
	month = newmonth;
	day = newday;
	number = newnumber;

}


int CAR::totalday() {
	return (stoi(day) + stoi(month) * 30 + stoi(year) * 365);
}

std::vector<CAR> load_txt(ifstream &ist, std::vector<CAR> &data) {
	string line;
	std::regex pattern1(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(\d{4})\s+([A-ZА-Я]{3}\d{3}[A-ZА-Я]\d))"); // Для формата "дд.мм.гггг номер"
	std::regex pattern2(R"((^[A-ZА-Я]{3}\d{3}[A-ZА-Я]\d$)\s+(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(\d{4}))"); // Для формата "номер дд.мм.гггг"

	while (getline(ist, line)) {
		std::smatch matches;
		if (std::regex_match(line, matches, pattern1)) {
			// Формат "дд.мм.гггг номер"
			string day = matches[1].str();
			string month = matches[2].str();
			string year = matches[3].str();
			string number = matches[4].str();
			data.push_back({ year, month, day, number });
		}
		else if (std::regex_match(line, matches, pattern2)) {
			// Формат "номер дд.мм.гггг"
			string number = matches[1].str();
			string day = matches[2].str();
			string month = matches[3].str();
			string year = matches[4].str();
			data.push_back({ year, month, day, number });
		}
	}
	return data;
}

void print_all_cars(const std::vector<CAR> &data) {
	for (int i = 0; i < data.size(); i++) {
		cout << i + 1 << " машина проехала - " << data[i].day << "." << data[i].month << "." << data[i].year << " " << data[i].number << endl;
	}
}

void validate_date(const std::string& day, const std::string& month, const std::string& year) {
	int day_num = stoi(day);
	int month_num = stoi(month);
	int year_num = stoi(year);

	if (month_num < 1 || month_num > 12) {
		throw std::invalid_argument("Ошибка: некорректный месяц: " + month);
	}
	if (day_num < 1 || day_num > 31) {
		throw std::invalid_argument("Ошибка: некорректный день: " + day);
	}
	// Дополнительные проверки для месяцев с разным количеством дней
	if ((month_num == 4 || month_num == 6 || month_num == 9 || month_num == 11) && day_num > 30) {
		throw std::invalid_argument("Ошибка: некорректный день для месяца: " + month);
	}
	if (month_num == 2) {
		bool leap_year = (year_num % 4 == 0 && year_num % 100 != 0) || (year_num % 400 == 0);
		if ((leap_year && day_num > 29) || (!leap_year && day_num > 28)) {
			throw std::invalid_argument("Ошибка: некорректный день для февраля: " + day);
		}
	}
}

void validate_number(const std::string& number) {
	std::regex number_pattern(R"(^[A-ZА-Я]{3}\d{3}[A-ZА-Я]\d$)");
	if (!std::regex_match(number, number_pattern)) {
		throw std::invalid_argument("Ошибка: некорректный номер: " + number);
	}
}


void car_sort(std::vector<CAR> &data) {
	std::regex pattern(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(\d{4}))"); // Для проверки даты
	std::regex number_pattern(R"(\w{8})"); // Для проверки номера

	for (auto &car : data) {
		// Проверка на корректность даты
		std::string date = car.day + "." + car.month + "." + car.year;
		if (!std::regex_match(date, pattern)) {
			throw std::invalid_argument("Ошибка: некорректная дата: " + date);
		}

		// Проверка на корректность номера
		if (!std::regex_match(car.number, number_pattern)) {
			throw std::invalid_argument("Ошибка: некорректный номер: " + car.number);
		}
	}

	// Сортировка
	for (int i = 1; i < data.size(); i++) {
		if (data[i].totalday() > data[i - 1].totalday()) {
			std::swap(data[i], data[i - 1]);
			i = 0; // Сброс индекса для повторной проверки
		}
	}
}

void find_car(const std::vector<CAR> &data, string num) {
	std::regex pattern(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(\d{4}))"); // Для проверки даты
	std::regex number_pattern(R"(\w{8})"); // Для проверки номера

	for (auto &car : data) {
		// Проверка на корректность даты
		std::string date = car.day + "." + car.month + "." + car.year;
		if (!std::regex_match(date, pattern)) {
			throw std::invalid_argument("Ошибка: некорректная дата: " + date);
		}

		// Проверка на корректность номера
		if (!std::regex_match(car.number, number_pattern)) {
			throw std::invalid_argument("Ошибка: некорректный номер: " + car.number);
		}
	}
	int f = 0;
	for (const auto& car : data) {
		if (num == car.number) {
			f++;
		}
	}
	if (f > 1)
		cout << "Даты проезда: " << endl;
	else if (f == 1)
		cout << "Дата проезда: " << endl;

	if (f > 0) {
		int j = 1;
		for (const auto& car : data) {
			if (num == car.number) {
				if (f == 1)
					cout << car.day << "." << car.month << "." << car.year << endl;
				else if (f > 1)
					cout << j << ". " << car.day << "." << car.month << "." << car.year << endl;
				j++;
			}
		}
	}
	else {
		cout << "Такая машина не проезжала";
	}
}

