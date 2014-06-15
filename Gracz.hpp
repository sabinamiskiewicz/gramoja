#ifndef GRACZ_HPP_
#define GRACZ_HPP_

#include "Plansza.hpp"
#include "Typy.hpp"
#include <vector>
#include <utility>

/*! \file */

/*! 
* \brief Gracz
* 	
* Modol zawiera klase Gracz.
* Zdefiniowany zostal TYP gracza.
* Na komputer i czlowieka.
* 	
*/

typedef enum {KOMPUTER,CZLOWIEK} _Typ_Gracza;

class Gracz {
public:
	_Kolor Kolor;
	_Typ_Gracza Typ_Gracza;
	Plansza* Plansza_gry;
	bool Czy_Ruchy_To_Bicia;
	std::vector<std::vector<std::pair<Krazek,Punkt> > >Lista_Ruchow;
	Gracz(_Typ_Gracza,_Kolor,Plansza* plansza);
	std::pair<Krazek,Punkt>  Wybierz_Ruch();
	bool Czy_Jest_Bicie(Punkt,Punkt,Krazek);
	void Stworz_Liste_Bic(Krazek);
	int Punkty_Za_Krazki();
	int Zasymuluj_Ruch(std::pair<Krazek,Punkt>);
	int Punkty();
	void Ulepsz_Ruch(){}
	void Stworz_Liste_Ruchow();
	void Wykonaj_Ruch(std::pair<Krazek,Punkt>);
	bool Czy_Zostal_Wybrany_Poprawny_Ruch(std::pair<Krazek,Punkt>);
	void Wyswietl_Liste_Ruchow();
	void Wyczysc_Liste_Ruchow();
	virtual ~Gracz();
};

#endif
