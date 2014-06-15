#include "Gracz.hpp"
#include "Gra.hpp"
#include <vector>
#include "Krazek.hpp"
#include "Typy.hpp"
#include <utility>
#include <iostream>
#include <cmath>

/*! \file */

/*! 
* \brief Gracz
* 	
* Funkcje zwiazane z klasa Gracz	
* 	
*/

using namespace std;

//konstruktor
//typ czy czlowek czy komputer, kolor, wskaznik do planszy
Gracz::Gracz(_Typ_Gracza gracz, _Kolor kol, Plansza* plansza) {
	Typ_Gracza = gracz;
	Kolor = kol;
	Plansza_gry = plansza;
	Czy_Ruchy_To_Bicia = false; //gdy jest wiecej bic to ma byc kolejny ruch tego krazka.
}
//destuktor
Gracz::~Gracz() {

}
/*!
* \brief Funkcja Czy_Jest_Bicie.
*
* Sprawdzamy czy mozemy bic. Czy pionek do zbicie jest nie nasz.
* Czy pole za pionkiem po biciu jest w planszy
* Czy pole po biciu jest wolne.
* 
*/
bool Gracz::Czy_Jest_Bicie(Punkt Z, Punkt Do, Krazek krazek) {
	if (!Plansza_gry->Czy_Punkt_W_Planszy(Do))
		return false; //sprawdza czy pkt jest w plasznysz do ktorego chcemy zrobic bicie
	if (!Plansza_gry->Czy_Jest(Do)) { /* sprawdza pole na ktore chce przeskoczyc pobiciu jest wolne*/
		Krazek* pomocniczy; //gdy tak, to robi wskaznik do krazka, przypisuje do wksaznika krazek
		if (Plansza_gry->Wez_Krazek(Punkt((Z.x + Do.x) / 2, (Z.y + Do.y) / 2),
				&pomocniczy)) //sprawdza czy jest to pionek innego koloru od naszego
			if (pomocniczy->Kolor != krazek.Kolor) //gdy rozny
				return true;

	}
	return false;
}

