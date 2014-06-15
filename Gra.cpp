#include "Gra.hpp"
#include "Gracz.hpp"
#include "Typy.hpp"
#include <time.h>
#include <iostream>

/*! \file */

/*! 
* \brief Gra
* 	
* Funkcje zwiazane z klasa Gra.	
* 	
*/

using namespace std;
/*destruktor*/
Gra::~Gra() {
}
/*!
* \brief Funkcja Wyswietl_Ekran_Koncowy.
*
* Wyswietla podsumwanie gry.
* Informacja o zakonczeniu gry i jej rezutacie
* Komunikacja z graczem czlowiekiem
* 
*/
void Gra::Wyswietl_Ekran_Koncowy(bool remis) {

	if (remis)
		cout << "Remis i ciesz sie. Tym razem mi sie nie udalo~KOMPUTER"<<endl;
	else if ((Bialy->Typ_Gracza == CZLOWIEK && plansza->Biale_Krazki.empty()
			&& Czarny->Typ_Gracza == KOMPUTER)
			|| (Czarny->Typ_Gracza == CZLOWIEK
					&& plansza->Czarne_Krazki.empty()
					&& Bialy->Typ_Gracza == KOMPUTER))
		cout<<"Jest mi bardzo przykro, ale Cie pokonalem~ KOMPUTER"<<endl;
	else
		cout<< "Tym razem Ci sie udalo. Jednorazowy fart~KOMPUTER"<<endl;
	system("PAUSE");
}

/*!
* \brief Rozgrywka.
*
* Zawiera gre, komunikacje z CZLOWIEKIEM
* Pyta o wspolrzedne
* GRA.
* 
*/
	void Gra::Rozgrywka() {
		//srand(time(NULL));

		bool remis = false;

		while (!Czy_Koniec_Gry() && !remis) {
			plansza->Zaktualizuj();
			Czy_Wykonano_Ruch = false;
			Aktualny_Gracz->Stworz_Liste_Ruchow();
			if (!Aktualny_Gracz->Lista_Ruchow.empty()) { //gdy nie jest pusta czyli nie ma remisu
				if (Aktualny_Gracz->Typ_Gracza == KOMPUTER) { //czy gracz jest kompem
					pair<Krazek, Punkt> Ruch = Aktualny_Gracz->Wybierz_Ruch();
					Aktualny_Gracz->Wykonaj_Ruch(Ruch);
					while (Aktualny_Gracz->Czy_Ruchy_To_Bicia) {
						Krazek krazek_bijacy = Ruch.first;
						krazek_bijacy.x() = Ruch.second.x;
						krazek_bijacy.y() = Ruch.second.y;
						Aktualny_Gracz->Stworz_Liste_Bic(krazek_bijacy); //gdy zrobimy bicie to sprawdza czy jest kolejne bicie dla tylko dla tego bicia.
						if (!Aktualny_Gracz->Lista_Ruchow.empty()) {
							Ruch = Aktualny_Gracz->Wybierz_Ruch();
							Aktualny_Gracz->Wykonaj_Ruch(Ruch);
						}
					}
				} else //teraz czlowieka ruchy.
					while (!Czy_Wykonano_Ruch) {
					int x1,y1,x2,y2;
					bool Jest_Krazek=false;
					Krazek* pomocniczy;
					while(!Jest_Krazek){
					cout <<"Ktory krazek chcesz przesunac? "<<endl;
					cin >> x1 >> y1;
					if(!plansza->Czy_Jest(Punkt(x1,y1)))
						cout<<"Nie ma tu krazka!"<<endl;
					else{
					plansza->Wez_Krazek(Punkt(x1,y1),&pomocniczy);
					if(pomocniczy->Kolor == Aktualny_Gracz->Kolor)
						Jest_Krazek=true;
					else
						cout<<"To nie twój krazek!"<<endl;
					}
					}
					cout << "Na jakie pole chcesz go przesunac? "<<endl;
					cin >> x2 >> y2;
					pair<Krazek, Punkt> Ruch = pair<Krazek, Punkt> (*pomocniczy,Punkt(x2,y2));
					if(Aktualny_Gracz->Czy_Zostal_Wybrany_Poprawny_Ruch(Ruch))
					{
						Aktualny_Gracz->Wykonaj_Ruch(Ruch);
						Czy_Wykonano_Ruch=true;
					}
					else
						cout<< "NIE MASZ PRAWA SIE TAK RUSZYC!"<<endl;
					};


				if (Aktualny_Gracz == Bialy)
					Aktualny_Gracz = Czarny;
				else
					Aktualny_Gracz = Bialy;
			} else
				remis = true;
		}
		Wyswietl_Ekran_Koncowy(remis);
	}

