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
    return 0;
}