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

    displayType type = displayType::ClairFonce;

    while (type != displayType::None)
    {
        switch (type)
        {
        case displayType::ClairFonce:
            type = displayClairFonce(sommeMoyStation);
            break;
        case displayType::Spirale:
            type = displaySpirale(sommeMoyStation);
            break;
        case displayType::Raie:
            type = displayRaieDeCouleurs(sommeMoyStation);
            break;
        }
    }
    ReleaseLibGraph2();
    return 0;
}