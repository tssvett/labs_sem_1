#include<iostream>
#include<string>
using namespace std;
int array_lenght;



int input_array_lenght() {
	cout << "Enter a massive lenght: ";
	while (!(cin >> array_lenght) || (cin.peek() != '\n') || (array_lenght < 0)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error has been detected! Input a correct nonegaive integer number: ";
	}
	return array_lenght;
}

void input_array() {

}

void output(string max_element,int max_counter) {
	cout << "The most friquent symbol is: " << max_element<< "\n";
	cout << "The counter of repeating is: " << max_counter + 1;
}
	
	


int main(){
	input_array_lenght();
	string *array = new string[array_lenght];
	string element;
	string max_element;
	int max_counter = 1;
	int counter = 0;
	for (int i = 0; i < array_lenght; i++) {
		cout << "Enter an array element: ";
		cin >> array[i];  // считываем числа в ячейки массива
	}
	for (int i = 0; i < array_lenght; i++) {
		for (int j = i+1; j < array_lenght; j++) {
			if (array[i] == array[j]) {
				counter++;
				element = array[j] ;
			}
		}
		if (counter >= max_counter) {
			max_counter = counter ;
			counter = 0;
			max_element = element;
			element = "";
		}
	}
	output(max_element, max_counter);
}

