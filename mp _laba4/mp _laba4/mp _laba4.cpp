#include<iostream>
#include<fstream>		// для работы с файлами
#include<vector>
#include<Windows.h>
using namespace std;


void string_output(vector<char>& words, ofstream &file) {		// функция записывает полученную строку в созданный файл
	file << "\n";
	for (int i = 0; i < words.size(); i++) {
		file << words[i];		// записываем в него строку 
	}
	file << "\n";
	file.close();		// закрываем файл
	cout << "\n";
	cout << "The string written to a file:" << endl;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива записанного в файл в  консоль
		cout << words[i];
	}
	cout << "\n";
}


vector<char> string_input(ifstream &file) {		// функция которая берет входные данные из файла
	vector<char> words;
	char symbol;
	while ((symbol = file.get()) != EOF) {		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	cout << "The string taken from a file is:" << endl;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива извлеченного из файл в конлось
		cout << words[i];
	}
	cout << endl;
	return words;
}

 //  В  отчете чтобы так было ЛР4

int spaces_to_star(vector<char>& words) {		// Функция которая заменяет все пробелы на звезды
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


void group_to_one_star(vector<char>& words, int counter_before) {		//функция которая заменяет группу звезд(пробелов) одной звездой(пробелом)
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
		return group_to_one_star(words, counter_after);
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


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool is_processing = true;
	char ofile_name[40] = "string_output.txt";		// создаем файл с заданным названием и выгружаем туда полученные строки
	char ifile_name[100];
	vector<char> words;
	int counter;
	while (is_processing) {
		bool is_open = true;	// без типа стринг очень тяжко в отдельную фунцию это завернуть
		// проблема в том что ??нельзя?? передать в функцию char переменная[100] так чтобы было как строка
		cout << "Enter a file name from which take input data: " << endl;
		while (is_open) {
			cin.clear();
			cin >> ifile_name;
			ifstream ifile(ifile_name);		// инициализируем файл для выходных файлов
			if (!ifile.is_open()) {
				is_open = true;
				cout << "Error #1 This file cannot be opened. " << endl;
			}
			else {
				is_open = false;
				if (ifile.peek() == EOF) {
					is_open = true;
					cout << "Error#2  This file is empty. " << endl;
				}
			}
			while (cin.get() != '\n');
			cout << "Enter correct file name! --> ";
		}
		ifstream ifile(ifile_name);
		ofstream ofile(ofile_name, ios_base::app);	// инициализируем файл для выходных данных
		words = string_input(ifile);
		counter = spaces_to_star(words);		// замена всех пробелов на звезды
		group_to_one_star(words, counter);
		string_output(words, ofile);
		is_processing = y_n_check();
	}
