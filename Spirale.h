#pragma once
#include "Graphique.h"


class CSpirale :
    public CGraphique
{
private:
    std::vector<CPoint> m_vCpointGraph;

public:

    void Afficher() const override;
    void CreateSpirale(const std::vector<float>& sommeMoyStation);
};

