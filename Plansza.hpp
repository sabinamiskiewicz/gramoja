#ifndef PLANSZA_HPP_
#define PLANSZA_HPP_

#include "Typy.hpp"
#include "Krazek.hpp"
#include <vector>
#include <utility>

/*! \file */

/*! 
* \brief Plansza
* 	
* Modol zawiera klase Plansza	
* 	
*/
class Plansza{
public:
	_Kolor Pola_Gry[8][8];
	bool Dodaj_Krazek(Krazek);
	std::vector<Krazek> Czarne_Krazki,Biale_Krazki;
	bool Przenies_Krazek(Krazek,Punkt Do);
	bool Usun_Krazek(Krazek);
	//sprawdzenie pola czy jest w plaszy
	bool Czy_Punkt_W_Planszy(Punkt P)
	{
		if(P.x >= 0 && P.x <8 && P.y >=0 && P.y<8 )
			return true;
		return false;
	}
	bool Wez_Krazek(Punkt P,Krazek**);
	void Zaktualizuj();
	bool Czy_Jest(Punkt P);
	Plansza(Plansza&);
	Plansza();
};


#endif
