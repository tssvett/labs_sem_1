#include<iostream>
#include<fstream>		// для работы с файлами
#include<vector>
#include<Windows.h>
#include<string>
#include<chrono>
using namespace std;
using namespace chrono;


void introduce(ifstream &file) {
	string words;
	char symbol;
	while ((symbol = file.get()) != EOF) {		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	cout << "Calculating average algorithmical time by running programm 10 times...." << endl;
	cout << "The string taken from a file by pp and mp algorithm is:" << endl;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива извлеченного из файл в конлось
		cout << words[i];
	}
	cout << endl;
}


void string_output_pp(string& words, ofstream &file) {		// функция записывает полученную строку в созданный файл
	for (int i = 0; i < words.size(); i++) {
		file << words[i];		// записываем в него строку 
	}
	file << "\n";
	file.close();		// закрываем файл
	cout << "The string written to a file by pp algorithm:";
	for (int i = 0; i < words.size(); i++) {		//		вывод массива записанного в файл в  консоль
		cout << words[i];
	}
	cout << "\n";
}


void string_output_mp(vector<char>& words, ofstream &file) {		// функция записывает полученную строку в созданный файл
	for (int i = 0; i < words.size(); i++) {
		file << words[i];		// записываем в него строку 
	}
	file << "\n";
	file.close();		// закрываем файл
	cout << "The string written to a file by mp algorithm:" ;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива записанного в файл в  консоль
		cout << words[i];
	}
	cout << "\n";
}


string string_input_pp(ifstream &file) {		// функция которая берет входные данные из файла
	string words;
	char symbol;
	while ((symbol = file.get()) != EOF) {		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	return words;
}


vector<char> string_input_mp(ifstream &file) {		// функция которая берет входные данные из файла
	vector<char> words;
	char symbol;
	while ((symbol = file.get()) != EOF) {		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	return words;
}



int spaces_to_star_pp(string& words) {		// Функция которая заменяет все пробелы на звезды
	char symbol;
	int counter = 0;		//счетчик который понадобится для создания рекурсии в другой функции
	for (int i = 0; i < words.size(); i++) {
		symbol = words[i];
		if (symbol == ' ') {		// Если символ пробел заменяем его звездой
			symbol = '*';
			words.erase(words.begin() + i);
			words.insert(words.begin() + i, symbol);
			counter++;
		}
	}
	return counter;
}


void group_to_one_star_pp(string& words, int counter_before) {		//функция которая заменяет группу звезд(пробелов) одной звездой(пробелом)
	char symbol;
	char second_symbol;
	int counter_after = 0;		//задаем второй счетчик для создания рекурсии
	for (int i = 0; i < words.size() - 1; i++) {
		symbol = words[i];
		second_symbol = words[i + 1];
		if ((symbol == '*') && (second_symbol == '*')) {		//если символ звезда и след за ним звезда, то убираем одну звезду
			words.erase(words.begin() + i);
			counter_after++;
		}
	}
	if (counter_before > counter_after) {		//Если число звезд больше чем число убранных звезд в группах (нам нужно уровнять ч)
		return group_to_one_star_pp(words, counter_after);
	}
}


int spaces_to_star_mp(vector<char>& words) {		// Функция которая заменяет все пробелы на звезды
	char symbol;
	int counter = 0;		//счетчик который понадобится для создания рекурсии в другой функции
	for (int i = 0; i < words.size(); i++) {
		symbol = words[i];
		if (symbol == ' ') {		// Если символ пробел заменяем его звездой
			symbol = '*';
			words.erase(words.begin() + i);
			words.insert(words.begin() + i, symbol);
			counter++;
		}
	}
	return counter;
}


void group_to_one_star_mp(vector<char>& words, int counter_before) {		//функция которая заменяет группу звезд(пробелов) одной звездой(пробелом)
	char symbol;
	char second_symbol;
	int counter_after = 0;		//задаем второй счетчик для создания рекурсии
	for (int i = 0; i < words.size() - 1; i++) {
		symbol = words[i];
		second_symbol = words[i + 1];
		if ((symbol == '*') && (second_symbol == '*')) {		//если символ звезда и след за ним звезда, то убираем одну звезду
			words.erase(words.begin() + i);
			counter_after++;
		}
	}
	if (counter_before > counter_after) {		//Если число звезд больше чем число убранных звезд в группах (нам нужно уровнять ч)
		return group_to_one_star_mp(words, counter_after);
	}
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
		cin.clear();
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

void get_all_times(vector<double> times1, vector<double> times2) {
	double sum1 = 0;
	double sum2 = 0;
	for (int i = 0; i < times1.size(); i++) { //ТУТ ХРАНИМ ВРЕМЕНА ДЛЯ ПП
		sum1 += times1[i];
	}
	for (int i = 0; i < times2.size(); i++) { //ТУТ ХРАНИМ ВРЕМЕНА ДЛЯ ПП
		sum2 += times2[i];
	}
	double average_time1 = sum1 / 10;
	double average_time2 = sum2 / 10;
	cout << "Average time in pp is: " << average_time1 << endl;
	cout << "Average time in mp is: " << average_time2 << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool is_processing = true;
	string ofile_name_pp = "string_output_pp.txt";		// создаем файл для алгоритма пп
	string ofile_name_mp = "string_output_mp.txt";		// создаем файл для алгоритма мп
	ofstream ofile_pp(ofile_name_pp, ios_base::app);	// инициализируем файл для выходных данных
	ofstream ofile_mp(ofile_name_mp, ios_base::app);	// инициализируем файл для выходных данных
	string ifile_name;
	string words_pp;
	vector<char> words_mp;
	int counter_pp;
	int counter_mp;
	vector<double> times1;
	vector<double> times2;
	while (is_processing) {
		ifile_name = file_name_input();
		ifstream introduced(ifile_name);
		introduce(introduced);
		for (int i = 0; i < 10; i++) {
			ifstream ifile_pp(ifile_name);
			ifstream ifile_mp(ifile_name);
			
			words_pp = string_input_pp(ifile_pp);
			auto begin1 = steady_clock::now();
			counter_pp = spaces_to_star_pp(words_pp);		// АЛГОРИТМ ДЛЯ ПП4
			group_to_one_star_pp(words_pp, counter_pp);
			auto end1 = steady_clock::now();
			auto time1 = duration_cast<nanoseconds>(end1 - begin1).count();
			double ms_time1 = time1 / pow(10, 6);
			times1.push_back(ms_time1);

			words_mp = string_input_mp(ifile_mp);
			auto begin2 = steady_clock::now();
			counter_mp = spaces_to_star_mp(words_mp);		// АЛГОРИТМ ДЛЯ МП4
			group_to_one_star_mp(words_mp, counter_mp);
			auto end2 = steady_clock::now();
			auto time2 = duration_cast<nanoseconds>(end2 - begin2).count();
			double ms_time2 = time2 / pow(10, 6);
			times2.push_back(ms_time2);
		}
		string_output_pp(words_pp, ofile_pp);		//Вывод информации вне цикла
		string_output_mp(words_mp, ofile_pp);
		get_all_times(times1, times2);
		is_processing = y_n_check();
	}
}
