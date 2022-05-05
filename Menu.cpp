#include "Menu.h"

void CMenu::Afficher() const
{
	// Problème d'écriture, impossible d'ecrire du texte
	//GetLibGraph2()->setFont(CString{ "consolas" }, 20.0f, font_styles::FontStyleRegular);
	//GetLibGraph2()->drawString(CString{ "Menu :" }, CPoint{ 750, 500 });
	GetLibGraph2()->drawEllipse(CRectangle{ CPoint{750,500}, CSize{50,50} });
}
