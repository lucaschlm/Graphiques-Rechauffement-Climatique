#include "Traitement.h"

std::vector<float> somme_Moy_Station(const std::vector<std::vector<float>>& vStationTmoy, size_t nbMonth)
{
	std::vector<float> sommeMoyStation(nbMonth);
	for (size_t i = 0; i < nbMonth; i++) { // Boucle sur le nombre de mois
		for (size_t j = 0; j < vStationTmoy.size(); j++) { // Boucle sur le nombre de station
			sommeMoyStation[i] += vStationTmoy[j][i];
		}
		sommeMoyStation[i] /= vStationTmoy.size();
	}

	return sommeMoyStation;
}