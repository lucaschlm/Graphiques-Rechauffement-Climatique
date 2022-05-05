#include "Spirale.h"

void CSpirale::CreateSpirale(const std::vector<float>& sommeMoyStation)
{
    size_t cptAnnee = 1; // Compteur pour compter le nombre d'annee
    float coefx = 750.0f;
    float coefy = 500.0f;

    for (size_t i = 13; i < sommeMoyStation.size() + 1; i++) { // On parcours tous les mois
        float T = ((sommeMoyStation[i - 1] - sommeMoyStation[i - 1 - (12 * cptAnnee)]) + 5) * 48;
        switch (i - (12 * cptAnnee)) // Switch pour savoir le mois en cours (janvier, février, ...)
        {
        case 1: // Janvier
            m_vCpointGraph.push_back(CPoint{ coefx, T + coefy });
            break;
        case 2: // Fevrier
            m_vCpointGraph.push_back(CPoint{ 0.5f * T + coefx, ((pi / 2.0f) * 0.5f * T) + coefy });
            break;
        case 3: // Mars
            m_vCpointGraph.push_back(CPoint{ ((std::sqrt(3.0f) / 2.0f) * T) + coefx, ((pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T) + coefy });
            break;
        case 4: // Avril
            m_vCpointGraph.push_back(CPoint{ T + coefx, coefy });
            break;
        case 5: // Mai
            m_vCpointGraph.push_back(CPoint{ ((std::sqrt(3.0f) / 2.0f) * T) + coefx, -((pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T) + coefy });
            break;
        case 6: // Juin
            m_vCpointGraph.push_back(CPoint{ (0.5f * T) + coefx, -((pi / 2.0f) * 0.5f * T) + coefy });
            break;
        case 7: // Juillet
            m_vCpointGraph.push_back(CPoint{ coefx, -T + coefy });
            break;
        case 8: // Aout
            m_vCpointGraph.push_back(CPoint{ (-0.5f * T) + coefx, ((pi / 2.0f) * -0.5f * T) + coefy });
            break;
        case 9: // Septembre
            m_vCpointGraph.push_back(CPoint{ (-(std::sqrt(3.0f) / 2.0f) * T) + coefx, ((pi / 6.0f) * -(std::sqrt(3.0f) / 2.0f) * T) + coefy });
            break;
        case 10: // Octobre
            m_vCpointGraph.push_back(CPoint{ -T + coefx, coefy });
            break;
        case 11: // Novembre
            m_vCpointGraph.push_back(CPoint{ (-(std::sqrt(3.0f) / 2.0f) * T) + coefx, (pi / 6.0f) * (std::sqrt(3.0f) / 2.0f) * T + coefy });
            break;
        case 12: // Decembre
            m_vCpointGraph.push_back(CPoint{ (-0.5f * T) + coefx, -((pi / 2.0f) * -0.5f * T) + coefy });
            break;

        }
        if (i % 12 == 0) { // Incrementation du compteur d'annee tous les 12 mois
            cptAnnee++;
        }
    }
}

void CSpirale::Afficher() const
{
    size_t m_cptColor12 = 15; // Compteur pour le changement de couleur tous les 12 mois

    for (size_t i = 1; i < m_vCpointGraph.size(); i++) {

        GetLibGraph2()->setSolidBrush(MakeARGB(255, 0, 0, 0));
        // Affichage des points pour tracer chaque traits
        GetLibGraph2()->drawEllipse(CRectangle{ m_vCpointGraph[i - 1], CSize{ 5, 5 } });

        if (i % 12 == 0) { // Changement des couleurs tous les 12 mois
            m_cptColor12 += 8;
        }
        // Changement de la couleur
        GetLibGraph2()->setPen(MakeARGB(255, 255, m_cptColor12, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
        // Affichage des traits entre les points
        GetLibGraph2()->drawLine(m_vCpointGraph[i - 1], m_vCpointGraph[i]);
    }
}
