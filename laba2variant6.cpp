﻿#include<iostream>	// для ввода вывода cin cout
#include<iomanip>	// для красивого вывода	
#include<string>	// для типа string
#include<conio.h>	// для _getch()
using namespace std;
double x;
double a;		// задаем все необходимые переменные для решения данной задачи
int n = 0;
double current_member;
double previous_member;
double series_sum = 0;
double R;

double numerical_series(int n, double x) {		// эта функция считает n-ый член ряда
	double current_member;		//задаем переменную
	current_member = pow(-1, n) * (pow(x, (2 * n) + 1) * (1 + (pow(x, 2))) / ((2 * n) + 1));		// находим значение по формуле	
	return current_member;		// возвращаем найденный n-ый член ряда
}

double R_is() { // эта функция подсчитывает значение погрешности R и возвращает его
	n++; // так же именно здесь происходит сама итерация
	previous_member = current_member;		// запоминание предыдущего элемента ряда
	current_member = numerical_series(n, x);		// подсчет нового значения ряда
	R = abs(current_member / series_sum);		// нахождение погрешности R по формуле
	return R;		// возвращаем значение R
}

void output_table() {										// Вывод таблицей
	cout << "n = " << setw(4) << n << " | ";				// Значение итерации шириной 4 символа
	cout << "An = " << setw(13) << current_member << " | ";	// Значение n-ого члена ряда шириной 13 
	cout << "S = " << setw(10) << series_sum << " | ";		// Значение суммы ряда шириной 10
	cout << "Alpha = " << setw(15) << R_is() << " | ";		// Значение константы 
	cout << "\n";											// Разграничение таблицы
}

double correct_input_x() {		// эта функция проверяет х на корректный ввод
	cout << "Enter parameter x: ";		//пока х не введен или символ
	while (!(cin >> x) || (cin.peek() != '\n') || (x > 1) || (x < -1) || x == 0) {	//пока х не введен или символ справа не пробел или  не принадлежит -1<=x<=1
		if (x == 0) {
			output_table();		// если x = 0 то выводим строку из таблицы и просим ввод снова
		}
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct -1 <= x <= 1 : " << endl; // выводим ошибку
	}
	return x;		// возвращаем корректный х
}


double correct_input_a() {		// эта функция проверяет а на корректный ввод
	cout << "Enter parameter a: ";
	while (!(cin >> a) || (cin.peek() != '\n') || (a < 0)) { // пока а не введен или символ справа не пробел или а меньше нуля
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct  accuraccity: " << endl;
	}
	return a;		//возвращаем корректное значение а
}


void first_iteration() {	// эта функция делает расчет первой итерации для дальнейшего просчета R
	current_member = numerical_series(n, x); // Нахождение An члена ряда
	series_sum += current_member;	// Добавляем данный член в сумму ряда
	output_table(); // Выводим все таблицей

}


void series_algorithm() {
	previous_member = current_member;						// после выполнения первой итерации запоминаем предыдущий член
	current_member = numerical_series(n, x);				// вычисление n-ого члена данного ряда
	series_sum += current_member;							// сумма ряда складывается из всех его членов
	output_table();											// красивый вывод в таблицу
}
				 

int main() {
	bool is_processing = true;		// ставим флаг true
	string symbol;		// задаем переменную типа стринг
	while (is_processing) {		// пока true
		correct_input_x(); // проверка и корректный ввод x
		correct_input_a(); // проверка и корректный ввод а
		first_iteration();		// Выполняем подсчет первой итерации отдельно, чтобы потом
		if (a != int(a)) {		// просчитать значение R
			while (R > a) {		// пока вычесленная точность больше данной точности
				series_algorithm();			// выполняем алгоритм 
			}
		}
		else {
			while (n < a) {			// пока число итераций меньше введенного целого а
				series_algorithm();		// Выполнение алгоритма 
			}
		}
		cout << "Do you want to continue? --> any symbol/N \n"; 
		cin >> symbol;		//чтение написанного символа
		x = a = n = current_member = previous_member = series_sum = R = 0;		//обнуление всех переменных
	if (symbol == "N" || symbol == "n") {	//если пишем N или n то программа отключается
		return 0;
		}
	}
}

