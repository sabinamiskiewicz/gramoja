#include "Plansza.hpp"
#include "Gracz.hpp"
#include "Typy.hpp"
#include <Windows.h>
#include <iostream>
/*! \file */

/*! 
* \brief Plansza
* 	
* Funkcje zwiazane z klasa Plansza.	
* 	
*/
using namespace std;

//KONSTRUktor kopiujacy do symuliowania planszy
//przpisuje te krazki z planszy do nowej plnaszy
Plansza::Plansza(Plansza& Plansza_gry)
{
	Czarne_Krazki = Plansza_gry.Czarne_Krazki;
	Biale_Krazki = Plansza_gry.Biale_Krazki;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Pola_Gry[i][j] =
					Plansza_gry.Pola_Gry[i][j];
}
//nieparzyte pola sa biale a parzyste czarne
//na czarnych w 3 pierwszych i ostatniech dodaje pionki
Plansza::Plansza() {
	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++) {
			if ((i + j) % 2)
				Pola_Gry[i][j] = BIALY;
			else {
				Pola_Gry[i][j] = CZARNY;
				if (i > 4)
					Dodaj_Krazek(Krazek(Punkt(j, i), BIALY));
				if (i < 3)
					Dodaj_Krazek(Krazek(Punkt(j, i), CZARNY));

			}
		}
}
//auto ogarnia jaki ma bym typ na podstwie podstawianych zmiennych
//begin zwraca iterator do poczatku vektoru krazkow
bool Plansza::Dodaj_Krazek(Krazek krazek) {
	std::vector<Krazek>* Krazki = &Czarne_Krazki;
	if (krazek.Kolor == BIALY)
		Krazki = &Biale_Krazki;

	for (auto it = Krazki->begin(); it != Krazki->end(); it++)
		if (it->x() == krazek.x() && it->y() == krazek.y())
			return false;
	Krazki->push_back(krazek);
	return true;
}
bool Plansza::Usun_Krazek(Krazek krazek) {
	std::vector<Krazek>* Krazki = &Czarne_Krazki;
	if (krazek.Kolor == BIALY)
		Krazki = &Biale_Krazki;
	for (auto it = Krazki->begin(); it != Krazki->end(); it++)
		if (it->x() == krazek.x() && it->y() == krazek.y()) {
			*it = Krazki->back();
			Krazki->pop_back();
			return true; //usuwa ostatni krazek po skopiowaniu go na miejsce inne
		}
	return false;
}
void Plansza::Zaktualizuj() {
	system("cls"); //czyszczenie terminalu
	cout<<endl<<endl<<endl<<endl<<endl<<"  ";
	for(int i =0;i<8;i++)
		cout<<i<<" "; //dodajemy numeracje kolumn GORA
	cout<<endl<<"  ";
	for(int i =0;i<8;i++)
		cout<<"--"; //krawedx pozioma
	cout<<endl<<0<<'|'; //rozdzielenie pola pierwszego 
	for(int j=0;j<64;j++)
	{
	bool Narysowano=false;  //czy jest krazek czy spacja
	for (auto it = Czarne_Krazki.begin(); it != Czarne_Krazki.end(); it++) {
		if(it->x()== j % 8 && it->y()== j/8)
		{
			Narysowano = true;
			if(it->Typ==Krazek::ZWYKLY)
			 cout<<"x";
			if(it->Typ==Krazek::DAMKA)
			 cout<<"X";
		}

	}
	for (auto it = Biale_Krazki.begin(); it != Biale_Krazki.end(); it++) {
		if(it->x()== j % 8 && it->y()== j/8)
		{
			Narysowano = true;
			if(it->Typ==Krazek::ZWYKLY)
			 cout<<"o";
			if(it->Typ==Krazek::DAMKA)
			 cout<<"O";
		}

	}
	if(!Narysowano) //nie ma krazka na tym polu
		cout<<" ";
	cout<<"|";
	if(j%8 ==7){
		cout<<endl<<"  "; //gdy jest w koncu lini idzie do kolejnej
		for(int i =0;i<8;i++)
			cout<<"--"; //znowu oddziela linijki
		if(j/8 != 7) //gdy koniec plaszy to nie daje nastepnego wiesza
		cout<<endl<<j/8 +1<<'|'; //koniec linii
	}
	}
	cout<<endl<<endl;
}

bool Plansza::Przenies_Krazek(Krazek krazek, Punkt Do) {
	bool Czy_Udalo_Sie = true;
	Czy_Udalo_Sie = Usun_Krazek(krazek);
	if (Czy_Udalo_Sie) {
		Krazek nowy(Do, krazek.Kolor);
		nowy.Typ = krazek.Typ;
		Czy_Udalo_Sie = Dodaj_Krazek(nowy);
	}
	return Czy_Udalo_Sie;
}
//krazek - adres wskxnika. agr- adres wskaznika. 
//wskaznikowi przypisuje adres krazka ktory jest na polu P
//sprawdzamy jaki krazek jest na polu P
//NULL nie ma kra¿ka tam
bool Plansza::Wez_Krazek(Punkt P, Krazek** krazek) {
	for (auto it = Czarne_Krazki.begin(); it != Czarne_Krazki.end(); it++)
		if (it->x() == P.x && it->y() == P.y) {
			*krazek = &(*it);
			return true;
		}
	for (auto it = Biale_Krazki.begin(); it != Biale_Krazki.end(); it++)
		if (it->x() == P.x && it->y() == P.y) {
			*krazek = &(*it);
			return true;
		}
	*krazek = NULL;
	return false;

}
//sprawdza czy jest krazek na polu P, ale ma gdzies jaki on jest
bool Plansza::Czy_Jest(Punkt P) {
	for (auto it = Czarne_Krazki.begin(); it != Czarne_Krazki.end(); it++)
		if (it->x() == P.x && it->y() == P.y)
			return true;
	for (auto it = Biale_Krazki.begin(); it != Biale_Krazki.end(); it++)
		if (it->x() == P.x && it->y() == P.y)
			return true;
	return false;
}
