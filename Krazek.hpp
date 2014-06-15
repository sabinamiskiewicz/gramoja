#ifndef KRAZEK_HPP_
#define KRAZEK_HPP_
#include "Typy.hpp"

/*! \file */

/*! 
* \brief Krazek.hpp
* 	
* Modol zawiera klase krazek.	
* 	
*/

class Krazek {
private:
	Punkt Polozenie;
public:
	enum	{
			ZWYKLY, DAMKA
			} 
	Typ;
	_Kolor Kolor;
/*!
* \brief Funkcja Awansuj.
*
* Gdy pionkiem dojdziemy do konca plaszny
* Wywolujemy ta funkcje alby zmienic pionek ZWYKLY
* Na DAMKA
* 
*/
	void Awansuj()	{
					Typ = DAMKA;
					};

/*!
* \brief Przeciazenie operatora ==
*
* Sprawdza po wspolzednych czy dwa krazki
* Sa takie same.
* Czyli czy maja jedno, wspolne polozenie, wspolrzedne.
* 
*/
	bool operator== (Krazek k) {
		if (x() == k.x() && y() == k.y())
			return true;
		return false;
	};
/*!
* \brief Zdefiniowanie istotnych cech krazka.
*
* Przypisanie polozenia pod punkt P oo wspolzednych (x,y).
* Nadanie krazkowi koloru. Bialy lub czarny.
* Nadanie typu krazkowi. Od poczatku gdy na ZWYKLY.
* 
*/
	Krazek(Punkt P, _Kolor kolor) {
		Polozenie = P;
		Kolor = kolor;
		Typ = ZWYKLY;
	};
/*!
* \brief Funkcja CzyDamka
*
* Sprawdza czy krazek jest DAMKA.
* Sprawdzajac jego Typ.
* 
*/
	bool CzyDamka() {
		return Typ == DAMKA;
	};
	//funcja zwraca referencje do x polozenia, bo jest prywatne. czyli mozna to zmienic bo to referencja
	int & x() {
		return Polozenie.x;
	};
	int &y() {
		return Polozenie.y;
	};
};

#endif
