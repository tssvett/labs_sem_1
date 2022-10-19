#include<iostream>
#include<fstream>		// для работы с файлами
#include<vector>
using namespace std;

void string_output(vector<char>& words) {		// функция записывает полученную строку в созданный файл
	ofstream file("string_output.txt",ios_base::app);		// создаем файл с заданным именем
	for (int i = 0; i < words.size(); i++) {
		file << words[i];		// записываем в него строку 
	}
	file << endl;
	file.close();		// закрываем файл
	cout << "The string written to a file:" << endl;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива записанного в файл в  консоль
		cout << words[i];
	}
}


 vector<char> string_input() {		// функция которая берет входные данные из файла
	vector<char> words;
	char symbol;
	ifstream file("string_input.txt");
	while((symbol = file.get()) != EOF){		//поштучно забираем символы до конца файла и добавляем их в вектор
		words.push_back(symbol);
	}
	file.close();
	cout << "The string taken from a file is:" << endl;
	for (int i = 0; i < words.size(); i++) {		//		вывод массива извлеченного из файл в конлось
		cout << words[i];
	}
	cout << endl;
	return words;
}



 int spaces_to_star(vector<char>& words) {		// Функция которая заменяет все пробелы на звезды
	 char symbol;
	 int counter = 0;		//счетчик который понадобится для создания рекурсии в другой функции
	 for (int i = 0; i < words.size(); i++) {
		 symbol = words[i];
		 if (symbol == ' ') {		// Если символ пробел заменяем его звездой
			 symbol = '*';
			 words.erase(words.begin() + i);
			 words.insert(words.begin() + i, symbol);
			 counter++;
		 }
	 }
	 return counter;
 }



 void group_to_one_star(vector<char>& words,int counter_before) {		//функция которая заменяет группу звезд(пробелов) одной звездой(пробелом)
	 char symbol;
	 char second_symbol;
	 int counter_after = 0;		//задаем второй счетчик для создания рекурсии
	 for (int i = 0; i < words.size()-1; i++) {
		 symbol = words[i];
		 second_symbol = words[i + 1];
		 if ((symbol == '*')&&(second_symbol == '*')) {		//если символ звезда и след за ним звезда, то убираем одну звезду
			 words.erase(words.begin() + i);
			 counter_after++;
		 }
	 }
	 if (counter_before > counter_after) {		//Использовал рекурисию до момента пока число звезд не станет равным
		 return group_to_one_star(words, counter_after);
	 }
 }


int main() {
	vector<char> words;
	int counter;
	words = string_input();
	counter = spaces_to_star(words);		// замена всех пробелов на звезды
	group_to_one_star(words, counter);
	string_output(words);


}