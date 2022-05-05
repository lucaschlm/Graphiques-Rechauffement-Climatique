#include "RaieCouleurs.h"

void CRaieCouleurs::Afficher() const
{
    size_t colNb = 0; //numero de colonne

    //On parcourt toutes les valeurs
    for (size_t i = 0; i < m_tempPerYear.size(); i++)
    {
        ARGB color = m_colors[7];
        //On cherche la couleur de la valeur
        for (size_t j = 0; j < 8; j++)
        {
            if (m_tempPerYear[i] <= m_intervals[j])
            {
                color = m_colors[j];
                break;
            }
        }
        GetLibGraph2()->setSolidBrush(color);
        CRectangle rectangle(CPoint(m_rectangleWidth * colNb, 0), CSize(m_rectangleWidth, m_rectangleHeight));
        GetLibGraph2()->drawRectangle(rectangle);
        colNb++;
    }
}

void CRaieCouleurs::CreateRaieCouleurs(const std::vector<float>& data)
{
    m_data = data;

    //On créé un nouveau tableau contenant les températures moyennes par années
    float moy = 0;
    size_t cpt = 0;
    for (size_t i = 0; i < m_data.size(); i++)
    {
        if (i % 12 == 0 && i != 0)
        {
            moy /= 12.f;
            m_tempPerYear.push_back(moy);
            cpt++;
        }
        moy += m_data[i];
    }
    //ne pas oublier la dernière valeur
    moy /= 12.f;
    m_tempPerYear.push_back(moy);

    //On calcule les intervalles de températures
    float maxTemp = *std::max_element(m_tempPerYear.begin(), m_tempPerYear.end());
    float minTemp = *std::min_element(m_tempPerYear.begin(), m_tempPerYear.end());
    float deltaTemp = maxTemp - (minTemp - 1);
    float interval = deltaTemp / 8.f;

    //Tableau contenant les intervals de valeurs (0-1, 1-2, ..., 6-7, 7+)
    m_intervals.resize(8);
    for (size_t i = 0; i < 8; i++)
        m_intervals[i] = minTemp + interval * i;

    //On récupère la taille de la fenêtre
    float width = GetLibGraph2()->getSize().m_fWidth;
    float height = GetLibGraph2()->getSize().m_fHeight;

    float heightMargin = GetLibGraph2()->getSize().m_fHeight * (10.f / 100.f);

    //On calcule la largeur d'un rectangle
    m_rectangleWidth = width / m_tempPerYear.size();
    //Puis on calcul la hauteur (un rectangle par an)
    m_rectangleHeight = (height/* - heightMargin*/);
}
