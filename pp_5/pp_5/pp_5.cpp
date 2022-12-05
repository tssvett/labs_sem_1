#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

class House_Data;	// Объявляю второй класс дружественным первому
class Elevator {	// Создаем класс лифта		КЛАСС ПЕРЕМЕННАЯ	
private:
	string time;
	int starting_floor;
	int ending_floor;

public:
	friend class House_Data;
	Elevator() {	// Конструктор по умолчанию
		time = "0";
		starting_floor = 0;
		ending_floor = 0;
	}

	Elevator(string t, int sf, int ef) {	// Инициализирующий конструктор
		time = t;
		starting_floor = sf;
		ending_floor = ef;
	}

	Elevator(const Elevator& val) : time(val.time), starting_floor(val.starting_floor), ending_floor(val.ending_floor) {}  //Конструктор копирования

	~Elevator() {}	//Деструктор

	void setTime(string t) {	//Сеттер времени
		time = t;
	}

	void setStarting_floor(int sf) {	//Сеттер стартового этажа
		starting_floor = sf;
	}

	void setEnding_floor(int se) {	//Сеттер конечного этажа
		ending_floor = se;
	}

	string getTime() {	//Геттер времени
		return time;
	}

	int getStarting_floor() {	//Геттер стартового этажа
		return starting_floor;
	}

	int getEnding_floor() {	//Геттер конечного этажа
		return ending_floor;
	}

	int passed_calc() {		//функция-член класса, реализующая обработку данных экземпляра класса согласно варианту ОДНА ИЗ ОСОБЕННОСТЕЙ
		int passed = abs(starting_floor - ending_floor);
		return passed;
	}
	friend istream& operator>>(istream &, Elevator&);	//Дружественная функция позволяет менять приватные переменные
	friend ostream& operator<<(ostream &, Elevator);	//Здесь находятся все 4 перегрузки
	friend ifstream& operator>>(ifstream &, vector<Elevator>&);		//Перегрузки операторов ввода вывода консоли
	friend ofstream& operator<< (ofstream &, Elevator&);	//Перегрузки операторов ввода вывода файла
	friend ifstream& operator>> (ifstream &, vector<House_Data>&);
};	


class House_Data{
private:
	string model;
	int movement_number;
	vector<Elevator> information;

public:
	friend class Elevator;		//Объявляю класс дружественным этому
	House_Data() {	// Конструктор по умолчанию
		model = "0";
		movement_number = 0;
		information = {};		//Пустой вектор
	}

	House_Data(string m, int mn, vector<Elevator> arr) {	// Инициализирующий конструктор
		model = m;
		movement_number =mn ;
		information = arr;
	}

	House_Data(const House_Data& val) : model(val.model), movement_number(val.movement_number), information(val.information) {}  //Конструктор копирования

	~House_Data() {}	//Деструктор

	void setModel(string m) {	//Сеттер времени
		model = m;
	}

	void setMovement_number(int mn) {	//Сеттер стартового этажа
		movement_number = mn;
	}

	void setInformation(vector<Elevator> arr) {	//Сеттер конечного этажа
		information = arr;
	}

	string getModel() {	//Геттер времени
		return model;
	}

	int getMovement_number() {	//Геттер стартового этажа
		return movement_number;
	}

	vector<Elevator> getInformation() {	//Геттер конечного этажа
		return information;
	}

	bool error_check() {		//проверяем j объект
		vector<bool> correct;
		if (movement_number != 0) {
			for (int i = 0; i < movement_number; i++) {
				if (information[i].time != "0" && information[i].starting_floor > 0 && 
					information[i].ending_floor > 0 && model != "0" && movement_number > 0 &&information.size() != 0)
					correct.push_back(0);	//если ошибки нет пушбек 0
				else
					correct.push_back(1);
			}
			bool max = 0;
			for (int j = 0; j < correct.size(); j++) {
				if (correct[j] == 1)
					max = 1;
			}
			return max;
		}
		else
			return 1;
	}



