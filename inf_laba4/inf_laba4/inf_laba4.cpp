#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<sstream>
#include <utility>

using namespace std;


void in_file_output(string& words, ofstream &file) {		// функция записывает полученную строку в созданный файл
	for (int i = 0; i < words.size(); i++) {
		file << words[i];		// записываем в него строку 
	}
	file << "\n";
	file.close();		// закрываем файл
	cout << "The string written to a file: ";
	for (int i = 0; i < words.size(); i++) {		//		вывод массива записанного в файл в  консоль
		cout << words[i];
	}
	cout << "\n";
}



string get_from_file(ifstream &file) {		// функция которая берет входные данные из файла
	string words;
	char symbol;
	while ((symbol = file.get()) != EOF) {		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	return words;
}


bool y_n_check() { // видимо конечная самописная функция проверки y/n
	bool flag = true;		// зацикливаем ее при случае неверного ввода y/n
	char symbol;
	cout << endl << "Do you want to continue? --> Y/N\n";
	while (!(cin >> symbol) || flag) {
		cin.clear();
		if ((symbol == 'N' || symbol == 'n') && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return false;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		else if ((symbol == 'Y' || symbol == 'y') && (cin.peek() == '\n')) {		// если да, то
			flag = false;		// зацикленность проверки отключается
			return true;		// функция возвращает true и программа продолжает свое выполнение
		}
		else {		// при иных значениях ввода проверка y/n зацикливается
			flag = true;
		}
		while (cin.get() != '\n');
		cout << "Do you want to continue? Please, enter --> Y/N\n";	// извлекаем ошибочные символы, считывая до конца строчки
	}
}


string file_name_input() {
	bool is_open = true;
	string ifile_name;
	cout << "Enter a file name from which take input data: " << endl;
	while (is_open) {
		cin >> ifile_name;
		ifstream ifile(ifile_name);		// инициализируем файл для выходных файлов
		if (!ifile.is_open()) {
			is_open = true;
			cout << "Error #1 This file cannot be opened. Enter correct filename. " << endl;
		}
		else {
			is_open = false;
			if (ifile.peek() == EOF) {
				is_open = true;
				cout << "Error#2  This file is empty. Enter correct filename " << endl;
			}
		}
		while (cin.get() != '\n');
	}
	return ifile_name;
}


bool in_romans(char symbol) { //Входит ли число в римский набор 
	if (symbol == 'I' || symbol == 'V' || symbol == 'X' || symbol == 'L' || symbol == 'C' || symbol == 'D' || symbol == 'M') {
		return 1;
	}
	else
		return 0;
}


vector<pair<long long, long long>> get_borders(string stroka) {
	vector<pair<long long, long long>> borders;
	vector<long long> borders1;
	vector<long long> borders2;
	for (long long i = 1; i < stroka.size(); i++) {
		char symbol = stroka[i];
		char prev = stroka[i - 1];
		char peek = stroka[i + 1];
		int first_gr = -1;
		int second_gr = -1;
		if ((in_romans(symbol) && (prev == ' ' || prev == '\n' || prev == '"' || prev == '-' || prev == '\'') && (peek == ' ' || peek == '\n' || in_romans(peek) || peek == '.'))) {
			borders1.push_back(i);
		}
		if ((peek == ' ' || peek == EOF || peek == '\n' || peek == '.') && (prev == ' ' || prev == '\n' || prev == '"' || prev == '-' || in_romans(prev)) && (in_romans(symbol))) {
			borders2.push_back(i);
		}
	}
	int size;
	if (borders1.size() > borders2.size())
		size = borders2.size();
	else
		size = borders1.size();
	
	for (long long i = 0; i < size; i++) {
		if ((borders2[i] - borders1[i]) > 9) {
			if (borders1.size() > borders2.size()) {
				auto iter1 = borders1.cbegin();
				borders1.erase(iter1 + (i - 1));
			}
			else {
				auto iter2 = borders2.cbegin();
				borders2.erase(iter2 + (i - 1));
			}
		}
	}
		for (long long i = 0; i < size; i++) {
			if (abs(borders2[i] - borders1[i]) <= 9) {
				borders.push_back(make_pair(borders1[i], borders2[i]));
			}

		}
	return borders;
}

string convert_borders(vector<pair<long long, long long>> borders, string file_text, long long i) {

		string roman_number;
		long long difference = abs(borders[i].second - borders[i].first);
		for (long long j = 0; j <= difference; j++) {
			roman_number += file_text[borders[i].first + j];
		}
		//roman_number = file_text[borders1[0]] + file_text[borders1[1]] + ... + file_text[borders1[5]]
		return roman_number;
}

string roman_to_int(string number) {
	map<char, int> dict = { {'I', 1}, {'V', 5}, {'X', 10} ,{'L', 50}, 
	{'C', 100}, {'D', 500}, {'M', 1000} };
	int total = 0;
	string arabic_number;
	for (int i = 0; i < number.size(); i++) {
		if (dict[number[i + 1]] <= dict[number[i]])
			total += dict[number[i]];
		else
			total -= dict[number[i]];
	}
	arabic_number = to_string(total);
	return arabic_number;
}


string replace_romans(vector<pair<long long, long long>> borders, vector<string> arabic, string file_text) {
	string copy = file_text;
	long long deleted_sum = 0;
	for (long long i = 0; i < borders.size(); i++) {
		long long difference = abs(borders[i].second - borders[i].first) + 2;
		file_text.erase(borders[i].first, difference);
		deleted_sum += difference;
		file_text.insert(borders[i].first, arabic[i] + ' ');
		deleted_sum -= arabic[i].size() + 1;
		if ((i + 1) < borders.size()) {
			borders[i + 1].first -= deleted_sum;
			borders[i + 1].second -= deleted_sum;
		}
	}
	cout << file_text << endl;
	return file_text;
}

int main() {
	bool processing = true;
	ofstream output_file;
	string file_name;
	string words;
	vector<long long> borders1;
	vector<long long> borders2;
	vector<pair<long long, long long>> borders;
	vector<string> romans;
	while (processing) {
		file_name = file_name_input();
		ifstream ifile(file_name);
		string file_text = get_from_file(ifile);
		borders = get_borders(file_text);
		vector<string> arabic;
		for (long long i = 0; i < borders.size(); i++) {
			string number;
			number = convert_borders(borders, file_text, i);
			number = roman_to_int(number);
			arabic.push_back(number); // Вектор с арабскими числами
		}
		file_text = replace_romans(borders, arabic, file_text);
		ofstream ofile("output.txt", ios_base::out | ios_base::trunc); // тут поменяешь название на ifile
		in_file_output(file_text, ofile);	// тут тоже
		processing = y_n_check();
	}
}


