#include "Bot.hpp"
#include "Cercle.hpp"
#include "CouleurCercle.hpp"
#include "Joueur.hpp"
#include "TailleCercle.hpp"
#include <cstdint>
#include <iostream>

Bot::Bot(Plateau* plateau, CouleurCercle couleur, int idJoueur) : Joueur(plateau, couleur, idJoueur)
{
}

Coup Bot::Jouer() {
    Coup parade(nullptr, nullptr, nullptr);

    // Menaces immédiates
    
    // Empilements sur une case 
    parade = verifierMenaceEmpilement();
    if (parade.getCaseCible()) {
        std::cout << "Parade contre empilement" << std::endl;
        return parade;
    }

    // Lignes
    for (int y = 1; y <= 3; y++) {
        parade = analyserAlignement({plateau->getCase(1,y), plateau->getCase(2,y), plateau->getCase(3,y)});
        if (parade.getCaseCible()) {
            std::cout << "Parade contre alignement ligne " << y << std::endl;
            return parade;
        }
    }

    // Colonnes
    for (int x = 1; x <= 3; x++) {
        parade = analyserAlignement({plateau->getCase(x,1), plateau->getCase(x,2), plateau->getCase(x,3)});
        if (parade.getCaseCible()) {
            std::cout << "Parade contre alignement colonne " << x << std::endl;
            return parade;
        }
    }

    // Diagonales
    parade = analyserAlignement({plateau->getCase(1,1), plateau->getCase(2,2), plateau->getCase(3,3)});
    if (parade.getCaseCible()) {
        std::cout << "Parade contre alignement diagonale principale" << std::endl;
        return parade;
    }

    parade = analyserAlignement({plateau->getCase(1,3), plateau->getCase(2,2), plateau->getCase(3,1)});
    if (parade.getCaseCible()) {
        std::cout << "Parade contre alignement diagonale secondaire" << std::endl;
        return parade;
    }

    // Genre d'algo minimax en se basant sur une explication github (voir description de la classe)
    
    PlanificationVictoire plan = chercherVictoireEn3Coups();
    
    if (!plan.coups.empty() && plan.coups[0].getCaseCible() != nullptr) {
        std::cout << "Minimax Coup " << 1 << "/" << plan.profondeur 
                  << " victoire en " << plan.profondeur << " coups (score: " 
                  << plan.score << ")" << std::endl;
        return plan.coups[0]; // Jouer le premier coup de la séquence
    }

    // ========== PRIORITÉ 3 : COUP PAR DÉFAUT (stratégie basique) ==========
    
    std::cout << "coup aléatoire" << std::endl;
    
    // Essayer de placer un cercle au centre si possible
    Case* centre = plateau->getCase(2, 2);
    for (int t = 0; t < 3; t++) {
        if (centre->getCercles()[t] == nullptr) {
            Case* origine = nullptr;
            Cercle* cercle = possedeCercle((TailleCercle)t, &origine);
            if (cercle && origine) return Coup(origine, cercle, centre);
        }
    }
    
    // Sinon, chercher n'importe quelle case libre
    for (int x = 1; x <= 3; x++) {
        for (int y = 1; y <= 3; y++) {
            Case* c = plateau->getCase(x, y);
            for (int t = 0; t < 3; t++) {
                if (c->getCercles()[t] == nullptr) {
                    Case* origine = nullptr;
                    Cercle* cercle = possedeCercle((TailleCercle)t, &origine);
                    if (cercle && origine) return Coup(origine, cercle, c);
                }
            }
        }
    }
    
    return Coup(nullptr, nullptr, nullptr);
}

// ========================================================================
// PLANIFICATION À 3 COUPS
// ========================================================================

Bot::PlanificationVictoire Bot::chercherVictoireEn3Coups() {
    PlanificationVictoire meilleurPlan;
    meilleurPlan.score = -1000.0;

    // Évaluer tous les types de victoires possibles
    PlanificationVictoire planAlignements = evaluerTousLesAlignements();
    
    // Vérifier tous les empilements possibles
    for (int x = 1; x <= 3; x++) {
        for (int y = 1; y <= 3; y++) {
            PlanificationVictoire planEmp = planifierEmpilement(plateau->getCase(x, y));
            if (planEmp.score > meilleurPlan.score) {
                meilleurPlan = planEmp;
            }
        }
    }

    // Comparer avec les alignements
    if (planAlignements.score > meilleurPlan.score) {
        meilleurPlan = planAlignements;
    }

    return meilleurPlan;
}

