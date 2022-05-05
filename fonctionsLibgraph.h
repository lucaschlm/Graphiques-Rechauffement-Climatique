#pragma once
#include "Spirale.h"
#include "ClairFonce.h"
#include "RaieCouleurs.h"
#include "Traitement.h"

#include <memory>
#include <vector>

enum class EFenetre
{
	FenetreMenu,
	FenetreClairFonce,
	FenetreSpirale,
	FenetreRaieCouleurs
};

class CAplication
{
private:
	std::vector<std::shared_ptr<CGraphique>> m_vpgListGraph;

public:
	CAplication();

	void AfficherFenetre(EFenetre Fenetre) const;

};