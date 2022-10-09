#include<iostream> 
#include<vector>
#include <iomanip>
using namespace std;
int lenght;
const unsigned int critical_lenght = 23;



int correct_input_lenght() {		// эта функция проверяет х на корректный ввод
	cout << "Enter array lenght: ";		//пока х не введен или символ
	while (!(cin >> lenght) || (cin.peek() != '\n') || (lenght <= 1)) {	//пока ввод некорректен
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "An Error has been detected! Please, enter a correct lenght > 1: "; // выводим ошибку
	}
	if (lenght > critical_lenght){
		return critical_lenght;
	}
	else if (lenght <= critical_lenght) {
		return lenght;	// возвращаем длину
	}
}


vector<int> random_array_input(vector<int> array) {
	for (int i = 0; i < array.size(); i++) 
		array[i] = rand() % 1000;
	return array;
}


vector<int> bubble_sorting(vector<int> array) {  // Сортировка пузырьком
	int swap;
	for (int i = 0; i < array.size() - 1; i++) {		// Используем вложенный цикл
		for (int j = 0; j < array.size() - 1; j++) {
			if (array[j + 1] < array[j]) {		// Если второй элемент меньше чем первый элемент
				swap = array[j + 1];		// Переменная принимает значение второго элемента
				array[j + 1] = array[j];		// Меняем их местами
				array[j] = swap;		// Переменная принимает значение первого элемента
			}
		}
	}
	return array;
}


void bubble_array_output(vector<int> array) {
	cout << "The array sorted by buble: ";
	for (int i = 0; i < array.size(); i++) {
		cout << setw(3) << array[i] << " ";
	}
	cout << "\n";
}


void generated_array_output(vector<int> array) {
	cout << "The random gerenated array: ";
	for (int i = 0; i < array.size(); i++) 
		cout << setw(3) << array[i] << " ";
	cout << "\n";
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
	bool is_processing = true;		// поднимаем флаг зацикленности программы
	while (is_processing) {
		lenght = correct_input_lenght();		//Ввод длины массива
		vector<int> void_array(lenght);		// Объявляем вектор
		vector<int> filled_vector = random_array_input(void_array);		// Заполняем вектор значениями введенными руками
		vector<int> bubble_array = bubble_sorting(filled_vector);
		generated_array_output(filled_vector);
		bubble_array_output(bubble_array);		// Выводим отсортированный вектор
		is_processing = y_n_check();
	}
}