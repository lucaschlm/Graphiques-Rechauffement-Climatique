#pragma once
#include "Graphique.h"

class CClairFonce :
    public CGraphique
{
private:
    std::vector<float> m_data;
    //Tableau contenant les couleurs de la représentation (du plus chaud au plus froid)
    std::vector<ARGB> m_colors{ MakeARGB(255, 3, 4, 94), MakeARGB(255, 2, 62, 138), MakeARGB(255, 0, 180, 216), MakeARGB(255, 173, 232, 244),
        MakeARGB(255, 249, 237, 204), MakeARGB(255, 230, 96, 99), MakeARGB(255, 208, 34, 36), MakeARGB(255, 156, 25, 27) };
    std::vector<float> m_intervals;
    float m_rectangleWidth;
    float m_rectangleHeight;
    float m_widthMargin;
    size_t m_colorNb;

public:

    void Afficher() const override;
    void CreateClairFonce(const std::vector<float>& data, size_t colorNb);
};

