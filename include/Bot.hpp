#pragma once
#include "CouleurCercle.hpp"
#include "Joueur.hpp"
#include "TailleCercle.hpp"
#include <vector>

/**
* @brief Tentative d'algo minimax (inspiré par https://github.com/AbdallahHemdan/MiniMax)
*/
class Bot : public Joueur
{
private:
    // Détection de menaces
    Coup verifierColonne(int col);
    Coup trouverParadeIdentColonne(TailleCercle taille, CouleurCercle c, int col);
    Coup analyserAlignement(const std::vector<Case*>& cases);
    Coup verifierMenaceEmpilement();
    
    
    /**
     * @brief Structure pour représenter une séquence de coups planifiés
     */
    struct PlanificationVictoire {
        std::vector<Coup> coups;        // Séquence de coups à jouer
        int profondeur;                 // Nombre de coups nécessaires
        double score;                   // Score de la planification (plus élevé = mieux)
        
        PlanificationVictoire() : profondeur(0), score(0.0) {}
    };

    /**
     * @brief Cherche une séquence de 3 coups menant à la victoire
     * @return La meilleure planification trouvée (peut être vide si aucune trouvée)
     */
    PlanificationVictoire chercherVictoireEn3Coups();

    /**
     * @brief Vérifie si on peut gagner en complétant un alignement de 3 cercles identiques
     * @param cases Les 3 cases à analyser (ligne, colonne ou diagonale)
     * @return Une planification si trouvée
     */
    PlanificationVictoire planifierAlignementIdentiques(const std::vector<Case*>& cases);

    /**
     * @brief Vérifie si on peut gagner en complétant un alignement P-M-G
     * @param cases Les 3 cases à analyser
     * @return Une planification si trouvée
     */
    PlanificationVictoire planifierAlignementOrdonne(const std::vector<Case*>& cases);

    /**
     * @brief Vérifie si on peut gagner en complétant un empilement P-M-G
     * @param c La case à analyser
     * @return Une planification si trouvée
     */
    PlanificationVictoire planifierEmpilement(Case* c);

    /**
     * @brief Évalue tous les alignements possibles (lignes, colonnes, diagonales)
     * @return La meilleure planification trouvée
     */
    PlanificationVictoire evaluerTousLesAlignements();

    /**
     * @brief Simule le placement d'un cercle (sans modifier réellement le plateau)
     * @param cercle Le cercle à placer
     * @param caseTarget La case cible
     * @return true si le placement est valide
     */
    bool simulerPlacement(Cercle* cercle, Case* caseTarget);

    /**
     * @brief Compte combien de cercles de la couleur donnée sont déjà dans les cases
     * @param cases Les cases à analyser
     * @param couleur La couleur à compter
     * @return Tableau [taille] -> nombre de cercles
     */
    std::array<int, 3> compterCerclesDansCases(const std::vector<Case*>& cases, CouleurCercle couleur);

public:
    Bot(Plateau* plateau, CouleurCercle c, int idJoueur);

    /**
     * @brief Méthode principale : choisit le meilleur coup à jouer
     * Priorité : 1) Parer menaces immédiates  2) Planifier victoire en 3 coups  3) Coup par défaut
     */
    Coup Jouer() override;

    /**
     * @brief Trouve un cercle disponible dans la réserve du joueur
     * @param taille Taille du cercle recherché
     * @param origine [OUT] Pointeur vers la case d'origine (sera modifié)
     * @return Pointeur vers le cercle trouvé, ou nullptr
     */
    Cercle* possedeCercle(TailleCercle taille, Case** origine);
};