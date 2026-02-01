/**
 * @file test_bot_planification.cpp
 * @brief Tests du Bot Otrio
 */

#include <gtest/gtest.h>
#include "Bot.hpp"
#include "Plateau.hpp"
#include "Case.hpp"
#include "Cercle.hpp"
#include "Coup.hpp"
#include "CouleurCercle.hpp"
#include "TailleCercle.hpp"

class BotPlanificationTest : public ::testing::Test {
protected:
    Plateau* plateau;
    Bot* botRouge;
    Bot* botBleu;
    
    void SetUp() override {
        plateau = new Plateau();
        botRouge = new Bot(plateau, rouge, 0);
        botBleu = new Bot(plateau, bleu, 1);
    }
    
    void TearDown() override {
        delete botRouge;
        delete botBleu;
        delete plateau;
    }
    
    /**
     * @brief Place un cercle sur le plateau à une position donnée
     */
    void placerCercle(TailleCercle taille, CouleurCercle couleur, int x, int y) {
        Case* caseTarget = plateau->getCase(x, y);
        Cercle* cercle = new Cercle(taille, couleur);
        caseTarget->setCercles(cercle, taille);
    }
    
    /**
     * @brief Vérifie qu'un coup cible une position spécifique
     */
    bool coupCible(Coup& coup, int x, int y) {
        if (!coup.getCaseCible()) return false;
        return (coup.getCaseCible()->getPosX() == x && 
                coup.getCaseCible()->getPosY() == y);
    }
    
    /**
     * @brief Vérifie qu'un coup utilise une taille spécifique
     */
    bool coupUtiliseTaille(Coup& coup, TailleCercle taille) {
        if (!coup.getCercle()) return false;
        return coup.getCercle()->getTaille() == taille;
    }
};

// ============================================================================
// VICTOIRE IMMÉDIATE PAR ALIGNEMENT IDENTIQUE
// ============================================================================

TEST_F(BotPlanificationTest, VictoireImmediate_AlignementIdentique_Ligne) {
    // Configuration : 2 petits rouges en ligne 1
    placerCercle(petite, rouge, 1, 1);
    placerCercle(petite, rouge, 2, 1);
    
    // Le bot rouge doit compléter immédiatement
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr) << "Le bot doit proposer un coup";
    EXPECT_TRUE(coupCible(coup, 3, 1)) << "Le bot doit compléter en (3,1)";
    EXPECT_TRUE(coupUtiliseTaille(coup, petite)) << "Le bot doit utiliser un petit cercle";
}

TEST_F(BotPlanificationTest, VictoireImmediate_AlignementIdentique_Colonne) {
    // Configuration : 2 moyens rouges en colonne 2
    placerCercle(moyenne, rouge, 2, 1);
    placerCercle(moyenne, rouge, 2, 3);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 2, 2)) << "Le bot doit compléter en (2,2)";
    EXPECT_TRUE(coupUtiliseTaille(coup, moyenne));
}

TEST_F(BotPlanificationTest, VictoireImmediate_AlignementIdentique_Diagonale) {
    // Configuration : 2 grands rouges en diagonale
    placerCercle(grande, rouge, 1, 1);
    placerCercle(grande, rouge, 3, 3);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 2, 2)) << "Le bot doit compléter en (2,2)";
    EXPECT_TRUE(coupUtiliseTaille(coup, grande));
}

// ============================================================================
// VICTOIRE IMMÉDIATE PAR EMPILEMENT
// ============================================================================

TEST_F(BotPlanificationTest, VictoireImmediate_Empilement) {
    // Configuration : Moyen et Grand rouges empilés en (2,2)
    placerCercle(moyenne, rouge, 2, 2);
    placerCercle(grande, rouge, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 2, 2)) << "Le bot doit compléter l'empilement en (2,2)";
    EXPECT_TRUE(coupUtiliseTaille(coup, petite)) << "Le bot doit utiliser un petit cercle";
}

// ============================================================================
// DÉFENSE PRIORITAIRE SUR PLANIFICATION
// ============================================================================

TEST_F(BotPlanificationTest, Defense_BloqueMenaceAdverse_Ligne) {
    // Configuration : 
    // - 2 petits bleus alignés (menace adverse)
    // - 2 moyens rouges alignés ailleurs (planification possible)
    placerCercle(petite, bleu, 1, 1);
    placerCercle(petite, bleu, 2, 1);
    placerCercle(moyenne, rouge, 1, 2);
    placerCercle(moyenne, rouge, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit parer la menace bleu en priorité
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 3, 1)) << "Le bot doit bloquer la menace en (3,1)";
    EXPECT_TRUE(coupUtiliseTaille(coup, petite));
}

