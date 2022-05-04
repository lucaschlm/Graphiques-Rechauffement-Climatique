#include <Windows.h>
#include <tchar.h>
#include "incLibGraph2.h"
using namespace LibGraph2;

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
    evt e;  //Evénement LibGraph 2

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
            libgraph->beginPaint();
            //Utiliser ici les fonctions de dessins
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