#include "Plansza.hpp"
#include "Gracz.hpp"
#include "Gra.hpp"
#include <iostream>

using namespace std;
/*! \file */

/*! 
* \brief MAIN
* 	
* Funkcja glowna.	
* 	
*/

int main(int argc, char **argv)
{
Plansza plansza;
Gracz Pierwszy(KOMPUTER,BIALY,&plansza);
Gracz Drugi(CZLOWIEK,CZARNY,&plansza);
Gra gra(&plansza,&Pierwszy,&Drugi);
gra.Rozgrywka();
return 0;
}
