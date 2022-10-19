#include<iostream>	// для ввода вывода cin cout
#include<iomanip>	// для красивого вывода	
#include<string>	// для типа string
#include<vector>	// для векторов
using namespace std;


double correct_input_x() {		// эта функция проверяет х на корректный ввод
	double x;
	cout << "Enter parameter x: ";		//пока х не введен или символ
	while (!(cin >> x) || (cin.peek() != '\n') || (x > 1) || (x < -1) || (x == 0)) {	//пока х не введен или символ справа не пробел или  не принадлежит -1<=x<=1
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
	double a;
	cout << "Enter parameter a: ";
	while (!(cin >> a) || (cin.peek() != '\n') || (a <= 0)) { // пока а не введен или символ справа не пробел или а меньше нуля
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct  accuraccity: " << endl;
	}
	return a;		//возвращаем корректное значение а
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


double numerical_series(int n, double x) {		// эта функция считает n-ый член ряда
	double an;		//задаем переменную
	an = pow(-1, n) * (pow(x, (2 * n) + 1) * (1 + (pow(x, 2))) / ((2 * n) + 1));		// находим значение по формуле	
	return an;		// возвращаем найденный n-ый член ряда
}


double alpha_is(double an1, double series_sum) { // эта функция подсчитывает значение погрешности alpha и возвращает его
	double alpha;
	alpha = abs(an1 / series_sum);		// нахождение погрешности R по формуле
	return alpha;		// возвращаем значение alpha
}


void output_table(int n, double an, double series_sum, double alpha) {		// Вывод таблицей
	cout << "n = " << setw(4) << n << " | ";				// Значение итерации шириной 4 символа
	cout << "An = " << setw(13) << an << " | ";	// Значение n-ого члена ряда шириной 13 
	cout << "S = " << setw(10) << series_sum << " | ";		// Значение суммы ряда шириной 10
	cout << "Alpha = " << setw(15) << alpha << " | ";		// Значение константы 
	cout << "\n";											// Разграничение таблицы
}


vector<vector<double>> algorithm(double x, double a) { // Функция для вычислений, возвращает результаты вычислений в виде двумерного вектора
	vector<vector<double>> storage;
	double an;
	double an1;
	double series_sum = 0;
	double alpha = 1; //любое значение для запуска цикла. Далее она примет адекватное значение
	if (a != int(a)) {		// если а с плавающей точкой
		int n = 0;
		while (alpha > a) {		// пока вычисленная точность больше данной точности
			an = numerical_series(n, x);		//вычисление первого члена ряда
			series_sum += an;		//прибавляем член к сумме ряда
			an1 = numerical_series(n + 1, x);		//вычисление второго члена рядо
			alpha = alpha_is(an1, series_sum);		//находим погрешность
			output_table(n, an, series_sum, alpha);		// выводим все табличкой
			storage.push_back({ an,series_sum,alpha });			//сохраняем найденные значения в двумерный вектор
			n++;
		}
	}


	else {		//если число а целое
		int n = 0;
		while (n < a) {			// пока число итераций меньше введенного целого а
			an = numerical_series(n, x);		//вычисление первого члена ряда
			series_sum += an;		// вычисдение первого члена ряда
			an1 = numerical_series(n + 1, x);		//вычисление второго члена рядо
			alpha = alpha_is(an1, series_sum);		//находим погрешность
			output_table(n, an, series_sum, alpha);			// красивый вывод в таблицу 
			storage.push_back({ an,series_sum,alpha });				//сохраняем все в вектор
			n++;
		}

	}
	return storage;
}


void post_algorithm(double x, double a, vector<vector<double>> &storage) {
	double an;
	double an1;
	double alpha = 1;
	int n = 1; // Счетчик выведенных элементов из вектора если он ноль и остальное без вычета единицы ничего не работает
	if (a != int(a)) {		// если а с плавающей точкой
		cout << "Output already calculated values: " << endl;
		while ((alpha > a)&&(n <= storage.size())) {
			output_table(n - 1, storage[n - 1][0], storage[n - 1][1], storage[n - 1][2]);
			n++;
		}
		alpha = storage[n - 2][2];
		n = n - 1;		//почему то съезжает на единичку без этого не работает
		if (alpha > a)
			cout << "New calculated: " << endl;
		double series_sum = storage[n - 1][1];
		while (alpha > a) {		// пока вычисленная точность больше данной точности
			an = numerical_series(n, x);		//вычисление первого члена ряда
			series_sum += an;		//складываем
			an1 = numerical_series(n + 1, x);		//вычисление второго члена рядо
			alpha = alpha_is(an1, series_sum);		//нахожим погрешность
			output_table(n, an, series_sum, alpha);
			storage.push_back({ an,series_sum,alpha });
			n++;
		}
	}

	else {		//целое число а
		cout << "Output already calculated values: " << endl;
		while ((n <= a) && (n <= storage.size())) {
			output_table(n - 1, storage[n - 1][0], storage[n - 1][1], storage[n - 1][2]);
			n++;
		}
		n = n - 1;		
		if (n < a)
			cout << "New calculated: " << endl;
		double series_sum = storage[n - 1][1];
		while (n < a) {		// пока вычисленная точность больше данной точности
			an = numerical_series(n, x);		//вычисление первого члена ряда
			series_sum += an;		//складываем
			an1 = numerical_series(n + 1, x);		//вычисление второго члена рядо
			alpha = alpha_is(an1, series_sum);		//нахожим погрешность
			output_table(n, an, series_sum, alpha);
			storage.push_back({ an,series_sum,alpha });
			n++;
		}
	}

}


int main() {
	double x;
	double a;
	double new_x = 5;		//любое значение для инициализации потом исчезнет без влияния
	vector<vector<double>> storage;
	bool is_processing = true;		// ставим флаг true
	while (is_processing) {		// пока true
		x = correct_input_x(); // проверка и корректный ввод x
		a = correct_input_a(); // проверка и корректный ввод а
		if (x != new_x) {		//для первой итерации всегда далее если старый икс не равен новому
			cout << "Problem solution is: " << endl;
			storage = algorithm(x, a);	//обычный расчет ряда
		}
		else {		// если же иксы одинаковые
			post_algorithm(x, a, storage);		//выводим уже посчитанное и считаем еще не посчитанное
		}
		new_x = x;		//запоминаем новый икс как старый
		is_processing = y_n_check();
	}
}