Bot::PlanificationVictoire Bot::evaluerTousLesAlignements() {
    PlanificationVictoire meilleurPlan;
    meilleurPlan.score = -1000.0;

    // Lignes
    for (int y = 1; y <= 3; y++) {
        std::vector<Case*> ligne = {plateau->getCase(1,y), plateau->getCase(2,y), plateau->getCase(3,y)};
        
        PlanificationVictoire p1 = planifierAlignementIdentiques(ligne);
        if (p1.score > meilleurPlan.score) meilleurPlan = p1;
        
        PlanificationVictoire p2 = planifierAlignementOrdonne(ligne);
        if (p2.score > meilleurPlan.score) meilleurPlan = p2;
    }

    // Colonnes
    for (int x = 1; x <= 3; x++) {
        std::vector<Case*> colonne = {plateau->getCase(x,1), plateau->getCase(x,2), plateau->getCase(x,3)};
        
        PlanificationVictoire p1 = planifierAlignementIdentiques(colonne);
        if (p1.score > meilleurPlan.score) meilleurPlan = p1;
        
        PlanificationVictoire p2 = planifierAlignementOrdonne(colonne);
        if (p2.score > meilleurPlan.score) meilleurPlan = p2;
    }

    // Diagonale principale
    std::vector<Case*> diag1 = {plateau->getCase(1,1), plateau->getCase(2,2), plateau->getCase(3,3)};
    PlanificationVictoire pd1 = planifierAlignementIdentiques(diag1);
    if (pd1.score > meilleurPlan.score) meilleurPlan = pd1;
    
    PlanificationVictoire pd2 = planifierAlignementOrdonne(diag1);
    if (pd2.score > meilleurPlan.score) meilleurPlan = pd2;

    // Diagonale secondaire
    std::vector<Case*> diag2 = {plateau->getCase(1,3), plateau->getCase(2,2), plateau->getCase(3,1)};
    PlanificationVictoire pd3 = planifierAlignementIdentiques(diag2);
    if (pd3.score > meilleurPlan.score) meilleurPlan = pd3;
    
    PlanificationVictoire pd4 = planifierAlignementOrdonne(diag2);
    if (pd4.score > meilleurPlan.score) meilleurPlan = pd4;

    return meilleurPlan;
}

Bot::PlanificationVictoire Bot::planifierAlignementIdentiques(const std::vector<Case*>& cases) {
    PlanificationVictoire plan;

    // Pour chaque taille de cercle (petit, moyen, grand)
    for (int taille = 0; taille < 3; taille++) {
        std::array<int, 3> compteur = compterCerclesDansCases(cases, Couleur);
        
        int nbDejaPoses = compteur[taille];
        int nbAPoser = 3 - nbDejaPoses;

        // On ne peut pas planifier si on a besoin de plus de 3 coups
        if (nbAPoser > 3 || nbAPoser <= 0) continue;

        // Vérifier qu'on possède assez de cercles de cette taille
        int cerclesDisponibles = 0;
        for (int i = 0; i < nbAPoser; i++) {
            if (possedeCercle((TailleCercle)taille, nullptr)) {
                cerclesDisponibles++;
            }
        }
        
        if (cerclesDisponibles < nbAPoser) continue;

        // Construire la séquence de coups
        std::vector<Coup> sequence;
        for (Case* c : cases) {
            if (c->getCercles()[taille] == nullptr) {
                Case* origine = nullptr;
                Cercle* cercle = possedeCercle((TailleCercle)taille, &origine);
                if (cercle && origine) {
                    sequence.push_back(Coup(origine, cercle, c));
                }
            }
        }

        // Calculer le score : moins de coups = meilleur score
        double score = 100.0 - (nbAPoser * 10.0) + (nbDejaPoses * 5.0);

        if (score > plan.score && sequence.size() == nbAPoser) {
            plan.coups = sequence;
            plan.profondeur = nbAPoser;
            plan.score = score;
        }
    }

    return plan;
}

