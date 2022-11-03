#include<iostream>
#include<string>
#include <vector>
using namespace std;

class Elevator {
private:
	string time;
	int starting_floor;
	int ending_floor;
public:
	void setInformation(string inf_time, int inf_starting_floor, int inf_ending_floor) {
		time = inf_time;
		starting_floor = inf_starting_floor;
		ending_floor = inf_ending_floor;
	}
	void getInformation() {
		cout << "Time: " << time << " Starting floor: " << starting_floor << " Ending floor: " << ending_floor << endl;
	}
	void floors_passed(int starting_floor, int ending_floor) {
		int passed;
		passed = abs(starting_floor - ending_floor);
		cout << "Passed floors: " << passed << endl;
		cout << "\n";

	}
};


string time_check() {
	bool flag = true;		// зацикливаем ее при случае неверного ввода y/n
	string time;
	string string_hour;
	string string_minute;
	int hour;
	int minute;
	vector<char> arr_time;
	cout << "Input correct time in format (hh:mm): ";
	while (!(cin >> time) || flag) {
		if (time.size() == 5) {
			if (isdigit(time[0]) && isdigit(time[1]) && time[2] == ':' && isdigit(time[3]) && isdigit(time[4])) {
				string_hour.push_back(time[0]);
				string_hour.push_back(time[1]);
				string_minute.push_back(time[3]);
				string_minute.push_back(time[4]);
				hour = stoi(string_hour);
				minute = stoi(string_minute);
				if ((hour >= 0 && hour < 24) && (minute >= 0 && minute < 60)) {
					flag = false;
					return time;
				}
				else {
					string_hour.pop_back();
					string_hour.pop_back();
					string_minute.pop_back();
					string_minute.pop_back();
					flag = true;
				}
			}
		}
		else 
			flag = true;
		while (cin.get() != '\n');
		cin.clear();
		cout << "Error! Input CORRECT date (hh:mm): ";	// извлекаем ошибочные символы, считывая до конца строчки
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


int correct_input_int() {		// эта функция проверяет длину на корректный ввод
	int floor;
	while (!(cin >> floor) || (cin.peek() != '\n') || (floor <= 0)) {	//пока ввод длина не введена или символ справа не конец строки или длина отрицательна
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a CORRECT number: "; // выводим ошибку
	}
	return floor;	// возвращаем длину
}



int main() {
	bool is_processing = true;
	string time;
	int starting_floor;
	int ending_floor;
	int lenght;
	vector<Elevator> array;
	Elevator lift;
	while (is_processing) {
		cout << "Input array lenght: ";
		lenght = correct_input_int();
		for (int i = 0; i < lenght; i++) {
			cout << "Initialization the " << i+1 << " class object" << endl;
			time = time_check();
			cout << "Input first floor: " ;
			starting_floor = correct_input_int();
			cout << "Input ending floor: ";
			ending_floor = correct_input_int();
			lift.setInformation(time, starting_floor, ending_floor);
			array.push_back(lift);
			for (int i = 0; i < array.size(); i++) {
				cout << array[i]; // ТУТ НУЖНО ПЕРЕГРУЗИТЬ ОПЕРАТОР ВЫВОДА В КЛАССЕ
			}
			//lift.getInformation();
			lift.floors_passed(starting_floor, ending_floor);




		}
		is_processing = y_n_check();
	}

}