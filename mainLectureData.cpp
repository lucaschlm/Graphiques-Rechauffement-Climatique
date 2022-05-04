#include <Windows.h>
#include <tchar.h>
#include "incLibGraph2.h"
#include "SAE_Datas_Heat.h"
#include "Traitement.h"
#include <cmath>
#include <iostream>
#include "fonctionsLibgraph.h"
using namespace LibGraph2;

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    SAE_Datas_Heat myStations;
    std::vector<float> sommeMoyStation = somme_Moy_Station(myStations.getStationTmoy(), myStations.nbMonths());

    displayClairFonce(sommeMoyStation);

    displaySpirale(sommeMoyStation);

    displayRaieDeCouleurs(sommeMoyStation);

    return 0;
}