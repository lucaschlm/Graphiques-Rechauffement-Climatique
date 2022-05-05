#pragma once
#include "Graphique.h"

class CRaieCouleurs :
    public CGraphique
{
private:
    std::vector<float> m_data;
    std::vector<float> m_tempPerYear;
    //Tableau contenant les couleurs de la représentation (du plus chaud au plus froid)
    std::vector<ARGB> m_colors{ MakeARGB(255, 3, 4, 94), MakeARGB(255, 2, 62, 138), MakeARGB(255, 0, 180, 216), MakeARGB(255, 173, 232, 244),
        MakeARGB(255, 249, 237, 204), MakeARGB(255, 230, 96, 99), MakeARGB(255, 208, 34, 36), MakeARGB(255, 156, 25, 27) };
    std::vector<float> m_intervals;
    float m_rectangleWidth;
    float m_rectangleHeight;

public:

    void Afficher() const override;
    void CreateRaieCouleurs(const std::vector<float>& data);
};

