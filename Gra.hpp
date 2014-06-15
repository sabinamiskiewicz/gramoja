#ifndef GRA_HPP_
#define GRA_HPP_

#include "Gracz.hpp"
#include "Krazek.hpp"
#include "Plansza.hpp"
#include "Typy.hpp"
#include <time.h>

/*! \file */

/*! 
* \brief Gra
* 	
* Modol zawiera klase Gra.	
* 	
*/

class Gra {
public:
	Gracz *Bialy, *Czarny;
	Plansza* plansza;
	Gracz* Aktualny_Gracz;
	bool Czy_Wykonano_Ruch;
	int Punkty();
	void Poczekaj(int ms);
	void Wyswietl_Ekran_Koncowy(bool remis);
/*!
* \brief Funkcja Czy_Koniec_Gry.
*
* Sprawdzamy czy nastapil koniec gry.
* Poprzez sprawdzenie czy ktorys gracz zostal bez krazkow
* Na planszy.
* 
*/
	bool Czy_Koniec_Gry() {
		return (plansza->Biale_Krazki.empty()||plansza->Czarne_Krazki.empty());
	};
/*!
* \brief Funkcja Rozgrywka.
*
* Okreslamy plansze,
* Gracza1 jako bialego
* Gracza2 jako czarnego.
* I aktualnego gracza jako bialy (zaczyna)
* 
*/
	void Rozgrywka();
	Gra(Plansza* _plansza,Gracz* gracz1,Gracz* gracz2)
	{
		plansza= _plansza;
		Bialy=gracz1;
		Czarny=gracz2;
		Aktualny_Gracz=Bialy;
	};
	virtual ~Gra();
};

#endif
