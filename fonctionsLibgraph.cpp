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
 */
displayType displayClairFonce(const std::vector<float>& data, size_t colorNb)
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
    libgraph->show(CSize(1500, 700));
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
            {
            //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();

            //On affiche le nom du graphique en haut à gauche
            libgraph->setFont(CString("Consolas"), 12, font_styles::FontStyleRegular);
            libgraph->drawString(CString("Clair-Fonce"), CPoint(0, 0));

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
        case evt_type::evtKeyDown:
            switch (e.vkKeyCode)
            {
            case 'S':
                return displayType::Spirale;
                break;
            case 'R':
                return displayType::Raie;
                break;
            //case 0x1B:
            //    ReleaseLibGraph2();
            //    break;
            case 0x70:
                help();
                break;
            }
        }
    }
    return displayType::None;
}

/*!
 *  \brief  Fonction permettant d'afficher une représentation en spirale des températures
 *  \param  sommeMoyStation - tableau contenant les températures
 */
displayType displaySpirale(const std::vector<float>& sommeMoyStation)
{
    
    //Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fenêtre graphique avec une taille par défaut
    libgraph->show(CSize{ 1000, 1000 });
    evt e;  //Evénement LibGraph 2
    std::vector<CPoint> vCpointGraph; // Vecteur contenant tous les points calculer avec les formules
    size_t cptAnnee = 1; // Compteur pour compter le nombre d'annee
    float coef = 500.0f; // Coefficient pour centrer le graphique dans la fenetre de 1000x1000
    size_t cptColor10 = 15; // Compteur pour le changement de couleur tous les 10 ans

    for (size_t i = 13; i < sommeMoyStation.size() + 1; i++) { // On parcours tous les mois
        float T = ((sommeMoyStation[i - 1] - sommeMoyStation[i - 1 - (12 * cptAnnee)]) + 5) * 48;
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
            
            //libgraph->drawString("Graphique Spirale", CPoint(20, 20));
            //Utiliser ici les fonctions de dessins

            for (size_t i = 1; i < vCpointGraph.size(); i++) {

                libgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
                // Affichage des points pour tracer chaque traits
                libgraph->drawEllipse(CRectangle{ vCpointGraph[i - 1], CSize{ 5, 5 } });

                if (i % 12 == 0) { // Changement des couleurs tous les 12 mois
                    cptColor10 += 8;
                }
                // Changement de la couleur
                libgraph->setPen(MakeARGB(255, 255, cptColor10, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
                // Affichage des traits entre les points
                libgraph->drawLine(vCpointGraph[i - 1], vCpointGraph[i]);
            }

            libgraph->endPaint();
            break;
        case evt_type::evtKeyDown:
            switch (e.vkKeyCode)
            {
            case 'C':
                return displayType::ClairFonce;
                break;
            case 'R':
                return displayType::Raie;                
                break;
            //case 0x1B:
            //    ReleaseLibGraph2();
            //    break;
            case 0x70:
                //help();
                break;
            }
        }
    }

    return displayType::None;
}

displayType displayRaieDeCouleurs(const std::vector<float>& data)
{
    //Tableau contenant les couleurs de la représentation (du plus chaud au plus froid)
    std::array<ARGB, 8> colors{ MakeARGB(255, 3, 4, 94), MakeARGB(255, 2, 62, 138), MakeARGB(255, 0, 180, 216), MakeARGB(255, 173, 232, 244),
    MakeARGB(255, 249, 237, 204), MakeARGB(255, 230, 96, 99), MakeARGB(255, 208, 34, 36), MakeARGB(255, 156, 25, 27) };

    //On créé un nouveau tableau contenant les températures moyennes par années
    std::vector<float> tempPerYear(data.size() / 12);
    float moy = 0;
    size_t cpt = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (i % 12 == 0 && i != 0)
        {
            moy /= 12.f;
            tempPerYear[cpt] = moy;
            cpt++;
        }
        moy += data[i];
    }
    //ne pas oublier la dernière valeur
    moy /= 12.f;
    tempPerYear[cpt] = moy;

    //On calcule les intervalles de températures
    float maxTemp = *std::max_element(tempPerYear.begin(), tempPerYear.end());
    float minTemp = *std::min_element(tempPerYear.begin(), tempPerYear.end());
    float deltaTemp = maxTemp - (minTemp - 1);
    float interval = deltaTemp / 8.f;

    //Tableau contenant les intervals de valeurs (0-1, 1-2, ..., 6-7, 7+)
    std::vector<float> intervals;
    intervals.resize(8);
    for (size_t i = 0; i < 8; i++)
        intervals[i] = minTemp + interval * i;


    //Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fenêtre graphique avec une taille par défaut
    libgraph->show(CSize(700, 200));
    evt e;  //Evénement LibGraph 2

    //On récupère la taille de la fenêtre
    float width = libgraph->getSize().m_fWidth;
    float height = libgraph->getSize().m_fHeight;

    float heightMargin = libgraph->getSize().m_fHeight * (10.f / 100.f);

    //On calcule la largeur d'un rectangle
    float rectangleWidth = width / tempPerYear.size();
    //Puis on calcul la hauteur (un rectangle par an)
    float rectangleHeight = (height/* - heightMargin*/);

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
        {
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();

            //On affiche le nom du graphique en haut à gauche
            //libgraph->setFont(CString("Consolas"), 12, font_styles::FontStyleRegular);
            //libgraph->drawString(CString("Clair-Fonce"), CPoint(0, 0));

            size_t colNb = 0; //numero de colonne

            //On parcourt toutes les valeurs
            for (size_t i = 0; i < tempPerYear.size(); i++)
            {
                ARGB color = colors[7];
                //On cherche la couleur de la valeur
                for (size_t j = 0; j < 8; j++)
                {
                    if (tempPerYear[i] <= intervals[j])
                    {
                        color = colors[j];
                        break;
                    }
                }
                libgraph->setSolidBrush(color);
                CRectangle rectangle(CPoint(rectangleWidth * colNb, 0), CSize(rectangleWidth, rectangleHeight));
                libgraph->drawRectangle(rectangle);
                colNb++;
            }

            libgraph->endPaint();
            break;
        }
        case evt_type::evtKeyDown:
            switch (e.vkKeyCode)
            {
            case 'S':
                return displayType::Spirale;
                break;
            case 'C':
                return displayType::ClairFonce;
                break;
            //case 0x1B:
            //    ReleaseLibGraph2();
            //    break;
            case 0x70:
                //help();
                break;
            }
        }
    }

    return displayType::None;
}

void help()
{
    GetLibGraph2()->guiMessageBox("Aide", "Commandes claviers :\n"
        "C : Afficher la représentation Clair-Foncé\n"
        "S : Afficher la représentation en spirale\n"
        "R : Afficher la représentation en raie de couleurs\n"
        "ESC : Fermer le logiciel proprement\n"
        "F1 : Affiche cette aide", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
}
