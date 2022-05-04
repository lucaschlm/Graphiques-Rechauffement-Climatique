#include <iostream> // std::cout
#include "SAE_Datas_Heat.h"
#include "Traitement.h"



int main()
{
	SAE_Datas_Heat myStations;
	std::cout << myStations.nbMonths() << "\n";
	//ListeStation lB = myStations.getListeStation();
	
	return 0;
}