Bot::PlanificationVictoire Bot::planifierAlignementOrdonne(const std::vector<Case*>& cases) {
    PlanificationVictoire plan;

    // Compter les cercles de notre couleur déjà présents de chaque taille
    std::array<int, 3> compteur = compterCerclesDansCases(cases, Couleur);

    // Vérifier si on a au moins un cercle de chaque taille dans ces cases
    int nbTaillesPresentes = 0;
    for (int i = 0; i < 3; i++) {
        if (compteur[i] > 0) nbTaillesPresentes++;
    }

    // Si on a déjà les 3 tailles, pas besoin de planifier (on devrait avoir gagné)
    if (nbTaillesPresentes == 3) return plan;

    // Identifier quelles tailles manquent
    std::vector<TailleCercle> taillesManquantes;
    for (int t = 0; t < 3; t++) {
        if (compteur[t] == 0) {
            taillesManquantes.push_back((TailleCercle)t);
        }
    }

    // On ne peut planifier que si on manque au max 3 tailles
    if (taillesManquantes.size() > 3) return plan;

    // Vérifier qu'on possède les cercles nécessaires
    bool toutesDisponibles = true;
    for (TailleCercle t : taillesManquantes) {
        Case* origineTemp = nullptr;
        if (!possedeCercle(t, &origineTemp)) {
            toutesDisponibles = false;
            break;
        }
    }

    if (!toutesDisponibles) return plan;

    // Construire la séquence de coups
    std::vector<Coup> sequence;
    for (TailleCercle taille : taillesManquantes) {
        // Trouver une case qui n'a pas de cercle de notre couleur pour cette taille
        // et qui peut accueillir un cercle de cette taille
        for (Case* c : cases) {
            // Vérifier que l'emplacement pour cette taille est libre
            if (c->getCercles()[taille] != nullptr) continue;
            
            // Pour un alignement P-M-G, on cherche une case qui n'a pas déjà
            // un cercle de notre couleur (sinon c'est un empilement)
            bool caseDejaUtilisee = false;
            for (int t = 0; t < 3; t++) {
                Cercle* cerclePresent = c->getCercles()[t];
                if (cerclePresent && cerclePresent->getCouleur() == Couleur) {
                    caseDejaUtilisee = true;
                    break;
                }
            }
            
            // Pour un alignement, on préfère une case vide ou avec un autre cercle
            if (!caseDejaUtilisee) {
                Case* origine = nullptr;
                Cercle* cercle = possedeCercle(taille, &origine);
                if (cercle && origine) {
                    sequence.push_back(Coup(origine, cercle, c));
                    break; // Une seule case par taille
                }
            }
        }
    }

    // Score : favoriser les alignements ordonnés avec moins de coups
    double score = 95.0 - (taillesManquantes.size() * 10.0) + (nbTaillesPresentes * 8.0);

    if (sequence.size() == taillesManquantes.size()) {
        plan.coups = sequence;
        plan.profondeur = taillesManquantes.size();
        plan.score = score;
    }

    return plan;
}

Bot::PlanificationVictoire Bot::planifierEmpilement(Case* c) {
    PlanificationVictoire plan;

    // Compter combien de cercles de notre couleur sont déjà empilés ici
    int nbDejaPoses = 0;
    std::vector<TailleCercle> taillesManquantes;

    for (int t = 0; t < 3; t++) {
        Cercle* cercle = c->getCercles()[t];
        if (cercle && cercle->getCouleur() == Couleur) {
            nbDejaPoses++;
        } else if (cercle == nullptr) {
            taillesManquantes.push_back((TailleCercle)t);
        }
    }

    int nbAPoser = 3 - nbDejaPoses;

    // On ne peut pas planifier si on a besoin de plus de 3 coups
    if (nbAPoser > 3 || nbAPoser <= 0) return plan;

    // Vérifier qu'on possède les cercles nécessaires
    std::vector<Coup> sequence;
    for (TailleCercle taille : taillesManquantes) {
        Case* origine = nullptr;
        Cercle* cercle = possedeCercle(taille, &origine);
        if (cercle && origine) {
            sequence.push_back(Coup(origine, cercle, c));
        }
    }

    if (sequence.size() != taillesManquantes.size()) return plan;

    // Score : empilements ont un bonus car ils sont plus rares
    double score = 105.0 - (nbAPoser * 10.0) + (nbDejaPoses * 6.0);

    plan.coups = sequence;
    plan.profondeur = nbAPoser;
    plan.score = score;

    return plan;
}

std::array<int, 3> Bot::compterCerclesDansCases(const std::vector<Case*>& cases, CouleurCercle couleur) {
    std::array<int, 3> compteur = {0, 0, 0}; // [petite, moyenne, grande]

    for (Case* c : cases) {
        for (int t = 0; t < 3; t++) {
            Cercle* cercle = c->getCercles()[t];
            if (cercle && cercle->getCouleur() == couleur) {
                compteur[t]++;
            }
        }
    }

    return compteur;
}

bool Bot::simulerPlacement(Cercle* cercle, Case* caseTarget) {
    // Vérifier si la case cible peut accueillir ce cercle
    if (!cercle || !caseTarget) return false;
    
    TailleCercle taille = cercle->getTaille();
    
    // Vérifier si la position est libre pour cette taille
    return (caseTarget->getCercles()[taille] == nullptr);
}

