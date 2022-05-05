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

    //R�cup�ration de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fen�tre graphique avec une taille par d�faut
    //libgraph->show();
    evt e;  //Ev�nement LibGraph 2

    //Boucle principale d'�v�nements
    //while (libgraph->waitForEvent(e))
    //{
    //    switch (e.type)  //En fonction du type d'�v�nement
    //    {
    //    case evt_type::evtKeyDown:  //Enfoncement d'une touche
    //        switch (e.vkKeyCode)
    //        {
    //        case 'C':
    //            displayClairFonce(sommeMoyStation);
    //            break;
    //        case 'S':
    //            displaySpirale(sommeMoyStation);
    //            break;
    //        case 'R':
    //            displayRaieDeCouleurs(sommeMoyStation);
    //            break;
    //        case 0x1B:
    //            ReleaseLibGraph2();
    //            break;
    //        case 0x70:
    //            //help();
    //            break;
    //        }
    //    }
    //}

    //Lib�ration de l'objet principal de LibGraph 2

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