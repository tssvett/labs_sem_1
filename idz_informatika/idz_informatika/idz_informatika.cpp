#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;


long long p(string s, int x, int m) //функция которая подсчитывает значение хеша
{
	long long func_value = 0, i, x_v_stepeni = 1, l = s.size();		//для первой итерации x^0 = 1
	for (i = 0; i < l; i++)
	{	
		func_value = ((func_value ) + (((s[i] - '0'))*(x_v_stepeni) % m)) % m;
		x_v_stepeni = (x_v_stepeni) * (x) % m;
	}
	// (a*b) % c = ((a % c) * (b % c)) % c
	return func_value;
}


int main() {
	//Задаю переменные
	int n, m, x;
	string s;
	vector<string> string_array;
	vector<int> counters;
	int counter = 0;
	cin >> n;
	cin >> m;
	cin >> x;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		string_array.push_back(s);
	}
	//Создаю вектор пар для его сортировки, чтобы потом найти одинаковые пары
	vector<pair<long long, int>> all_i;
	for (int i = 0; i < string_array.size(); ++i) {
		long long func_value = p(string_array[i], x, m);
		all_i.push_back(make_pair(func_value, i));
	}
	//Сортировка по значениям функции
	sort(all_i.begin(), all_i.end());
	long long start_value = all_i[0].first;
	//Разделим значения функций по группам
	for (int i = 1; i < all_i.size(); i++) {
		long long prev_func_value = all_i[i - 1].first;
		int prev_i_value = all_i[i - 1].second;
		if (prev_i_value < all_i[i].second && prev_func_value == all_i[i].first) { //если все условия выполнены для пары 
			//значений функции, то счетчик ++
			counter++;
		}
		if (prev_i_value >= all_i[i].second || prev_func_value != start_value) { //если нет то сбрасываем счетчик и обновляем
			//группу
			if (counter != 0) 
				counters.push_back(counter + 1);
			counter = 0;
			start_value = all_i[i].first;
		}
		
	}
	if (counter != 0) {		//пушбекаем последний счетчик
		counters.push_back(counter + 1);
	}
	long long calculated = 0;
	for (int i = 0; i < counters.size(); i++) {	//подсчитываем колличество пар для каждой группы и складываем
		if (counters[i] == 1)
			calculated += 0;
		else 
			calculated += (counters[i] * (counters[i] - 1)) / 2;
	}
	cout << calculated;
} 
