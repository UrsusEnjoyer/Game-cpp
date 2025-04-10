#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void kreski() {
	cout << "---------------------------------\n";
}

int obliczPozostaleZycie(int zycie, int obrazenia) {
	int wynik = zycie - obrazenia;
	return wynik > 0 ? wynik : 0;
}

int leczenie(int zycie, int ile) {
	int wynik = zycie + ile;
	return wynik > 100 ? 100 : wynik;
}

int odpoczynek(int mana) {
	mana += 15;
	if (mana > 50) mana = 50;
	cout << "Odpoczywasz... Twoja mana wynosi teraz: " << mana << endl;
	return mana;
}

bool dropMikstury() {
	return rand() % 100 < 10; // 10% szansy
}

int wybierzAtak(int sila, int& mana) {
	cout << "Wybierz rodzaj ataku:\n";
	cout << "1. Lekki (50% sily, 100% trafienia, koszt 5 many)\n";
	cout << "2. Sredni (75% sily, 80% trafienia, koszt 10 many)\n";
	cout << "3. Mocny (100% sily, 50% trafienia, koszt 20 many)\n";
	cout << "Wybór: ";
	char wybor;
	cin >> wybor;

	int trafienie = rand() % 100;
	int wynik = 0;

	switch(wybor) {
		case '1':
			if (mana >= 5) {
				mana -= 5;
				wynik = sila * 0.5;
				cout << "Lekki atak trafia za " << wynik << " obrazen. Pozostala mana: " << mana << endl;
				return wynik;
			} else {
				cout << "Nie masz wystarczajaco many!\n";
				return 0;
			}
		case '2':
			if (mana >= 10) {
				mana -= 10;
				if (trafienie < 80) {
					wynik = sila * 0.75;
					cout << "Sredni atak trafia za " << wynik << " obrazen. Pozostala mana: " << mana << endl;
					return wynik;
				} else {
					cout << "Sredni atak chybia. Pozostala mana: " << mana << endl;
					return 0;
				}
			} else {
				cout << "Nie masz wystarczajaco many!\n";
				return 0;
			}
		case '3':
			if (mana >= 20) {
				mana -= 20;
				if (trafienie < 50) {
					wynik = sila;
					cout << "Mocny atak trafia za " << wynik << " obrazen. Pozostala mana: " << mana << endl;
					return wynik;
				} else {
					cout << "Mocny atak chybia. Pozostala mana: " << mana << endl;
					return 0;
				}
			} else {
				cout << "Nie masz wystarczajaco many!\n";
				return 0;
			}
		default:
			cout << "Zly wybor. Uzywasz lekkiego ataku.\n";
			if (mana >= 5) {
				mana -= 5;
				wynik = sila * 0.5;
				return wynik;
			} else {
				cout << "Brak many nawet na lekki atak!\n";
				return 0;
			}
	}
}

void pelnaWalka(string imie, int& zycie, int sila, int& mana,
                string potwor, int& zyciePotwora, int silaPotwora, int& mikstury) {
	int tura = 1;

	while (zycie > 0 && zyciePotwora > 0) {
		kreski();
		cout << "TURA " << tura << endl;
		cout << "Twoje zycie: " << zycie << " | Mana: " << mana << " | Zycie potwora: " << zyciePotwora << " | Mikstury: " << mikstury << endl;

		cout << "1. Atakuj\n2. Odpocznij\n3. Uzyj mikstury\nWybierz akcje: ";
		char akcja;
		cin >> akcja;

		if (akcja == '1') {
			int obrazenia = wybierzAtak(sila, mana);
			zyciePotwora = obliczPozostaleZycie(zyciePotwora, obrazenia);
		} else if (akcja == '2') {
			mana = odpoczynek(mana);
		} else if (akcja == '3') {
			if (mikstury > 0) {
				int leczenieHP = rand() % 100 + 1;
				zycie = leczenie(zycie, leczenieHP);
				cout << "Uzyles mikstury! Twoje zycie: " << zycie << endl;
				mikstury--;
			} else {
				cout << "Nie masz mikstur!\n";
			}
		} else {
			cout << "Nieznana akcja! Tracisz kolejke.\n";
		}

		if (zyciePotwora > 0) {
			int dmg = rand() % silaPotwora + 1;
			cout << potwor << " atakuje za " << dmg << " obrazen!\n";
			zycie = obliczPozostaleZycie(zycie, dmg);
		}

		if (dropMikstury()) {
			cout << "Znalazles miksture podczas tury!" << endl;
			mikstury++;
		}

		tura++;
	}

	if (zyciePotwora <= 0) {
		cout << potwor << " zostal pokonany!\n";
	} else {
		cout << "Zostales pokonany przez " << potwor << "...\n";
	}
	kreski();
}


