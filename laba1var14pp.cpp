#include<iostream>
#include<string>
using namespace std;
int array_lenght;
string *array = new string[array_lenght];
string element;
string max_element;
int max_counter = 0;
int counter = 0;


int input_array_lenght() {
	cout << "Enter a massive lenght: ";
	while (!(cin >> array_lenght) || (cin.peek() != '\n') || (array_lenght < 0)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error has been detected! Input a correct nonegaive integer number: ";
	}
	return array_lenght;
}

void input_array(int array_lenght) {
	for (int i = 0; i < array_lenght; i++) {
		cout << "Enter an array element: ";
		cin >> array[i];  // считываем числа в ячейки массива
	}
}

void output(string max_element,int max_counter) {
	cout << "The most friquent symbol is: " << max_element<< "\n";
	cout << "The counter of repeating is: " << max_counter + 1<< "\n";
}
	
	


int main(){
	int array_lenght = input_array_lenght();
	input_array(array_lenght);
	num = arr[0]; <br>
		max_frq = 1; <br>
		for (i = 0; i < N - 1; i++) {
			<br>
				frq = 1; <br>
				for (k = i + 1; k < N; k++) < br >
					if (arr[i] == arr[k]) < br >
						frq += 1; <br>
						if (frq > max_frq) {
							<br>
								max_frq = frq; <br>
								num = arr[i]; <br>
						}<br>
		}<br>
			<br>
								if (max_frq > 1) < br >
									printf("%d раз(а) встречается число %d\n", max_frq, num); <br>
								else<br>
									printf("Все элементы уникальны!\n"); <br>
}<br>
}