//szablon klasy gdzie mozna wpisac dwie dowolne klasy
pair<Krazek, Punkt> Gracz::Wybierz_Ruch() {
	/*	int x = rand() % Lista_Ruchow.size();
	 return Lista_Ruchow[x].front();
	 */ //ruch na pale
	int max = -1000000;//zeby pierwszy ruch byl zawsze wiekszy
	int indeks_najlepszego = 0;

	for (int i = 0; i < Lista_Ruchow.size(); i++) {
		int wynik = Zasymuluj_Ruch(Lista_Ruchow[i].front()); //wynik=punktowy stan planszy po ruchu
		if (wynik > max) {
			max = wynik;
			indeks_najlepszego = i;
		}
	}
	return Lista_Ruchow[indeks_najlepszego].front();  //pierwszy ruch z vectora ruchow
}
/*!
* \brief Czy_Zostal_Wybrany_Poprawny_Ruch
*
* Sprawdzamy czy ruch wybrany jest na licie ruchow
* Czy jest poprawny,
* Mozliwy
* 
*/
bool Gracz::Czy_Zostal_Wybrany_Poprawny_Ruch(pair<Krazek, Punkt> Ruch) {
	for (auto it = Lista_Ruchow.begin(); it != Lista_Ruchow.end(); it++)
		if (it->front().first == Ruch.first
				&& it->front().second.x == Ruch.second.x
				&& it->front().second.y == Ruch.second.y)
			return true;
	return false;
}
/*!
* \brief Wykonaj_Ruch
*
* Sprawdza jaki jest aktualny krazek.
* Sprawdza czy ruch jest biciem
* Jesli tak to wykonkuje bicie
* Jak nie to zwykly ruch wykonuje o ile mozliwy
* Gdy na ostatnim polu to zamienia na DAMKA
* 
*/
void Gracz::Wykonaj_Ruch(pair<Krazek, Punkt> Ruch) {
	if (Czy_Ruchy_To_Bicia) {
		_Kolor kolor;
		Punkt Punkt;
		if (Ruch.first.Kolor == BIALY)
			kolor = CZARNY;
		else
			kolor = BIALY;
		Punkt.x = (Ruch.first.x() + Ruch.second.x) / 2;
		Punkt.y = (Ruch.first.y() + Ruch.second.y) / 2;
		Plansza_gry->Usun_Krazek(Krazek(Punkt, kolor));
		//gdy to jest bicie to usuwa krazek pomiedzy  Z do DO.
	}
	if (((Kolor == BIALY) && (Ruch.second.y == 0)) //koncowe dla bialych jest zerowa
			|| ((Kolor == CZARNY) && (Ruch.second.y == 7))) { //koncowe dla czarnych jest 7
		Ruch.first.Awansuj();
		//Ruch.first.Typ = Krazek::DAMKA;
	}
	Plansza_gry->Przenies_Krazek(Ruch.first, Ruch.second); //przenosi krazek z Z do DO.
}
/*!
* \brief Stworz_Liste_Bic
*
* Bedzie to przydatne przy biciach wielokrotnych.
* Gdy nie ma bicia wielokrotnego oddaje ruch przeciwnikowi.
* 
*/
//gdy beda bicia wielokrotne
void Gracz::Stworz_Liste_Bic(Krazek krazek) {
	Wyczysc_Liste_Ruchow();
	signed int Kierunek_y = 1; //czarne do dolu czyli 1.   //zmienna za znakiem
	if (Kolor == BIALY)
		Kierunek_y = -1;
	//Sprawdzenie w lewo i w prawo. czy bicie
	for (signed int Kierunek_x = 1; Kierunek_x >= -1; Kierunek_x += -2) {
		//Sprawdzenie w gore i w dol.
		if (krazek.Typ == Krazek::DAMKA)
			for (signed int Kierunek_y = 1; Kierunek_y >= -1; Kierunek_y += -2)
			//Sprawdzanie czy jest bicie
					{
				Punkt Punkt1 = Punkt((signed int) (krazek.x()),
						(signed int) (krazek.y()));
				Punkt Punkt2 = Punkt(Punkt1.x + 2 * Kierunek_x,
						Punkt1.y + 2 * Kierunek_y);
				if (Czy_Jest_Bicie(Punkt1, Punkt2, krazek)) {
					Lista_Ruchow.push_back(vector<pair<Krazek, Punkt> >());
					Lista_Ruchow.back().push_back(
							pair<Krazek, Punkt>(krazek, Punkt2));
					Czy_Ruchy_To_Bicia = true;
				}
			}
		else {
			Punkt Punkt1 = Punkt((signed int) (krazek.x()),
					(signed int) (krazek.y()));
			Punkt Punkt2 = Punkt(Punkt1.x + 2 * Kierunek_x,
					Punkt1.y + 2 * Kierunek_y);
			if (Czy_Jest_Bicie(Punkt1, Punkt2, krazek)) {
				Lista_Ruchow.push_back(vector<pair<Krazek, Punkt> >());
				Lista_Ruchow.back().push_back(
						pair<Krazek, Punkt>(krazek, Punkt2));
				Czy_Ruchy_To_Bicia = true;
			}
		}
	}
	if (Lista_Ruchow.empty())
		Czy_Ruchy_To_Bicia = false;
}
/*!
* \brief Stworz_Liste_Ruchow
*
* Tworzymy liste ruchow dla wszystkich pionkow dla gracza.

* 
*/
//stwarza jedna liste wszystkich ruchow dla wszystkich pionkow dalengo gracza
void Gracz::Stworz_Liste_Ruchow() {
	Wyczysc_Liste_Ruchow();
	vector<Krazek>* Krazki_Gracza = &Plansza_gry->Biale_Krazki;
	vector<Krazek>* Krazki_Przeciwnika = &Plansza_gry->Czarne_Krazki;
	signed int Kierunek_y = -1;
	//zmiana gracza
	if (Kolor == CZARNY) {
		Krazki_Gracza = &Plansza_gry->Czarne_Krazki;
		Krazki_Przeciwnika = &Plansza_gry->Biale_Krazki;
		Kierunek_y = 1;
	}

//Petla- Sprawdzenie czy sa bicia i ew dodanie ich do listy.
	for (auto it = Krazki_Gracza->begin(); it != Krazki_Gracza->end(); it++)
		//Sprawdzenie w lewo i w prawo.
		for (signed int Kierunek_x = 1; Kierunek_x >= -1; Kierunek_x += -2) {
			//Sprawdzenie w gore i w dol.
			if (it->Typ == Krazek::DAMKA)
				for (signed int Kierunek_y = 1; Kierunek_y >= -1; Kierunek_y +=
						-2)
						//Sprawdzanie czy jest bicie
						{
					Punkt Punkt1 = Punkt((signed int) (it->x()),
							(signed int) (it->y()));
					Punkt Punkt2 = Punkt(Punkt1.x + 2 * Kierunek_x,
							Punkt1.y + 2 * Kierunek_y);
					if (Czy_Jest_Bicie(Punkt1, Punkt2, *it)) {
						Lista_Ruchow.push_back(
								vector<pair<Krazek, Punkt> >());
						Lista_Ruchow.back().push_back(
								pair<Krazek, Punkt>(*it, Punkt2));
						Czy_Ruchy_To_Bicia = true;
					}
				}
			else {
				Punkt Punkt1 = Punkt((signed int) (it->x()),
						(signed int) (it->y()));
				Punkt Punkt2 = Punkt(Punkt1.x + 2 * Kierunek_x,
						Punkt1.y + 2 * Kierunek_y);
				if (Czy_Jest_Bicie(Punkt1, Punkt2, *it)) {
					Lista_Ruchow.push_back(vector<pair<Krazek, Punkt> >());
					Lista_Ruchow.back().push_back(
							pair<Krazek, Punkt>(*it, Punkt2));
					Czy_Ruchy_To_Bicia = true;
				}
			}
		}

		//gdy juz nie ma zadnych bic to dopiero zabiera sie za wzykle ruchy
	if (Lista_Ruchow.empty()) {
//Petla- Sprawdzenie czy sa bicia i ew dodanie ich do listy.
		for (auto it = Krazki_Gracza->begin(); it != Krazki_Gracza->end(); it++)
			//Sprawdzenie w lewo i w prawo.
			for (signed int Kierunek_x = 1; Kierunek_x >= -1; Kierunek_x += -2)
				if (it->Typ == Krazek::ZWYKLY)
				//Sprawdzenie w gore i w dol.
				//Sprawdzanie czy jest bicie
						{
					int Kierunek_y;
					if (Kolor == BIALY)
						Kierunek_y = -1;
					else
						Kierunek_y = 1;
					Punkt Punkt1 = Punkt((signed int) (it->x()),
							(signed int) (it->y()));
					Punkt Punkt2 = Punkt(Punkt1.x + Kierunek_x,
							Punkt1.y + Kierunek_y);
					if (!Plansza_gry->Czy_Jest(Punkt2)
							&& (Plansza_gry->Czy_Punkt_W_Planszy(Punkt2))) {

						Lista_Ruchow.push_back(
								vector<pair<Krazek, Punkt> >());
						Lista_Ruchow.back().push_back(
								pair<Krazek, Punkt>(*it, Punkt2));
						Czy_Ruchy_To_Bicia = false;

					}
				} else {
					for (signed int Kierunek_y = 1; Kierunek_y >= -1;
							Kierunek_y += -2) {
						Punkt Punkt1 = Punkt((signed int) (it->x()),
								(signed int) (it->y()));
						Punkt Punkt2 = Punkt(Punkt1.x + Kierunek_x,
								Punkt1.y + Kierunek_y);
						if (!Plansza_gry->Czy_Jest(Punkt2)
								&& (Plansza_gry->Czy_Punkt_W_Planszy(Punkt2))) {

							Lista_Ruchow.push_back(
									vector<pair<Krazek, Punkt> >());
							Lista_Ruchow.back().push_back(
									pair<Krazek, Punkt>(*it, Punkt2));
							Czy_Ruchy_To_Bicia = false;
						}
					}

				}
	}
}
/*void Gracz::Wyswietl_Liste_Ruchow() {
	cout << "Mozliwe Ruchy to:" << endl;
	for (auto i = Lista_Ruchow.begin(); i != Lista_Ruchow.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++)
			cout << "Krazek " << j->first.x() << " " << j->first.y()
					<< " Na pole " << j->second.x << " " << j->second.y << "\t";
		cout << endl;
	}
}*/ //sprawdzenie czy dziala lista ruchow
/*!
* \brief Wyczysc_Liste_Ruchow
*
* Usuwamy wszystko z listy ruchow gracza.
* 
*/
void Gracz::Wyczysc_Liste_Ruchow() {
	for (auto it = Lista_Ruchow.begin(); it != Lista_Ruchow.end(); it++)
		while (!it->empty())
			it->pop_back();
	while (!Lista_Ruchow.empty())
		Lista_Ruchow.pop_back();
}
/*!
* \brief Zasymuluj_Ruch
*
* Symulujemy ruch
* By sprawdzic stan punktowy 
* I ocenic najkorzystniejszy ruch.
* 
*/
//stan pkt po ruchu sprwadzajcym
int Gracz::Zasymuluj_Ruch(pair<Krazek, Punkt> Ruch) {

	Plansza Symulowana_Plansza;
	_Kolor kolor_przeciwnika;

	Symulowana_Plansza.Czarne_Krazki = Plansza_gry->Czarne_Krazki;
	Symulowana_Plansza.Biale_Krazki = Plansza_gry->Biale_Krazki;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Symulowana_Plansza.Pola_Gry[i][j] = Plansza_gry->Pola_Gry[i][j];

	if (Kolor == BIALY)
		kolor_przeciwnika = CZARNY;
	else
		kolor_przeciwnika = BIALY;

	Gracz gracz_symulujacy(KOMPUTER, Kolor, &Symulowana_Plansza);
	Gracz przeciwnik(KOMPUTER, kolor_przeciwnika, &Symulowana_Plansza);

	gracz_symulujacy.Wykonaj_Ruch(Ruch);
	return (gracz_symulujacy.Punkty() - przeciwnik.Punkty_Za_Krazki());
}
/*!
* \brief Punkty_Za_Krazki
*
* Punkty za kr¹¿ki.
* 15 za ZWYKLY krazek
* 25 za DAMKA
*/
int Gracz::Punkty_Za_Krazki() {
	const int Punkty_Za_Zwykly_Krazek = 15;
	const int Punkty_Za_Damke = 25;

	int punkty = 0;

	vector<Krazek>* Krazki;
	if (Kolor == BIALY)
		Krazki = &Plansza_gry->Biale_Krazki;
	else
		Krazki = &Plansza_gry->Czarne_Krazki;

	//Zliczenie punktow za ilosc i typ krazkow.
	for (vector<Krazek>::iterator it = Krazki->begin(); it != Krazki->end();
			it++) {
		if (it->Typ == Krazek::ZWYKLY)
			punkty += Punkty_Za_Zwykly_Krazek;
		else
			punkty += Punkty_Za_Damke;
	}

	//Zliczenie Punktow za pozycje.
	//W przypadku zwyklych krazkow premiowane jest bliskosc jak najblizej konca mapy
	//oraz bliskosc do srodka.
	//W przypadku damek tylko bliskosc do srodka
	for (vector<Krazek>::iterator it = Krazki->begin(); it != Krazki->end();
			it++) {
		if (it->Typ == Krazek::ZWYKLY) {
			if (Kolor == BIALY)
				punkty += 14 - 2*it->y(); // 14 i odejmuje 2 za ka¿de oddalenie siê od kraju planszy
			else
				punkty += 2*it->y();
		} else
			punkty += 3.5*3.5 - (abs(3.5 - it->x()) * abs(3.5 - it->y()));
	}
	return punkty;
}
/*!
* \brief Punkty
*
* Punkty
* 10 za bicia (nie zaleznie od ilosci)
* -40 za bicie przeciwnika (nie zaleznie od ilosci)
*/
int Gracz::Punkty() {
	int punkty = Punkty_Za_Krazki();

	//Punkty za bicia.
	Plansza Symulowana_Plansza;
	_Kolor kolor_przeciwnika;
	//przepisujemy krazki do nowej plaszy
	Symulowana_Plansza.Czarne_Krazki = Plansza_gry->Czarne_Krazki;
	Symulowana_Plansza.Biale_Krazki = Plansza_gry->Biale_Krazki;
	//mo¿na tylko po czarnych sie ruszac
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Symulowana_Plansza.Pola_Gry[i][j] = Plansza_gry->Pola_Gry[i][j];

	if (Kolor == BIALY)
		kolor_przeciwnika = CZARNY;
	else
		kolor_przeciwnika = BIALY;

	Gracz gracz_symulujacy(KOMPUTER, Kolor, &Symulowana_Plansza);
	Gracz przeciwnik(KOMPUTER, kolor_przeciwnika, &Symulowana_Plansza);

	gracz_symulujacy.Stworz_Liste_Ruchow();
	//Zobaczenie ile bedzie bic.
	int punkty_za_bicia = 0;
	if (gracz_symulujacy.Czy_Ruchy_To_Bicia)
			punkty_za_bicia = 10; //dla kazdego bicia i nie wazne ile ich jest dotajesz 10 pkt 
	//nie wazne czy damka czy zwykly

	punkty += punkty_za_bicia;
	Symulowana_Plansza.Czarne_Krazki = Plansza_gry->Czarne_Krazki;
	Symulowana_Plansza.Biale_Krazki = Plansza_gry->Biale_Krazki;

	przeciwnik.Stworz_Liste_Ruchow();
	int punkty_za_strate = 0;
	if (przeciwnik.Czy_Ruchy_To_Bicia) 
			punkty_za_strate = -40;
	punkty += punkty_za_strate;
	return punkty;
}