int main() {
	srand(time(NULL));

	string potwory[] = {"Zombie", "Pajak", "Robak", "Krzyzak", "Golum"};
	int rozmiar = sizeof(potwory) / sizeof(string);

	string imie;
	cout << "Podaj imie bohatera: ";
	cin >> imie;
	cout << "Witaj: " << imie << " w naszej grze!" << endl;

	int zycie = rand() % 50 + 51;
	int sila = rand() % 20 + 20;
	int mana = 50;
	int mikstury = 0;

	string potwor1 = potwory[rand() % rozmiar];
	string potwor2 = potwory[rand() % rozmiar];
	string potwor3 = potwory[rand() % rozmiar];

	int zycie1 = rand() % 40 + 40;
	int sila1 = rand() % 20 + 10;

	int zycie2 = rand() % 40 + 40;
	int sila2 = rand() % 20 + 10;

	int zycie3 = rand() % 40 + 40;
	int sila3 = rand() % 20 + 10;

	while (zycie > 0) {
		kreski();
		cout << "=============MENU:=============\n";
		cout << "1. Walcz z potworem\n";
		cout << "2. Uzyj mikstury\n";
		cout << "3. Statystyki\n";
		cout << "4. Wyjdz\n";
		cout << "Wybierz opcje: ";
		char opcja;
		cin >> opcja;

		switch (opcja) {
			case '1': {
				cout << "Dostepni przeciwnicy:\n";
				if (zycie1 > 0)
					cout << "1. " << potwor1 << " (Zycie: " << zycie1 << ", Sila: " << sila1 << ")\n";
				if (zycie2 > 0)
					cout << "2. " << potwor2 << " (Zycie: " << zycie2 << ", Sila: " << sila2 << ")\n";
				if (zycie3 > 0)
					cout << "3. " << potwor3 << " (Zycie: " << zycie3 << ", Sila: " << sila3 << ")\n";

				cout << "Wybierz potwora (1-3): ";
				char wybor;
				cin >> wybor;

				switch (wybor) {
					case '1':
						if (zycie1 > 0)
							pelnaWalka(imie, zycie, sila, mana, potwor1, zycie1, sila1, mikstury);
						else cout << potwor1 << " juz pokonany!\n";
						break;
					case '2':
						if (zycie2 > 0)
							pelnaWalka(imie, zycie, sila, mana, potwor2, zycie2, sila2, mikstury);
						else cout << potwor2 << " juz pokonany!\n";
						break;
					case '3':
						if (zycie3 > 0)
							pelnaWalka(imie, zycie, sila, mana, potwor3, zycie3, sila3, mikstury);
						else cout << potwor3 << " juz pokonany!\n";
						break;
					default:
						cout << "Zly wybor!\n";
				}
				break;
			}

			case '2': {
				if (mikstury > 0) {
					cout << "Uzywasz mikstury! Twoje zycie wzroslo.\n";
					zycie = leczenie(zycie, rand() % 100 + 1);
					mikstury--;
				} else {
					cout << "Brak mikstur!\n";
				}
				break;
			}

			case '3': {
				cout << "\nStatystyki bohatera " << imie << ":\n";
				cout << "Zycie: " << zycie << " | Sila: " << sila << " | Mana: " << mana << " | Mikstury: " << mikstury << endl;
				break;
			}

			case '4': {
				cout << "Koniec gry. Dzieki za gre, " << imie << "!\n";
				return 0;
			}

			default:
				cout << "Nieznana opcja!\n";
		}
	}

	cout << "\nNiestety " << imie << " polegl w walce...\n";
	return 0;
}

