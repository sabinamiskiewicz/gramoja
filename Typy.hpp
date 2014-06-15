#ifndef TYPY_HPP_
#define TYPY_HPP_

/*! \file */

/*! 
* \brief Punkt
* 	
* Modol zawiera klase Punkt	
* Ktory okreslaja wspolzedne x i y.	
*/
typedef enum {BIALY,CZARNY} _Kolor;

//deklaracja koloru
//bialy o
//czarny x
class Punkt {
public:
	int x;
	int y;
	Punkt(int _x,int _y) {x=_x;y=_y;};
	Punkt() {
	};
};

#endif
