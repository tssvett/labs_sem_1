#include<iostream>
#include<string>		// Подключаем необходимые библиотеки
using namespace std;
int array_lenght;
string element;
string max_element;
int max_counter, counter;		// Объявляем необходимые переменные


int input_array_lenght() {		// Функция, которая вводит корректную длину массива
	cout << "Enter a massive lenght: ";
	while (!(cin >> array_lenght) || (cin.peek() != '\n') || (array_lenght <= 0)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error has been detected! Input a correct nonegaive integer number: ";
	}
	return array_lenght;
}


void input_array_elements(string array[]) {		// Функция, которая вводит корректные элементы массива поштучно
	int i = 0;
	for (i = 0; i < array_lenght; i++) {
		cout << "Enter an array element: ";
		while (!(cin >> array[i]) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error has been detected! Input one array element: ";
		}
	}
}


void find_frequent_algorithm(string array[]) {		// Алгоритм нахождения самого часто встречаемого
	element = array[0];								// символа и колличество его повторений в массиве
	max_counter = 1;		// Инициализируем переменную для максимального колличества повторений
	for (int i = 0; i < array_lenght; i++) {		// Цикл фор, который пробегает по всем элементам массива
		counter = 1;		// Инициализируем счетчик повторений
		for (int k = i + 1; k < array_lenght; k++)		// Перебор символов после символа i и сравнение с символом i
			if (array[i] == array[k])					// Если символы равны, то счетчик повторений +1
				counter += 1;
		if (counter > max_counter) {		// Если счетчик вхождений больше чем максимальный счетчик,
			max_counter = counter;		// то переприсваиваем значение максимального счетчика вхождений
			element = array[i];		// и переприсваиваем элемент в часто встречаемый элемент
		}
	}
}


void output() {		// Выводные данные программы
	if (max_counter > 1)		// если число повторений больше чем одно, то повторения есть и выводим их
		cout << "The number of repetitions is: " << max_counter << "\n" << "The most frequent element is: " << element << "\n";
	else		// если повторение одно(инициализировано в переменных) то повторений нет и выводим соответсвующее сообщение
		cout << ("All elements are unique!\n");
}


bool y_n_check() {		// Проверка на продолжение программы
	bool flag = 1;		// зацикливаем ее при случае неверного ввода y/n
	while (flag){
		char symbol;		// объявляем переменную
		cout << "Do you want to continue? --> Y/N\n";
		cin >> symbol;		// вводим ее
		if (symbol == 'N' || symbol == 'n') {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return false;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		else if (symbol == 'Y' || symbol == 'y') {		// если да, то
			flag = false;		// зацикленность проверки отключается
			return true;		// функция возвращает true и программа продолжает свое выполнение
		}
		else {		// при иных значениях ввода проверка y/n зацикливается
			flag = true;
		}
	}
}


int main() {
	bool is_processing = true;		// поднимаем флаг зацикленности программы
	while (is_processing) {		// пока флаг поднят
		int array_lenght = input_array_lenght();		// вводим корректное значение длины массива
		string *array = new string[array_lenght];		// задаем динамический массив с его длинной
		input_array_elements(array);		// поштучно вводим в массив элементы
		find_frequent_algorithm(array);		// применяем алгоритм для решения задачи
		output();		// выводим полученные значения
		is_processing = y_n_check();		// продолжаем программу или нет, если нет флаг опускаем
	}
}


