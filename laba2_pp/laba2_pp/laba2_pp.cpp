#include<iostream>	// для ввода вывода cin cout
#include<iomanip>	// для красивого вывода	
#include<string>	// для типа string
using namespace std;


double numerical_series(int n, double x) {		// эта функция считает n-ый член ряда
	double current_member;		//задаем переменную
	current_member = pow(-1, n) * (pow(x, (2 * n) + 1) * (1 + (pow(x, 2))) / ((2 * n) + 1));		// находим значение по формуле	
	return current_member;		// возвращаем найденный n-ый член ряда
}


double alpha_is(int n,double x,double previous_member,double current_member, double series_sum) { // эта функция подсчитывает значение погрешности alpha и возвращает его
	double alpha;
	n++; // так же именно здесь происходит сама итерация
	previous_member = current_member;		// запоминание предыдущего элемента ряда
	current_member = numerical_series(n, x);		// подсчет нового значения ряда
	alpha = abs(current_member / series_sum);		// нахождение погрешности R по формуле
	return alpha;		// возвращаем значение alpha
}


void output_table(int n, double x,double previous_member, double current_member,double series_sum,double alpha) {		// Вывод таблицей
	cout << "n = " << setw(4) << n << " | ";				// Значение итерации шириной 4 символа
	cout << "An = " << setw(13) << current_member << " | ";	// Значение n-ого члена ряда шириной 13 
	cout << "S = " << setw(10) << series_sum << " | ";		// Значение суммы ряда шириной 10
	cout << "Alpha = " << setw(15) << alpha << " | ";		// Значение константы 
	cout << "\n";											// Разграничение таблицы
}


double correct_input_x(int n) {		// эта функция проверяет х на корректный ввод
	cout << "Enter parameter x: ";		//пока х не введен или символ
	double x;
	while (!(cin >> x) || (cin.peek() != '\n') || (x > 1) || (x < -1) || (x ==0)) {	//пока х не введен или символ справа не пробел или  не принадлежит -1<=x<=1
		if (x == 0) {
			cout << "In any cases table output zeros and alpha is nan\n";
		}
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct -1 <= x <= 1, x != 0: " << endl; // выводим ошибку
	}
	return x;		// возвращаем корректный х
}


double correct_input_a() {		// эта функция проверяет а на корректный ввод
	cout << "Enter parameter a: ";
	double a;
	while (!(cin >> a) || (cin.peek() != '\n') || (a <= 0)) { // пока а не введен или символ справа не пробел или а меньше нуля
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct  accuraccity: " << endl;
	}
	return a;		//возвращаем корректное значение а
}


void series_algorithm(int n, double x,double previous_member, double current_member,double series_sum,double alpha) {
	current_member = numerical_series(n, x);				// вычисление n-ого члена данного ряда
	series_sum += current_member;							// сумма ряда складывается из всех его членов
	output_table(n, x, previous_member, current_member, series_sum,alpha);											// красивый вывод в таблицу
}


bool y_n_check() { // видимо конечная самописная функция проверки y/n
	bool flag = 1;		// зацикливаем ее при случае неверного ввода y/n
	char symbol;
	cout << "Do you want to continue? --> Y/N\n";
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
	bool is_processing = true;		// ставим флаг true
	while (is_processing) {		// пока true
		int n = 0;
		double a;		// задаем все необходимые переменные для решения данной задачи
		double x;
		double current_member;
		double previous_member = 0;
		double series_sum = 0;
		double alpha;


		x = correct_input_x(n); // проверка и корректный ввод x
		a = correct_input_a(); // проверка и корректный ввод а
		current_member = numerical_series(n, x); // Нахождение An члена ряда
		series_sum += current_member;	// Добавляем данный член в сумму ряда
		alpha = alpha_is(n, x, previous_member, current_member, series_sum);
		output_table(n, x, previous_member, current_member, series_sum, alpha); // Выводим все таблицей		// Выполняем подсчет первой итерации отдельно, чтобы потом
		n++;

		if (a != int(a)) {		// 
			while (alpha > a) {		// пока вычисленная точность больше данной точности
				current_member = numerical_series(n, x);				// вычисление n-ого члена данного ряда
				series_sum += current_member;							// сумма ряда складывается из всех его членов
				alpha = alpha_is(n, x, previous_member, current_member, series_sum);
				output_table(n, x, previous_member, current_member, series_sum, alpha);											// красивый вывод в таблицу 
				n++;
			}
		}
		else {
			while (n < a) {			// пока число итераций меньше введенного целого а
				current_member = numerical_series(n, x);				// вычисление n-ого члена данного ряда
				series_sum += current_member;							// сумма ряда складывается из всех его членов
				alpha = alpha_is(n, x, previous_member, current_member, series_sum);
				output_table(n, x, previous_member, current_member, series_sum, alpha);											// красивый вывод в таблицу 
				n++;
			}
		}
		is_processing = y_n_check();
	}
}