#include "ClairFonce.h"

void CClairFonce::Afficher() const
{
    size_t lineNb = 0; //numero de ligne
    size_t colNb = 0; //numero de colonne

    //On parcourt toutes les valeurs
    for (size_t i = 0; i < m_data.size(); i++)
    {
        if (i % 12 == 0 && i != 0) // Si on change d'année (12mois) on change de ligne
        {
            lineNb++;
            colNb = 0;
        }

        ARGB color = m_colors[m_colorNb - 1];
        //On cherche la couleur de la valeur
        for (size_t j = 0; j < m_colorNb; j++)
        {
            if (m_data[i] <= m_intervals[j])
            {
                color = m_colors[j];
                break;
            }
        }
        GetLibGraph2()->setSolidBrush(color);
        CRectangle rectangle(CPoint(colNb * m_rectangleWidth + m_widthMargin, lineNb * m_rectangleHeight), CSize(m_rectangleWidth, m_rectangleHeight));
        GetLibGraph2()->drawRectangle(rectangle);
        colNb++;
    }
}

void CClairFonce::CreateClairFonce(const std::vector<float>& data, size_t colorNb)
{
    m_data = data;
    m_colorNb = colorNb;

    //On calcule les intervalles de températures
    float maxTemp = *std::max_element(m_data.begin(), m_data.end());
    float minTemp = *std::min_element(m_data.begin(), m_data.end());
    float deltaTemp = maxTemp - (minTemp - 1);
    float interval = deltaTemp / static_cast<float>(m_colorNb);


    //Tableau contenant les intervals de valeurs (0-1, 1-2, ..., 6-7, 7+)
    m_intervals.resize(m_colorNb);
    for (size_t i = 0; i < m_colorNb; i++)
        m_intervals[i] = minTemp + interval * i;

    //On récupère la taille de la fenêtre
    float width = GetLibGraph2()->getSize().m_fWidth;
    float height = GetLibGraph2()->getSize().m_fHeight;

    //On calcule une taille pour la marge pour laisser de la place à la légende
    m_widthMargin = GetLibGraph2()->getSize().m_fWidth * (10.f / 100.f);
    float heightMargin = GetLibGraph2()->getSize().m_fHeight * (30.f / 100.f);

    //On calcule la largeur d'un rectangle (12 mois sur la largeur)
    m_rectangleWidth = (width - m_widthMargin) / 12;
    //Puis on calcul la hauteur (un rectangle par an)
    m_rectangleHeight = (height - heightMargin) / (m_data.size() / 12);
}
