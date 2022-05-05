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

CAplication::CAplication()
{
    SAE_Datas_Heat myStations;
    auto sommeMoyStation = somme_Moy_Station(myStations.getStationTmoy(), myStations.nbMonths());

    CMenu menu;
    m_vpgListGraph.push_back(std::make_shared<CMenu>(menu));

    CClairFonce clairFonce;
    clairFonce.CreateClairFonce(sommeMoyStation, 8);
    m_vpgListGraph.push_back(std::make_shared<CClairFonce>(clairFonce));

    CSpirale spirale;
    spirale.CreateSpirale(sommeMoyStation);
    m_vpgListGraph.push_back(std::make_shared<CSpirale>(spirale));

    CRaieCouleurs raieCouleurs;
    raieCouleurs.CreateRaieCouleurs(sommeMoyStation);
    m_vpgListGraph.push_back(std::make_shared<CRaieCouleurs>(raieCouleurs));
}

void CAplication::AfficherFenetre(EFenetre Fenetre) const
{
    switch (Fenetre)
    {
    case EFenetre::FenetreMenu:
        m_vpgListGraph[0]->Afficher();
        break;
    case EFenetre::FenetreClairFonce:
        m_vpgListGraph[1]->Afficher();
        break;
    case EFenetre::FenetreSpirale:
        m_vpgListGraph[2]->Afficher();
        break;
    case EFenetre::FenetreRaieCouleurs:
        m_vpgListGraph[3]->Afficher();
        break;
    default:
        break;
    }
}
