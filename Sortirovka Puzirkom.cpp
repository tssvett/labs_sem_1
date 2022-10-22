#include<iostream> // библиотека для потока ввода вывода
#include<vector>		//библиотека для использования векторов
#include <iomanip>		//библиотека для setw()
// вариант 11 
using namespace std;
int lenght;
const int critical_lenght = 23;		// 'некоторое разумное значение'


int correct_input_lenght() {		// эта функция проверяет длину на корректный ввод
	cout << "Enter array lenght: ";
	while (!(cin >> lenght) || (cin.peek() != '\n') || (lenght <= 1)) {	//пока ввод длина не введена или символ справа не конец строки или длина отрицательна
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct lenght > 1: "; // выводим ошибку
	}
	return lenght;	// возвращаем длину
}


void random_array_input(vector<int> &array) {		//функция для заполнения вектора случайными числами
	for (int i = 0; i < array.size(); i++)
		array[i] = (rand() % 1000) - 300;
}


void bubble_sorting(vector<int> &array) {  // Сортировка пузырьком		
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
}


void bubble_array_output(vector<int> &array, int x_input) {		// вывод отсортированного массива по некоторому разумному значению
	cout << "The array sorted by buble:  ";
	for (int i = 0; i < x_input; i++) {
		cout << setw(3) << array[i] << " ";
	}
	cout << "\n";
}


void generated_array_output(vector<int> &array, int x_lenght) {		// вывод заполненного массива по некоторому разумному значению
	cout << "The random gerenated array: ";
	for (int i = 0; i < x_lenght; i++)
		cout << setw(3) << array[i] << " ";
	cout << "\n";
}


bool y_n_check() { // видимо конечная самописная функция проверки y/n
	bool flag = true;		// зацикливаем ее при случае неверного ввода y/n
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
	bool is_processing = true;		// поднимаем флаг зацикленности программы
	while (is_processing) {
		lenght = correct_input_lenght();		//Ввод длины массива
		vector<int> empty_array(lenght);		// Объявляем вектор
		random_array_input(empty_array);		// Заполняем вектор значениями введенными руками
		if (lenght < critical_lenght) {
			generated_array_output(empty_array, lenght);		// Выводим отсортированный вектор
		}
		else {
			generated_array_output(empty_array, critical_lenght);
		}
		bubble_sorting(empty_array);
		if (lenght < critical_lenght) {
			bubble_array_output(empty_array, lenght);		// Выводим отсортированный вектор
		}
		else {
			bubble_array_output(empty_array, critical_lenght);
		}

		is_processing = y_n_check();
	}
}