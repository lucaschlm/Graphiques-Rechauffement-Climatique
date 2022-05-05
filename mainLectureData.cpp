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


    EFenetre FenetreEnCours = EFenetre::FenetreMenu;
    CAplication Aplication;

    //R�cup�ration de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fen�tre graphique avec une taille par d�faut
    libgraph->show(CSize{1500, 1000});
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

            Aplication.AfficherFenetre(FenetreEnCours);

            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfonc�e
            {
            case 'C':
                FenetreEnCours = EFenetre::FenetreClairFonce;
                libgraph->askForRefresh();
                break;
            case 'S':
                FenetreEnCours = EFenetre::FenetreSpirale;
                libgraph->askForRefresh();
                break;
            case 'R':
                FenetreEnCours = EFenetre::FenetreRaieCouleurs;
                libgraph->askForRefresh();
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

    return 0;
}