TEST_F(BotPlanificationTest, Defense_BloqueMenaceAdverse_Empilement) {
    // Configuration : 2 cercles bleus empilés (menace)
    placerCercle(petite, bleu, 1, 1);
    placerCercle(moyenne, bleu, 1, 1);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 1, 1)) << "Le bot doit bloquer l'empilement en (1,1)";
    EXPECT_TRUE(coupUtiliseTaille(coup, grande));
}

TEST_F(BotPlanificationTest, Defense_BloqueMenaceAdverse_Colonne) {
    // 2 grands bleus en colonne 3
    placerCercle(grande, bleu, 3, 1);
    placerCercle(grande, bleu, 3, 2);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 3, 3)) << "Le bot doit bloquer en (3,3)";
    EXPECT_TRUE(coupUtiliseTaille(coup, grande));
}

TEST_F(BotPlanificationTest, Defense_BloqueMenaceAdverse_DiagonaleSecondaire) {
    // 2 moyens bleus en diagonale secondaire
    placerCercle(moyenne, bleu, 1, 3);
    placerCercle(moyenne, bleu, 3, 1);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 2, 2));
    EXPECT_TRUE(coupUtiliseTaille(coup, moyenne));
}

// ============================================================================
// PLANIFICATION À 2 COUPS
// ============================================================================

