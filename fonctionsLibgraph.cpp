#include "fonctionsLibgraph.h"
#include "incLibGraph2.h"
#include <array>
#include <vector>
#include <algorithm>
using namespace LibGraph2;

/*!
 *  \brief  Fonction permettant d'afficher une repr�sentation Clair-Fonc� des temp�ratures
 *  \param  data    - tableau contenant les temp�ratures
 *  \param  colorNb - Le nombre de couleurs diff�rentes sur la repr�sentation (max=8)
 *  \author Lucas Chalmandrier
 */
void displayClairFonce(const std::vector<float>& data, size_t colorNb)
{
    //Tableau contenant les couleurs de la repr�sentation (du plus chaud au plus froid)
    std::array<ARGB, 8> colors{ MakeARGB(255, 156, 25, 27), MakeARGB(255, 208, 34, 36), MakeARGB(255, 230, 96, 99), MakeARGB(255, 249, 237, 204),
    MakeARGB(255, 173, 232, 244), MakeARGB(255, 0, 180, 216), MakeARGB(255, 2, 62, 138), MakeARGB(255, 3, 4, 94) };

    //On calcule les intervalles de temp�ratures
    float maxTemp = *std::max_element(data.begin(), data.end());
    float minTemp = *std::min_element(data.begin(), data.end());
    float deltaTemp = maxTemp - (minTemp - 1);
    float interval = deltaTemp / static_cast<float>(colorNb);
    std::vector<float> intervals;
    intervals.resize(colorNb);
    for (size_t i = 0; i < colorNb; i++)
        intervals[i] = minTemp + interval * (i + 1);
/*
    //R�cup�ration de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fen�tre graphique avec une taille par d�faut
    libgraph->show();
    evt e;  //Ev�nement LibGraph 2

    //Boucle principale d'�v�nements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'�v�nement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser �ventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();
            //Utiliser ici les fonctions de dessins
            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfonc�e
            {
            case 'A':
                break;
            }
            break;

        case evt_type::evtMouseMove:  //D�placement de la souris
          //Position de la souris dans les variables e.x et e.y
            break;
        }
    }

    //Lib�ration de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
*/
}
