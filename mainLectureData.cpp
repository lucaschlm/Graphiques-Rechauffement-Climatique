#include <Windows.h>
#include <tchar.h>
#include "incLibGraph2.h"
#include "SAE_Datas_Heat.h"
#include "Traitement.h"
#include <cmath>
#include <iostream>
using namespace LibGraph2;

const float pi = 3.14159265358979323846;

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
    libgraph->show(CSize{ 1000, 1000 });
    evt e;  //Evénement LibGraph 2

    SAE_Datas_Heat myStations;
    std::vector<float> sommeMoyStation = somme_Moy_Station(myStations.getStationTmoy(), myStations.nbMonths());

    std::vector<CPoint> vCpointGraph; // Vecteur contenant tous les points calculer avec les formules
    size_t cptAnnee = 1; // Compteur pour compter le nombre d'annee
    float coef = 500.0f; // Coefficient pour centrer le graphique dans la fenetre de 1000x1000
    size_t cptColor10 = 15; // Compteur pour le changement de couleur tous les 10 ans
    
    for (size_t i = 13; i < sommeMoyStation.size() + 1; i++) { // On parcours tous les mois
        float T = ((sommeMoyStation[i - 1] - sommeMoyStation[i - 1 - (12 * cptAnnee)]) + 5) * 50;
        switch (i - (12 * cptAnnee)) // Switch pour savoir le mois en cours (janvier, février, ...)
        {
        case 1: // Janvier
            vCpointGraph.push_back(CPoint{ coef, T + coef });
            break;
        case 2: // Fevrier
            vCpointGraph.push_back(CPoint{ 0.5f * T + coef, ((pi / 2.0f) * 0.5f * T) + coef });
            break;
        case 3: // Mars
            vCpointGraph.push_back(CPoint{ ((std::sqrt(3.0f) / 2.0f) * T) + coef, ((pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T) + coef });
            break;
        case 4: // Avril
            vCpointGraph.push_back(CPoint{ T + coef, coef });
            break;
        case 5: // Mai
            vCpointGraph.push_back(CPoint{ ((std::sqrt(3.0f) / 2.0f) * T) + coef, -((pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T) + coef });
            break;
        case 6: // Juin
            vCpointGraph.push_back(CPoint{ (0.5f * T) + coef, -((pi / 2.0f) * 0.5f * T) + coef });
            break;
        case 7: // Juillet
            vCpointGraph.push_back(CPoint{ coef, -T + coef });
            break;
        case 8: // Aout
            vCpointGraph.push_back(CPoint{ (-0.5f * T) + coef, ((pi / 2.0f) * -0.5f * T) + coef });
            break;
        case 9: // Septembre
            vCpointGraph.push_back(CPoint{ (-(std::sqrt(3.0f) / 2.0f) * T) + coef, ((pi / 6.0f) * -(std::sqrt(3.0f) / 2.0f) * T) + coef });
            break;
        case 10: // Octobre
            vCpointGraph.push_back(CPoint{ -T + coef, coef });
            break;
        case 11: // Novembre
            vCpointGraph.push_back(CPoint{ (-(std::sqrt(3.0f) / 2.0f) * T) + coef, (pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T + coef });
            break;
        case 12: // Decembre
            vCpointGraph.push_back(CPoint{ (-0.5f * T) + coef, -((pi / 2.0f) * -0.5f * T) + coef });
            break;

        }
        if (i % 12 == 0) { // Incrementation du compteur d'annee tous les 12 mois
            cptAnnee++;
        }
    }

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();
            //Utiliser ici les fonctions de dessins

            for (size_t i = 1; i < vCpointGraph.size(); i++) {
                libgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
                // Affichage des points pour tracer chaque traits
                libgraph->drawEllipse(CRectangle{ vCpointGraph[i-1], CSize{ 5, 5 } });

                if (i%12 == 0) { // Changement des couleurs tous les 12 mois
                    cptColor10 += 8;
                }
                // Changement de la couleur
                libgraph->setPen(MakeARGB(255, 255, cptColor10, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
                // Affichage des traits entre les points
                libgraph->drawLine(vCpointGraph[i-1], vCpointGraph[i]);
            }

            libgraph->endPaint();
            break;

        }
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}