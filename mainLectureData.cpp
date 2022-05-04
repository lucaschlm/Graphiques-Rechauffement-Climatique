#include <Windows.h>
#include <tchar.h>
#include "incLibGraph2.h"
#include "SAE_Datas_Heat.h"
#include "Traitement.h"
#include <cmath>
#include <iostream>
using namespace LibGraph2;

const double pi = 3.14159265358979323846;

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fenêtre graphique avec une taille par défaut
    libgraph->show();
    libgraph->showConsole();
    evt e;  //Evénement LibGraph 2

    SAE_Datas_Heat myStations;
    std::vector<int> IDStation = myStations.getIdStation();
    std::vector<float> sommeMoyStation = somme_Moy_Station(myStations.getStationTmoy(), myStations.nbMonths());

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();
            //Utiliser ici les fonctions de dessins
            size_t cptAnnee = 0; // Compteur pour compter le nombre d'annee
            CPoint pointMoisPrecedent{ 0.0f, sommeMoyStation[0] };
            CPoint pointMoisEnCours{ 0.0f, sommeMoyStation[0] };
            for (size_t i = 1; i < sommeMoyStation.size() + 1; i++) { // On parcours tous les mois
                switch (i - (12*cptAnnee)) // Switch pour savoir le mois en cours (janvier, février, ...)
                {
                case 1: // Janvier
                    pointMoisEnCours = CPoint{ 0.0f, sommeMoyStation[i - 1] };
                    break;
                case 2: // Fevrier
                    pointMoisEnCours = CPoint{ (1/2)*sommeMoyStation[i - 1], (pi/2)*(std::sqrt(3)/2)*sommeMoyStation[i - 1] };

                }
                if (i % 12 == 0) { // Incrementation du compteur d'annee tous les 12 mois
                    cptAnnee++;
                }
                pointMoisPrecedent = pointMoisEnCours;
            }
            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfoncée
            {
            case 'A':
                break;
            }
            break;

        case evt_type::evtMouseMove:  //Déplacement de la souris
          //Position de la souris dans les variables e.x et e.y
            break;
        }
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}