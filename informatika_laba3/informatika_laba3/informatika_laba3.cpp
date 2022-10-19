#include<iostream>
#include<vector>
#include <iomanip>

using namespace std;

int input_lenght() {		// эта функция проверяет х на корректный ввод
	int x;
	cout << "Enter the number of dates: ";		//пока х не введен или символ
	while (!(cin >> x) || (cin.peek() != '\n') || (x <= 0)) {	//пока х не введен или символ справа не пробел или  не принадлежит -1<=x<=1
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct pozitive lenght: " << endl; // выводим ошибку
	}
	return x;		// возвращаем корректный х
}

vector<vector<int>> vector_input(int lenght){		// эта функция проверяет х на корректный ввод
	vector<vector<int>> date;
	char day[3], month[3], year[5];
	int counter = 1;
	for (int i = 0; i < lenght; i++) {
		cout << "Input the date number #" << counter << " "<< "DD.MM.YYYY" << endl;
		cin.get(day, 3,'.');
		cin.ignore(100, '.');
		cin.get(month, 3, '.');
		cin.ignore(100, '.');
		cin.get(year, 5);
		int d, m, y;
		m = atoi(month);
		y = atoi(year);
		d = atoi(day);
		counter++;
		date.push_back({ d, m, y });
	}

	return date;	// возвращаем корректный х
}


void output_table(int d, int m, int y) {		// Вывод таблицей
	cout << "day " << setw(4) << d << " | ";				// Значение итерации шириной 4 символа
	cout << "month " << setw(13) << m << " | ";	// Значение n-ого члена ряда шириной 13 
	cout << "year " << setw(10) << y << " | ";		// Значение суммы ряда шириной 10
	cout << "\n";											// Разграничение таблицы
}
int main() {
	int lenght;
	vector<vector<int>> date;
	lenght = input_lenght();
	date = vector_input(lenght);
	output_table(date[0][0], date[0][1], date[0][2]);
		


}