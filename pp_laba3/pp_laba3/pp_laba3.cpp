#include<iostream> // библиотека для потока ввода вывода
#include<vector>		//библиотека для использования векторов
#include <iomanip>		//библиотека для setw()
#include<chrono>
#include<algorithm>
// вариант 11 
using namespace std;
using namespace chrono;

int lenght;
const int critical_lenght = 23;		// 'некоторое разумное значение'


int correct_input_lenght() {		// эта функция проверяет длину на корректный ввод
	cout << "Enter array lenght: ";
	while (!(cin >> lenght) || (cin.peek() != '\n') || (lenght <= 1)) {	//пока ввод длина не введена или символ справа не конец строки или длина отрицательна
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a correct lenght > 1" << endl; // выводим ошибку
		cout << "--> ";
	}
	return lenght;	// возвращаем длину
}


int correct_input_element() {		// эта функция проверяет длину на корректный ввод
	int element;
	cout << "Enter array element: ";
	while (!(cin >> element) || (cin.peek() != '\n')) {	//пока ввод длина не введена или символ справа не конец строки или длина отрицательна
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a correct integer element" << endl; // выводим ошибку
		cout << "--> ";
	}
	return element;	// возвращаем длину
}


void array_output(vector<int> &array, int x_input) {		// вывод отсортированного массива по некоторому разумному значению
	for (int i = 0; i < x_input; i++) {
		cout << setw(3) << array[i] << " ";
	}
	cout << "\n";
}


void keyboard_array_input(vector<int> &array) {		//функция для заполнения вектора случайными числами
	for (int i = 0; i < array.size(); i++)
		array[i] = correct_input_element();
}


void random_array_input(vector<int> &array) {		//функция для заполнения вектора случайными числами
	for (int i = 0; i < array.size(); i++)
		array[i] = (rand() % 1000) - 300;
}

void reversed_array_input(vector<int> &array) {		//функция для заполнения вектора случайными числами
	for (int i = 0; i < array.size(); i++)
		array[i] = (rand() % 1000) - 300;

}


vector<int> bubble_sorting(vector<int> &array) {  // Сортировка пузырьком		
	int swap;
	for (int i = 0; i < array.size() - 1; i++) {		// Используем вложенный цикл
		for (int j = 0; j < array.size() - i - 1; j++) {		// array.size() - i тк последний член уже самый большой и отсортирован
			if (array[j + 1] < array[j]) {		// Если второй элемент меньше чем первый элемент
				swap = array[j + 1];		// Переменная принимает значение второго элемента
				array[j + 1] = array[j];		// переприсваивание
				array[j] = swap;		// Переменная принимает значение первого элемента
			}
		}
	}
	return array;
}


bool y_n_check() { // видимо конечная самописная функция проверки y/n
	bool flag = true;		// зацикливаем ее при случае неверного ввода y/n
	char symbol;
	cout << "\n" << "Do you want to continue? --> Y/N\n";
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
		cout <<"Error! Input Y or N" << endl;	// извлекаем ошибочные символы, считывая до конца строчки
		cout << "--> ";
	}
}


void switch_menu_output() {
	cout << "Choose the array input method:" << endl;
	cout << "1 -- input array by keyboard" << endl;
	cout << "2 -- input strict random data" << endl;
	cout << "3 -- input sorted on the contrary random data" << endl;
	cout << "Your choise ----> ";
}


int switch_symbol_input() {
	int symbol;
	bool flag = true;
	while (flag) {
		cin >> symbol;
		if ((symbol == 1) && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return 1;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		if ((symbol == 2) && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return 2;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		if ((symbol == 3) && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return 3;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		while (cin.get() != '\n');
		cout << "Error! Input  1 or 2 or 3" << endl;	// извлекаем ошибочные символы, считывая до конца строчки
		cout << "--> ";
	}
}


void algorithm(vector<int> &empty_array) {
	if (lenght < critical_lenght) {
		cout << "The random gerenated array: ";
		array_output(empty_array, lenght);		// Выводим отсортированный вектор
	}
	else {
		cout << "The random gerenated array: ";
		array_output(empty_array, critical_lenght);
	}
	steady_clock::time_point begin1 = steady_clock::now();
	vector<int>bubble = bubble_sorting(empty_array);
	steady_clock::time_point end1 = steady_clock::now();
	double time1 = duration_cast<microseconds>(end1 - begin1).count();
	if (lenght < critical_lenght) {
		cout << "The array sorted by buble:  ";
		array_output(bubble, lenght);		// Выводим отсортированный вектор
	}
	else {
		cout << "The array sorted by buble:  ";
		array_output(bubble, critical_lenght);
	}
	steady_clock::time_point begin2 = steady_clock::now();
	sort(empty_array.begin(), empty_array.end());
	steady_clock::time_point end2 = steady_clock::now();
	double time2 = duration_cast<microseconds>(end2 - begin2).count();
	if (lenght < critical_lenght) {
		cout << "The array sorted by sort:  ";
		array_output(empty_array, lenght);		// Выводим отсортированный вектор
		cout << "Time for bubble sort is: " << time1 << "ms" << endl;
		cout << "Time for sort() is: " << time2 << "ms" << endl;
		cout << "The acceleration is: " << time1 / time2 << endl;
	}
	else {
		cout << "The array sorted by sort:  ";
		array_output(empty_array, critical_lenght);
		cout << "Time for bubble sort is: " << time1 << "ms" << endl;
		cout << "Time for sort() is: " << time2 << "ms" << endl;
		cout << "The acceleration is: " << time1 / time2 << endl;
	}

}


int main() {
	int symbol;
	bool is_processing = true;		// поднимаем флаг зацикленности программы
	while (is_processing) {
		switch_menu_output();
		symbol = switch_symbol_input();
		lenght = correct_input_lenght();		//Ввод длины массива
		vector<int> empty_array(lenght);		// Объявляем вектор
		switch (symbol) {
		case 1:
			keyboard_array_input(empty_array);
			algorithm(empty_array);
			break;
		case 2:
			random_array_input(empty_array);		// Заполняем вектор значениями введенный случайными значениями
			algorithm(empty_array);
			break;
		case 3:
			random_array_input(empty_array);		// Заполняем вектор значениями введенный случайными значениями
			algorithm(empty_array);
			break;
		}
		is_processing = y_n_check();
	}
}