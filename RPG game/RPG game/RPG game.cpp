#include<iostream>
#include<string>
#include <iomanip>
using namespace std;

enum types { Warrior, Mage, Ogre, Skeleton };

class Creature {
protected:
	string name;
	int type;
	int max_hp;
	int cur_hp;
	int min_damage;
	int max_damage;
	double resist;
public:
	string getName() {
		return name;
	}
	int getType() {
		return type;
	}
	int getMax_hp() {
		return max_hp;
	}
	int getCur_hp() {
		return cur_hp;
	}
	int getMin_damage() {
		return min_damage;
	}
	int getMax_damage() {
		return max_damage;
	}
	void attack(Creature& enemy) {
		srand(time(NULL));
		int real_damage = (1 - enemy.resist)* (min_damage + rand() % (max_damage - min_damage));	//урон от минимального до максимального значения
		cout << name << " dealt " << real_damage << " damage to " << enemy.name << endl;
		enemy.take_damage(real_damage);
	}
	void block() {
		resist = 0.5;
		cout << name << " decide to block." << endl;
	}
	void reset_resist() {
		resist = 0;
	}


	void take_damage(int real_damage) {
		cur_hp -= real_damage;
		cout << name << " hp is " << cur_hp << endl;
	}
	bool alive() {
		if (cur_hp > 0) return 1;
		else { cout << name << " IS DEAD? HAHA" << endl; return 0; }
	}

};
class Hero : public Creature {
public:
	Hero(string n, int type) {
		switch (type) {
		case Warrior:
			name = n;
			max_hp = 100;
			cur_hp = max_hp;
			min_damage = 10;
			max_damage = 30;
			resist = 0;
			break;
		case Mage:
			name = n;
			max_hp = 50;
			cur_hp = max_hp;
			min_damage = 20;
			max_damage = 50;
			resist = 0;
			break;
		}

	}
};
class Monster : public Creature {
public:
	Monster(string n, int type) {
		switch (type) {
		case Ogre:
			name = n;
			max_hp = 85;
			cur_hp = max_hp;
			min_damage = 11;
			max_damage = 25;
			resist = 0;
			break;
		case Skeleton:
			name = n;
			max_hp = 40;
			cur_hp = max_hp;
			min_damage = 10;
			max_damage = 30;
			resist = 0;
			break;
		}

	}
};



//Пошаговая стратежка
int main() {
	Hero Rudeus("Rudeus", Mage);
	Monster ghoul("Tvarina", Ogre);
	bool who_attack = 1;
	int turn = 1;
	string action;
	while (Rudeus.alive() && ghoul.alive()) {
		cout << endl << "TURN number " << turn << endl;
		if (who_attack) {
			cout << Rudeus.getName() << ", your turn! " << endl;
			cout << Rudeus.getName() << " HP " << ghoul.getName() << " HP " << endl;
			cout << setw(7) << Rudeus.getCur_hp() << setw(13) << ghoul.getCur_hp() << endl;
			cout << "What will you do? Attack/Block -->";
			cin >> action;
			if (action == "attack") {
				Rudeus.attack(ghoul);
				Rudeus.reset_resist();
			}
			if (action == "block") {
				Rudeus.block();
			}
		}
		if (!who_attack) {
			cout << ghoul.getName() << ", your turn! " << endl;
			cout << Rudeus.getName() << " HP " << ghoul.getName() << " HP " << endl;
			cout << setw(7) << Rudeus.getCur_hp() << setw(13) << ghoul.getCur_hp() << endl;
			cout << "What will you do? Attack/Block -->";
			cin >> action;
			if (action == "attack") {
				ghoul.attack(Rudeus);
				ghoul.reset_resist();
			}
			if (action == "block") {
				ghoul.block();
			}
		}
		if ((Rudeus.alive() && ghoul.alive())) {
			who_attack = !who_attack;
			turn++;
			cout << "Turn is completed." << endl;
		}
	}
}