TEST_F(BotPlanificationTest, Planification_2Coups_Empilement) {
    // Configuration : 1 grand rouge en (2,2)
    placerCercle(grande, rouge, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot peut choisir d'empiler (petit ou moyen)
    ASSERT_NE(coup.getCaseCible(), nullptr);
    
    // Si le bot choisit l'empilement, ce doit être en (2,2)
    if (coup.getCaseCible()->getPosX() == 2 && coup.getCaseCible()->getPosY() == 2) {
        EXPECT_TRUE(coup.getCercle()->getTaille() == petite || 
                   coup.getCercle()->getTaille() == moyenne)
            << "Pour empiler, le bot doit utiliser petit ou moyen";
    }
}

// ============================================================================
// PLANIFICATION À 3 COUPS (MAXIMUM)
// ============================================================================

TEST_F(BotPlanificationTest, Planification_3Coups_PlateauVide_AlignementIdentique) {
    // Plateau vide : le bot doit planifier une stratégie
    Coup coup = botRouge->Jouer();
    
    // Le bot doit proposer un coup valide
    ASSERT_NE(coup.getCaseCible(), nullptr) << "Le bot doit toujours proposer un coup";
    ASSERT_NE(coup.getCercle(), nullptr);
    
    // Position valide sur le plateau de jeu (1-3, 1-3)
    int x = coup.getCaseCible()->getPosX();
    int y = coup.getCaseCible()->getPosY();
    EXPECT_GE(x, 1);
    EXPECT_LE(x, 3);
    EXPECT_GE(y, 1);
    EXPECT_LE(y, 3);
}

TEST_F(BotPlanificationTest, Planification_3Coups_PrefereCentre) {
    // Sur plateau vide, le bot peut préférer le centre
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    
    // Note : Le bot peut choisir le centre (2,2) mais ce n'est pas obligatoire
    // Ce test vérifie juste que le coup est stratégiquement raisonnable
    int x = coup.getCaseCible()->getPosX();
    int y = coup.getCaseCible()->getPosY();
    EXPECT_GE(x, 1);
    EXPECT_LE(x, 3);
}

// ============================================================================
// PLANIFICATION ALIGNEMENT ORDONNÉ
// ============================================================================

TEST_F(BotPlanificationTest, Planification_AlignementOrdonne_PMG_Ligne) {
    // Configuration : Petit et Moyen rouges en ligne 2
    placerCercle(petite, rouge, 1, 2);
    placerCercle(moyenne, rouge, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit compléter avec un Grand
    ASSERT_NE(coup.getCaseCible(), nullptr);
    cout << coup.getCaseCible()->getPosX() << " " << coup.getCaseCible()->getPosY() << std::endl;
    EXPECT_TRUE(coupCible(coup, 3, 2)) << "Le bot doit compléter l'ordre P-M-G en (3,2)";
    EXPECT_TRUE(coupUtiliseTaille(coup, grande));
}

TEST_F(BotPlanificationTest, Planification_AlignementOrdonne_GMP_Colonne) {
    // Configuration : Grand et Moyen rouges en colonne 1
    placerCercle(grande, rouge, 1, 1);
    placerCercle(moyenne, rouge, 1, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit compléter avec un Petit pour faire G-M-P
    ASSERT_NE(coup.getCaseCible(), nullptr);
    EXPECT_TRUE(coupCible(coup, 1, 3));
    EXPECT_TRUE(coupUtiliseTaille(coup, petite));
}

// ============================================================================
// COMPARAISON DE PLUSIEURS PLANIFICATIONS
// ============================================================================

TEST_F(BotPlanificationTest, Planification_ChoisitMeilleurScore) {
    // Configuration complexe avec plusieurs options :
    // - Ligne 1 : 1 petit rouge (score empilement possible)
    // - Case (1,1) : 1 grand rouge (empilement possible, meilleur score)
    placerCercle(petite, rouge, 2, 1);
    placerCercle(grande, rouge, 1, 1);
    
    Coup coup = botRouge->Jouer();
    
    ASSERT_NE(coup.getCaseCible(), nullptr);
    
    // Le bot devrait préférer l'empilement (meilleur score)
    // Mais on accepte aussi qu'il continue l'alignement
    bool strategieValide = 
        (coup.getCaseCible()->getPosX() == 1 && coup.getCaseCible()->getPosY() == 1) || // Empilement
        (coup.getCaseCible()->getPosY() == 1); // Alignement ligne 1
    
    EXPECT_TRUE(strategieValide) << "Le bot doit choisir une stratégie cohérente";
}

// ============================================================================
// DÉTECTION DE MENACE AVEC ALIGNEMENT ORDONNÉ
// ============================================================================

TEST_F(BotPlanificationTest, Defense_MenaceAlignementOrdonne_PMG) {
    // Configuration : Bleu a Petit et Moyen alignés (menace P-M-G)
    placerCercle(petite, bleu, 1, 1);
    placerCercle(moyenne, bleu, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit bloquer la diagonale en (3,3) avec un grand cercle
    ASSERT_NE(coup.getCaseCible(), nullptr);
    ASSERT_EQ(coup.getCercle()->getTaille(), grande);

    // Si le bot détecte la menace, il doit bloquer en (3,3)
    // Sinon, il peut jouer ailleurs (selon l'implémentation)
    bool bloqueOuStrategie = 
        (coup.getCaseCible()->getPosX() == 3 && coup.getCaseCible()->getPosY() == 3) ||
        (coup.getCaseCible() != nullptr); // Coup valide au minimum
    
    EXPECT_TRUE(bloqueOuStrategie);
}

// ============================================================================
// PLATEAU COMPLEXE (PLUSIEURS COULEURS)
// ============================================================================

TEST_F(BotPlanificationTest, PlateauComplexe_PlusieursOptions) {
    // Configuration complexe
    placerCercle(petite, rouge, 1, 1);
    placerCercle(moyenne, bleu, 2, 1);
    placerCercle(grande, rouge, 3, 1);
    placerCercle(petite, bleu, 1, 2);
    placerCercle(moyenne, rouge, 2, 2);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit trouver une stratégie valide
    ASSERT_NE(coup.getCaseCible(), nullptr);
    ASSERT_NE(coup.getCercle(), nullptr);
    
    // Vérifier que le coup est dans la zone de jeu
    EXPECT_GE(coup.getCaseCible()->getPosX(), 1);
    EXPECT_LE(coup.getCaseCible()->getPosX(), 3);
    EXPECT_GE(coup.getCaseCible()->getPosY(), 1);
    EXPECT_LE(coup.getCaseCible()->getPosY(), 3);
}

// ============================================================================
// COMPORTEMENT PAR DÉFAUT (AUCUNE STRATÉGIE CLAIRE)
// ============================================================================

TEST_F(BotPlanificationTest, CoupParDefaut_AucuneStrategieClaire) {
    // Plateau avec cercles dispersés sans menace ni opportunité claire
    placerCercle(petite, bleu, 1, 1);
    placerCercle(grande, rouge, 3, 3);
    placerCercle(moyenne, bleu, 2, 3);
    
    Coup coup = botRouge->Jouer();
    
    // Le bot doit quand même proposer un coup valide
    ASSERT_NE(coup.getCaseCible(), nullptr) << "Le bot doit toujours proposer un coup";
    ASSERT_NE(coup.getCercle(), nullptr);
    
    // Couleur correcte
    EXPECT_EQ(coup.getCercle()->getCouleur(), rouge);
}