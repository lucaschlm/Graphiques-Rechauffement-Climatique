#pragma once
#include "Traitement.h"
#include "incLibGraph2.h"
#include "SAE_Datas_Heat.h"

const float pi = 3.14159265358979323846;
using namespace LibGraph2;

class CGraphique
{

public:
	virtual void Afficher() const = 0;
};

