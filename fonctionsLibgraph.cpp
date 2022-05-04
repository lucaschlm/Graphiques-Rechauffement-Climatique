#include "fonctionsLibgraph.h"
#include "incLibGraph2.h"
#include <array>
#include <vector>
#include <algorithm>
using namespace LibGraph2;

/*!
 *  \brief  Fonction permettant d'afficher une représentation Clair-Foncé des températures
 *  \param  data    - tableau contenant les températures
 *  \param  colorNb - Le nombre de couleurs différentes sur la représentation (max=8)
 *  \author Lucas Chalmandrier
 */
void displayClairFonce(const std::vector<float>& data, size_t colorNb)
{
    //Tableau contenant les couleurs de la représentation (du plus chaud au plus froid)
    std::array<ARGB, 8> colors{ MakeARGB(255, 3, 4, 94), MakeARGB(255, 2, 62, 138), MakeARGB(255, 0, 180, 216), MakeARGB(255, 173, 232, 244),
    MakeARGB(255, 249, 237, 204), MakeARGB(255, 230, 96, 99), MakeARGB(255, 208, 34, 36), MakeARGB(255, 156, 25, 27) };
    //On calcule les intervalles de températures
    float maxTemp = *std::max_element(data.begin(), data.end());
    float minTemp = *std::min_element(data.begin(), data.end());
    float deltaTemp = maxTemp - (minTemp - 1);
    float interval = deltaTemp / static_cast<float>(colorNb);
    //Tableau contenant les intervals de valeurs (0-1, 1-2, ..., 6-7, 7+)
    std::vector<float> intervals;
    intervals.resize(colorNb);
    for (size_t i = 0; i < colorNb; i++)
        intervals[i] = minTemp + interval * i;


    //Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fenêtre graphique avec une taille par défaut
    libgraph->show();
    evt e;  //Evénement LibGraph 2

    //On récupère la taille de la fenêtre
    float width = libgraph->getSize().m_fWidth;
    float height = libgraph->getSize().m_fHeight;

    //On calcule une taille pour la marge pour laisser de la place à la légende
    float widthMargin = libgraph->getSize().m_fWidth * (10.f / 100.f);
    float heightMargin = libgraph->getSize().m_fHeight * (30.f / 100.f);

    //On calcule la largeur d'un rectangle (12 mois sur la largeur)
    float rectangleWidth = (width - widthMargin) / 12;
    //Puis on calcul la hauteur (un rectangle par an)
    float rectangleHeight = (height - heightMargin) / (data.size() / 12);

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();

            //On affiche le nom du graphique en haut à gauche
            //libgraph->setFont(CString("Consolas"), 12, font_styles::FontStyleRegular);
            //libgraph->drawString(CString("Clair-Fonce"), CPoint(0, 0));

            size_t lineNb = 0; //numero de ligne
            size_t colNb = 0; //numero de colonne

            //On parcourt toutes les valeurs
            for (size_t i = 0; i < data.size(); i++)
            {
                if (i % 12 == 0 && i != 0) // Si on change d'année (12mois) on change de ligne
                {
                    lineNb++;
                    colNb = 0;
                }
                ARGB color = colors[colorNb - 1];
                //On cherche la couleur de la valeur
                for (size_t j = 0; j < colorNb; j++)
                {
                    if (data[i] <= intervals[j])
                    {
                        color = colors[j];
                        break;
                    }
                }
                libgraph->setSolidBrush(color);
                CRectangle rectangle(CPoint(colNb * rectangleWidth + widthMargin, lineNb * rectangleHeight), CSize(rectangleWidth, rectangleHeight));
                libgraph->drawRectangle(rectangle);
                colNb++;
            }

            libgraph->endPaint();
            break;
        }
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();

}