	int passed_inDay_calc() {		//функция-член класса, реализующая обработку данных экземпляра класса согласно варианту ОДНА ИЗ ОСОБЕННОСТЕЙ
		int sum = 0;
		for (int i = 0; i < information.size(); i++) {
			sum += information[i].passed_calc();
		}
		return sum;
	}

	friend istream& operator>>(istream &, House_Data&);	//Дружественная функция позволяет менять приватные переменные
	friend ostream& operator<<(ostream &, House_Data);	//Здесь находятся все 4 перегрузки
	friend ifstream& operator>>(ifstream &, vector<House_Data>&);		//Перегрузки операторов ввода вывода консоли
	friend ofstream& operator<< (ofstream &, House_Data&);	//Перегрузки операторов ввода вывода файла
};

ostream& operator<<(ostream &out, Elevator lift)		// Перегрузка оператора вывода в консоль ОДНА ИЗ ОСОБЕННОСТЕЙ
{
	out << lift.time << ' ' << lift.starting_floor << ' ' << lift.ending_floor << ' ' << endl;
	return out;
}

ostream& operator<<(ostream &out, House_Data data)		// Перегрузка оператора вывода в консоль ОДНА ИЗ ОСОБЕННОСТЕЙ
{
	out << data.model << ' ' << data.movement_number << endl;
	for (int i = 0; i < data.information.size(); i++) {
		out <<setw(22) << data.information[i];
	}
	return out;
}


ofstream& operator <<(ofstream &out, Elevator& lift) {	//Перегрузка оператора вывода в файл ОДНА ИЗ ОСОБЕННОСТЕЙ
	out << setw(5) << lift.time << ' ' << setw(10) << lift.starting_floor << ' '
		<< setw(10) << lift.ending_floor << ' ' << setw(10) << lift.passed_calc() << endl;
	return out;
}

ofstream& operator <<(ofstream &out, House_Data& data) {	//Перегрузка оператора вывода в файл ОДНА ИЗ ОСОБЕННОСТЕЙ
	out << data.model << ' ' << ' ' << data.movement_number << ' ' << data.passed_inDay_calc() << endl << endl;
	for (int i = 0; i < data.information.size(); i++) {
		out << data.information[i] <<endl;
	}

	return out;
}