Coup Bot::analyserAlignement(const std::vector<Case*>& cases) {
    uint8_t ident[3][4] = {0}; // [taille][couleur]
    uint8_t masques[4] = {0};  // [couleur] pour l'ordre P-M-G

    for (Case* c : cases) {
        for (Cercle* cercle : c->getCercles()) {
            if (cercle == nullptr) continue;
            
            int couleur = cercle->getCouleur();
            int t = cercle->getTaille();

            // Détection Menace Tailles Identiques
            ident[t][couleur]++;
            if (ident[t][couleur] == 2 && couleur != Couleur) {
                // Menace adverse détectée
                for (Case* target : cases) {
                    if (target->getCercles()[t] == nullptr) {
                        Case* origine = nullptr;
                        Cercle* monCercle = possedeCercle((TailleCercle)t, &origine);
                        if (monCercle && origine) return Coup(origine, monCercle, target);
                    }
                }
            }

            // Détection Menace Ordre (P-M-G)
            masques[couleur] |= (1 << t);
            if ((masques[couleur] == 3 || masques[couleur] == 5 || masques[couleur] == 6) && couleur != Couleur) {
                TailleCercle manquante = (masques[couleur] == 3) ? TailleCercle::grande : 
                                        (masques[couleur] == 5 ? TailleCercle::moyenne : TailleCercle::petite);
                for (Case* target : cases) {
                    if (target->getCercles()[manquante] == nullptr) {
                        Case* origine = nullptr;
                        Cercle* monCercle = possedeCercle(manquante, &origine);
                        if (monCercle && origine) return Coup(origine, monCercle, target);
                    }
                }
            }
        }
    }
    return Coup(nullptr, nullptr, nullptr);
}

Coup Bot::verifierMenaceEmpilement() {
    for (int x = 1; x <= 3; x++) {
        for (int y = 1; y <= 3; y++) {
            Case* c = plateau->getCase(x, y);
            uint8_t count[4] = {0};
            for (Cercle* cercle : c->getCercles()) {
                if (cercle) count[cercle->getCouleur()]++;
            }
            for (int i = 0; i < 4; i++) {
                if (count[i] == 2 && i != Couleur) { // Menace adverse
                    for (int t = 0; t < 3; t++) {
                        if (c->getCercles()[t] == nullptr) {
                            Case* origine = nullptr;
                            Cercle* monCercle = possedeCercle((TailleCercle)t, &origine);
                            if (monCercle && origine) return Coup(origine, monCercle, c);
                        }
                    }
                }
            }
        }
    }
    return Coup(nullptr, nullptr, nullptr);
}

Coup Bot::verifierColonne(int col)
{
    uint8_t ident[3][4] = {0};
    for(int y = 1; y <= 3; y++)
    {
        Case* current = plateau->getCase(col, y);
        for(Cercle* cercle : current->getCercles()) {
            if(cercle == nullptr) continue;

            ident[cercle->getTaille()][cercle->getCouleur()] += 1; 
            if(ident[cercle->getTaille()][cercle->getCouleur()] == 2 && cercle->getCouleur() != Couleur) {
                std::cout << "Menace immédiate: Colonne num " << col <<" tailles identiques" << std::endl;
                Coup parade = trouverParadeIdentColonne(cercle->getTaille(), cercle->getCouleur(), col);
                return parade;
            }
        }
    }
    return Coup(nullptr, nullptr, nullptr);
}

Coup Bot::trouverParadeIdentColonne(TailleCercle taille, CouleurCercle couleur, int col)
{
    for (int y = 1; y <= 3; y++) {
        Case* current = plateau->getCase(col, y);
        if(current->getCercles()[taille] != nullptr) continue;

        Case* origine = nullptr;
        Cercle* cercle = possedeCercle(taille, &origine);
        if (cercle != nullptr && origine != nullptr) {
            return Coup(origine, cercle, current);
        } else {
            std::cout << "On est morts, pas de cercle pour contrer" << std::endl;
            return Coup(nullptr, nullptr, nullptr);
        }
    }
    std::cout << "Fausse menace détectée ? Vérifier colonne a indentifié une menace non existante" << std::endl;
    return Coup(nullptr, nullptr, nullptr);
}

Cercle* Bot::possedeCercle(TailleCercle taille, Case** origine)
{
    int x, y, maxX, maxY;

    switch (Couleur) {
    case rouge:
        y = 4; maxY = 4; x = 1; maxX = 3;
        break;
    case bleu:
        y = 0; maxY = 0; x = 1; maxX = 3;
        break;
    case jaune:
        y = 1; maxY = 3; x = 0; maxX = 0;
        break;
    case vert:
        y = 1; maxY = 3; x = 4; maxX = 4;
        break;
    }

    for (; x <= maxX; x++) {
        for (; y <= maxY; y++) {
            Case* c = plateau->getCase(x, y);
            if(c->getCercles()[taille] != nullptr) {
                if (origine) *origine = c;  // Stocker la case d'origine
                return c->getCercles()[taille];
            }
        }
    }
    
    if (origine) *origine = nullptr;
    return nullptr;
}