istream& operator>>(istream &in, Elevator& lift) {  //Перегрузка оператора ввода в консоль ОДНА ИЗ ОСОБЕННОСТЕЙ
	bool flag = true;
	string string_hour;
	string string_minute;
	int hour;
	int minute;
	while (flag) {
		in >> lift.time;
		in.clear();
		if (lift.time.size() == 5) {
			if (isdigit(lift.time[0]) && isdigit(lift.time[1]) && lift.time[2] == ':'
				&& isdigit(lift.time[3]) && isdigit(lift.time[4])) {
				string_hour.push_back(lift.time[0]);
				string_hour.push_back(lift.time[1]);
				string_minute.push_back(lift.time[3]);
				string_minute.push_back(lift.time[4]);
				hour = stoi(string_hour);
				minute = stoi(string_minute);
				if ((hour >= 0 && hour < 24) && (minute >= 0 && minute < 60)) {
					flag = false;
				}
				else {
					string_hour.pop_back();
					string_hour.pop_back();
					string_minute.pop_back();
					string_minute.pop_back();
					flag = true;
					cout << "Error! Enter CORRECT time: ";
				}
			}
			else {
				flag = true;
				cout << "Error! Enter CORRECT time: ";
			}
		}
		else {
			flag = true;
			cout << "Error! Enter CORRECT time: ";
		}
	}
	while (!(in >> lift.starting_floor) || (cin.peek() != '\n') || (lift.starting_floor <= 0)) {	//Работа с потоком
		in.clear(); // очищаем поток от флага ошибки
		while (in.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a CORRECT number: "; // выводим ошибку
	}
	while (!(in >> lift.ending_floor) || (cin.peek() != '\n') || (lift.ending_floor <= 0)) {	//Работа с потоком
		in.clear(); // очищаем поток от флага ошибки
		while (in.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a CORRECT number: "; // выводим ошибку
	}
	return in;
}

istream& operator>>(istream &in, House_Data& data) {  //Перегрузка оператора ввода в консоль ОДНА ИЗ ОСОБЕННОСТЕЙ
	bool flag = true;
	while (flag) {
		in >> data.model;
		in.clear();
		if ((data.model.size() == 5)) {
			if ((!(isdigit(data.model[0]))) && (!(isdigit(data.model[1]))) && (isdigit(data.model[2]))
				&& (isdigit(data.model[3])) && (isdigit(data.model[4]))) {
				flag = false;
			}
			else {
				flag = true;
				cout << "Error! Enter CORRECT model: ";
			}
		}
		else {
			flag = true;
			cout << "Error! Enter CORRECT model: ";
		}
	}
	while (!(in >> data.movement_number) || (in.peek() != '\n') || (data.movement_number <= 0)) {	//Работа с потоком
		in.clear(); // очищаем поток от флага ошибки
		while (in.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a CORRECT number: "; // выводим ошибку
	}
	for (int i = 0; i < data.movement_number; i++) {
		Elevator lift;
		cout << "Input correct time in format (hh:mm), starting floor, ending floor. Each field input in separated string." << endl;
		in >> lift;
		data.information.push_back(lift);
	}
	return in;
}


ifstream& operator>> (ifstream &ifile, vector<Elevator>& lifts) {		// Перегрузка оператора ввода из файла ОДНА ИЗ ОСОБЕННОСТЕЙ**
	string starting;
	while ((getline(ifile, starting))) {
		bool flag = true;
		Elevator lift;
		string times;
		string string_hour;
		string string_minute;
		int hour;
		int minute;
		string string_number1 = "";
		string string_number2 = "";
		if (starting.size() >= 5) {
			for (int i = 0; i < 5; i++) {
				times.push_back(starting[i]);
			}
		}
		else {
			flag = false;
		}
		if (flag && isdigit(times[0]) && isdigit(times[1]) && times[2] == ':' && isdigit(times[3]) && isdigit(times[4])) {
			string_hour.push_back(times[0]);
			string_hour.push_back(times[1]);
			string_minute.push_back(times[3]);
			string_minute.push_back(times[4]);
			hour = stoi(string_hour);
			minute = stoi(string_minute);
			if ((hour >= 0 && hour < 24) && (minute >= 0 && minute < 60)) {
				lift.time = times;
			}
			else {
				string_hour.pop_back();
				string_hour.pop_back();
				string_minute.pop_back();
				string_minute.pop_back();
				flag = false;
			}

		}
		else {
			flag = false;
		}
		starting.erase(0, 6);		//Убираем время
		while (flag && starting[0] == ' ')
			starting.erase(0);
		if (flag && starting.size() >= 1) {
			for (int i = 0; i < starting.size(); i++) {
				string_number1 += starting[i];
				if (starting[i] == ' ') {
					i = starting.size();
				}
			}
			lift.starting_floor = stoi(string_number1);
			starting.erase(0, string_number1.size());
		}
		else
		{
			flag = false;
		}

		if (flag && starting.size() >= 1) {
			for (int i = 0; i < starting.size(); i++) {
				string_number2 += starting[i];
				if (starting[i] == ' ') {
					i = starting.size();
				}
			}
			lift.ending_floor = stoi(string_number2);
			starting.erase(0, 100);
		}
		else
		{
			flag = false;
		}
		lifts.push_back(lift);
	}
	return ifile;
}


ifstream& operator>> (ifstream &ifile, vector<House_Data>& datas) {		// Перегрузка оператора ввода из файла ОДНА ИЗ ОСОБЕННОСТЕЙ**
	string starting;
	while ((getline(ifile, starting))) {
		bool flag = true;
		House_Data data;
		string model;
		string move_number;
		string string_number1 = "";
		if (starting.size() >= 5) {		//Проверяем модель на корректность
			for (int i = 0; i < 5; i++) {
				model.push_back(starting[i]);
			}
		}
		else 
			flag = false;
		if (flag && (!(isdigit(model[0]))) && (!(isdigit(model[1]))) && (isdigit(model[2]))
			&& (isdigit(model[3])) && (isdigit(model[4]))) 
			data.model = model;
		else 
			flag = false;
		starting.erase(0, 6);		//Убираем модель из строки
		while (flag && starting[0] == ' ')		//вместе  с пробелом
			starting.erase(0);
		if (flag && starting.size() >= 1) {		//Проверяем корректность количества передвижений
			for (int i = 0; i < starting.size(); i++) {
				string_number1 += starting[i];
				if (starting[i] == ' ') {
					i = starting.size();
				}
			}
			data.movement_number = stoi(string_number1);
			starting.erase(0, string_number1.size());		//Убираем из строки количество передвижений
		}
		else
			flag = false;
		for (int j = 0; j < data.movement_number; j++) {		//Ввод объектов Elevator по колличеству передвижений
			string string_number2 = "";
			string string_number3 = "";
			Elevator lift;
			string times;
			string string_hour;
			string string_minute;
			int hour;
			int minute;
			if (starting.size() >= 5) {		//Проверка времени
				for (int i = 0; i < 5; i++) {
					times.push_back(starting[i]);
				}
			}
			else 
				flag = false;
			if (flag && isdigit(times[0]) && isdigit(times[1]) && times[2] == ':' && isdigit(times[3]) && isdigit(times[4])) {
				string_hour.push_back(times[0]);
				string_hour.push_back(times[1]);
				string_minute.push_back(times[3]);
				string_minute.push_back(times[4]);
				hour = stoi(string_hour);
				minute = stoi(string_minute);
				if ((hour >= 0 && hour < 24) && (minute >= 0 && minute < 60))
					lift.time = times;
				else {
					string_hour.pop_back();
					string_hour.pop_back();
					string_minute.pop_back();
					string_minute.pop_back();
					flag = false;
				}

			}
			else 
				flag = false;
			starting.erase(0, 6);		//Удаляем из строки время
			if (flag && starting.size() >= 1) {		//проверка стартового этажа
				int i = 0;
				while (starting[i] != ' ' &&  isdigit(starting[i])) {
					string_number2 += starting[i];
					i++;
				}
				if (string_number2 != "")
				lift.starting_floor = stoi(string_number2);
				else
					flag = false;
			}
			else
				flag = false;
			starting.erase(0, string_number2.size() + 1);
			if (flag && starting.size() >= 1) {		//Проверка конечного этажа
				int k = 0;
				while (starting[k] != '\0' && starting[k] != ' ' && isdigit(starting[k])) {
					string_number3 += starting[k];
					k++;
				}
				if (string_number3 != "")
					lift.ending_floor = stoi(string_number3);
				else
					flag = false;
			}
			else
				flag = false;
			starting.erase(0, string_number3.size() + 1);		//удаляем из строки
			data.information.push_back(lift);
		}
		datas.push_back(data);
	}
	return ifile;
}


int correct_check() {		// Функция проверки длины массива
	int lenght;
	while (!(cin >> lenght) || (cin.peek() != '\n') || (lenght <= 0)) {	//Работа с потоком
		cin.clear(); // очищаем поток от флага ошибки
		while (cin.get() != '\n'); // извлекаем ошибочные символы, считывая до конца строчки
		cout << "Error! Input a CORRECT number: "; // выводим ошибку
	}
	return lenght;	// возвращаем длину
}


bool y_n_check() { // Функция возвращает 1 0 в зависимости от y n
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


string file_name_input() {	//Функция проверки названия файла на корректность
	bool is_open = true;
	string ifile_name;
	cout << "Enter a file name from which take input data: " << endl;
	while (is_open) {	//пока файл открыт
		cin.clear();
		cin >> ifile_name;
		ifstream ifile(ifile_name);		// инициализируем файл для входных файлов
		if (!ifile.is_open()) {	//Если файл нельзя открыть выкидываем ошибку
			is_open = true;
			cout << "Error #1 This file cannot be opened. Enter correct filename. " << endl;
		}
		else {
			is_open = false;
			if (ifile.peek() == EOF) {	//Если файл пустой выкидываем ошибку
				is_open = true;
				cout << "Error#2  This file is empty. Enter correct filename " << endl;
			}
		}
		while (cin.get() != '\n');
	}
	return ifile_name;
}


void input_menu_output() {	//Просто вывод
	cout << "Console application designed to work with information about the evelator movement" << endl;
	cout << "Choose the object input method:" << endl;
	cout << "1 -- input objects by keyboard" << endl;
	cout << "2 -- input objects from file" << endl;
	cout << "Your choise ----> ";
}


void output_menu_output() {	//Просто вывод
	cout << "Choose the object output method:" << endl;
	cout << "1 -- output objects in console" << endl;
	cout << "2 -- output objects in file" << endl;
	cout << "Your choise ----> ";
}


int switch_symbol_input() {	//Функция проверки символа для свича
	char symbol;
	bool flag = true;
	while (flag) {
		cin >> symbol;
		if ((symbol == '1') && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return 1;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		if ((symbol == '2') && (cin.peek() == '\n')) {		// если нет, то
			flag = false;		// зацикленность проверки y/n отключается
			return 2;		// функция возвращает false и вся программа прекращает свое выполнение
		}
		while (cin.get() != '\n');
		cout << "Error! Input  1 or 2" << endl;	// извлекаем ошибочные символы, считывая до конца строчки
		cout << "--> ";
	}
}


void switch_cycle_console(vector<House_Data> objects_array, vector<int> passed_array) {
	for (int i = 0; i < objects_array.size(); i++) {
		cout << "Object number " << i + 1 << ": " << objects_array[i];
		cout << "Object number " << i + 1 << " passed floors: " << passed_array[i] << endl;
		cout << endl;
	}
}


void before_cin_introdution(int i) {
	cout << "Initialization the " << i + 1 << " class object" << endl;
	cout << "Input model in format (LP201) and number of movements per day. Next input is information about mo"
		"vement. Each field input in separated string." << endl;
}


void switch_cycle_file(vector<House_Data> objects_array, vector<int> passed_array, ofstream& ofile) {
	for (int i = 0; i < objects_array.size(); i++) {
		ofile << objects_array[i] << endl;
	}
	ofile << "\n" << endl;
}


void out_switch(vector<House_Data> objects_array, vector<int> passed_array, ofstream& ofile) {
	output_menu_output();
	int output_symbol = switch_symbol_input();	//Вводим символ для выводного свича
	switch (output_symbol) {
	case 1:
		switch_cycle_console(objects_array, passed_array);
		break;
	case 2:
		switch_cycle_file(objects_array, passed_array, ofile);
		break;
	}
	cout << "Output completed successfully." << endl;
}


int main() {
	bool is_processing = true;
	int lenght;
	int input_symbol;	//объявляем переменные
	int output_symbol;
	string ofile_name = "output.txt";
	string ifile_name;
	ofstream ofile(ofile_name);
	while (is_processing) {	//Зацикливаем программу
		bool error;
		vector<House_Data> objects_array;
		vector<int> passed_array;
		input_menu_output();
		input_symbol = switch_symbol_input();	//вводим символ для свича
		switch (input_symbol) {
		case 1:		//Если 1 то вводим в консоль с клавиатуры
			cout << "Input number of objects: ";
			lenght = correct_check();
			for (int i = 0; i < lenght; i++) {
				House_Data data;
				before_cin_introdution(i);
				cin >> data;
				objects_array.push_back(data);
				passed_array.push_back(data.passed_inDay_calc());
			}
			out_switch(objects_array, passed_array, ofile);
			break;
		case 2:	// Если 2 вводим из файла
			ifile_name = file_name_input();
			ifstream ifile(ifile_name);
			vector<House_Data> data;
			ifile >> data;
			for (int i = 0; i < data.size(); i++) {
				objects_array.push_back(data[i]);
				passed_array.push_back(data[i].passed_inDay_calc());
				if (data[i].error_check() == 1){		//Отлавливаем и обрабатываем ошибки внутри полей класса
					cout << "Error with object number " << i + 1 <<
						" has been detected! Console app will ignore it. Output without damaged object." << endl;
					objects_array.pop_back();
					passed_array.pop_back();
				}
			}
			out_switch(objects_array, passed_array, ofile);
			break;
		}
		is_processing = y_n_check();
	}
}