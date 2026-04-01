#include <cassert>
#include <iostream>

#include "Case.hpp"
#include "CouleurCercle.hpp"
#include "TailleCercle.hpp"
#include "Plateau.hpp"

// Constructeurs
Plateau::Plateau()
{
    // Instancier toutes les cases du plateau
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            // Ne pas instancier les coins
            if ((y == 0 || y == 4) && (x == 0 || x == 4))
            {
                cases[x][y] = nullptr;
                continue;
            }

            cases[x][y] = new Case(x, y);

            // Initialiser la case avec des cercles si besoin
            if (y == 0)
            {
                // TODO: Moche de ouf
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::bleu), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::bleu), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::bleu), TailleCercle::petite);
            }
            else if (y == 4)
            {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::rouge), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::rouge), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::rouge), TailleCercle::petite);
            }
            else if (x == 0)
            {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::jaune), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::jaune), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::jaune), TailleCercle::petite);
            }
            else if (x == 4)
            {
                cases[x][y]->setCercles(new Cercle(TailleCercle::grande, CouleurCercle::vert), TailleCercle::grande);
                cases[x][y]->setCercles(new Cercle(TailleCercle::moyenne, CouleurCercle::vert), TailleCercle::moyenne);
                cases[x][y]->setCercles(new Cercle(TailleCercle::petite, CouleurCercle::vert), TailleCercle::petite);
            }
        }
    }
}

Plateau::~Plateau()
{
    // Détruire toutes les instances de case
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            Case *c = cases[x][y];
            if (c)
            {
                delete c;
            }
        }
    }
}

// Accesseur
Case *Plateau::getCase(int x, int y)
{
    // Validation des entrées
    assert(x >= 0 && x < 5);
    assert(y >= 0 && y < 5);
    return cases[x][y];
}

// Méthodes
void Plateau::Affichage()
{
    std::cout << "\033[2J"; // Clear le screen
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (cases[x][y])
            {
                cases[x][y]->AffichageCase(x, y);
            }
        }
    }
    std::cout << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl;
}

bool Plateau::placerCercle(Coup coup)
{
    if (coup.getOrigine() == nullptr || coup.getCercle() == nullptr || coup.getCaseCible() == nullptr)
    {
        return false;
    }

    if (coup.getCaseCible()->getCercles()[coup.getCercle()->getTaille()] != nullptr)
    {
        return false;
    }

    // déplacer le cercle
    coup.getOrigine()->setCercles(nullptr, coup.getCercle()->getTaille());
    coup.getCaseCible()->setCercles(coup.getCercle(), coup.getCercle()->getTaille());

    return true;
}

/**
 * @brief Vérifie la condition d'empilement de 3 cercles de meme couleur
 *
 * @return true
 * @return false
 */
bool Plateau::victoireEmpilement(CouleurCercle couleur)
{
    bool empilement = false;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            Case *laCase = getCase(i, j); // parcours de toutes les cases du tableau
            if (!laCase)
                continue;

            int nb = 0;
            std::array<Cercle *, 3> cercles = laCase->getCercles();
            for (Cercle *cercle : cercles) // parcours des cercles dans la case
            {
                if (cercle && cercle->getCouleur() == couleur)
                {
                    nb++;
                }
            }
            if (nb == 3)
            {
                empilement = true;
            }
        }
    }
    return empilement;
}
/**
 * @brief Vérifie l'alignement de 3 cercles identiques
 *
 * @return true
 * @return false
 */
bool Plateau::victoireAlignementIdentique(CouleurCercle couleur)
{
    bool victoire = false;
    // Pour chaque taille : 0=petit, 1=moyen, 2=grand
    for (int taille = 0; taille < 3; ++taille)
    {
        // ===== LIGNES =====
        for (int y = 1; y <= 3; ++y)
        {
            Cercle *c1 = getCase(1, y)->getCercles()[taille];
            Cercle *c2 = getCase(2, y)->getCercles()[taille];
            Cercle *c3 = getCase(3, y)->getCercles()[taille];

            if (c1 && c2 && c3 &&
                c1->getCouleur() == couleur &&
                c2->getCouleur() == couleur &&
                c3->getCouleur() == couleur)
            {
                victoire = true;
            }
        }

        // ===== COLONNES =====
        for (int x = 1; x <= 3; ++x)
        {
            Cercle *c1 = getCase(x, 1)->getCercles()[taille];
            Cercle *c2 = getCase(x, 2)->getCercles()[taille];
            Cercle *c3 = getCase(x, 3)->getCercles()[taille];

            if (c1 && c2 && c3 &&
                c1->getCouleur() == couleur &&
                c2->getCouleur() == couleur &&
                c3->getCouleur() == couleur)
            {
                victoire = true;
            }
        }

        // ===== DIAGONALE PRINCIPALE ↘ ===== (1,1) (2,2) (3,3)
        {
            Cercle *c1 = getCase(1, 1)->getCercles()[taille];
            Cercle *c2 = getCase(2, 2)->getCercles()[taille];
            Cercle *c3 = getCase(3, 3)->getCercles()[taille];

            if (c1 && c2 && c3 &&
                c1->getCouleur() == couleur &&
                c2->getCouleur() == couleur &&
                c3->getCouleur() == couleur)
            {
                victoire = true;
            }
        }

        // ===== DIAGONALE SECONDAIRE ↙ ===== (3,1) (2,2) (1,3)
        {
            Cercle *c1 = getCase(3, 1)->getCercles()[taille];
            Cercle *c2 = getCase(2, 2)->getCercles()[taille];
            Cercle *c3 = getCase(1, 3)->getCercles()[taille];

            if (c1 && c2 && c3 &&
                c1->getCouleur() == couleur &&
                c2->getCouleur() == couleur &&
                c3->getCouleur() == couleur)
            {
                victoire = true;
            }
        }
    }

    return victoire;
}

/**
 * @brief Vérifie l'alignement de 3 cercles de meme couleur de taille ascendante ou descendante
 *
 * @return true
 * @return false
 */
bool Plateau::victoireAlignementOrdonnee(CouleurCercle couleur)
{
    bool victoire = false;
    // ===== LIGNES =====
    for (int y = 1; y <= 3; ++y)
    {
        // Ascendant : petit, moyen, grand
        Cercle *a1 = getCase(1, y)->getCercles()[0];
        Cercle *a2 = getCase(2, y)->getCercles()[1];
        Cercle *a3 = getCase(3, y)->getCercles()[2];

        if (a1 && a2 && a3 &&
            a1->getCouleur() == couleur &&
            a2->getCouleur() == couleur &&
            a3->getCouleur() == couleur)
        {
            victoire = true;
        }

        // Descendant : grand, moyen, petit
        Cercle *d1 = getCase(1, y)->getCercles()[2];
        Cercle *d2 = getCase(2, y)->getCercles()[1];
        Cercle *d3 = getCase(3, y)->getCercles()[0];

        if (d1 && d2 && d3 &&
            d1->getCouleur() == couleur &&
            d2->getCouleur() == couleur &&
            d3->getCouleur() == couleur)
        {
            victoire = true;
        }
    }

    // ===== COLONNES =====
    for (int x = 1; x <= 3; ++x)
    {
        // Ascendant : petit, moyen, grand (de haut en bas)
        Cercle *a1 = getCase(x, 1)->getCercles()[0];
        Cercle *a2 = getCase(x, 2)->getCercles()[1];
        Cercle *a3 = getCase(x, 3)->getCercles()[2];

        if (a1 && a2 && a3 &&
            a1->getCouleur() == couleur &&
            a2->getCouleur() == couleur &&
            a3->getCouleur() == couleur)
        {
            victoire = true;
        }

        // Descendant : grand, moyen, petit
        Cercle *d1 = getCase(x, 1)->getCercles()[2];
        Cercle *d2 = getCase(x, 2)->getCercles()[1];
        Cercle *d3 = getCase(x, 3)->getCercles()[0];

        if (d1 && d2 && d3 &&
            d1->getCouleur() == couleur &&
            d2->getCouleur() == couleur &&
            d3->getCouleur() == couleur)
        {
            victoire = true;
        }
    }

    // ===== DIAGONALE PRINCIPALE ↘ ===== (1,1) (2,2) (3,3)
    {
        // Ascendant
        Cercle *a1 = getCase(1, 1)->getCercles()[0];
        Cercle *a2 = getCase(2, 2)->getCercles()[1];
        Cercle *a3 = getCase(3, 3)->getCercles()[2];

        if (a1 && a2 && a3 &&
            a1->getCouleur() == couleur &&
            a2->getCouleur() == couleur &&
            a3->getCouleur() == couleur)
        {
            victoire = true;
        }

        // Descendant
        Cercle *d1 = getCase(1, 1)->getCercles()[2];
        Cercle *d2 = getCase(2, 2)->getCercles()[1];
        Cercle *d3 = getCase(3, 3)->getCercles()[0];

        if (d1 && d2 && d3 &&
            d1->getCouleur() == couleur &&
            d2->getCouleur() == couleur &&
            d3->getCouleur() == couleur)
        {
            victoire = true;
        }
    }

    // ===== DIAGONALE SECONDAIRE ↙ ===== (3,1) (2,2) (1,3)
    {
        // Ascendant (dans l'ordre (3,1)->(2,2)->(1,3))
        Cercle *a1 = getCase(3, 1)->getCercles()[0];
        Cercle *a2 = getCase(2, 2)->getCercles()[1];
        Cercle *a3 = getCase(1, 3)->getCercles()[2];

        if (a1 && a2 && a3 &&
            a1->getCouleur() == couleur &&
            a2->getCouleur() == couleur &&
            a3->getCouleur() == couleur)
        {
            victoire = true;
        }

        // Descendant
        Cercle *d1 = getCase(3, 1)->getCercles()[2];
        Cercle *d2 = getCase(2, 2)->getCercles()[1];
        Cercle *d3 = getCase(1, 3)->getCercles()[0];

        if (d1 && d2 && d3 &&
            d1->getCouleur() == couleur &&
            d2->getCouleur() == couleur &&
            d3->getCouleur() == couleur)
        {
            victoire = true;
        }
    }

    return victoire;
}

/**
 * @brief Vérifie si l'une des cnditions de victoire est ok
 *
 * @return true
 * @return false
 */
bool Plateau::victoire(CouleurCercle couleur)
{
    if (victoireEmpilement(couleur))
    {
        std::cout << "Le cercle de couleur: " << couleur << "vient de réaliser un empilement de ses trois cercles." << std::endl;
        return true;
    }
    if (victoireAlignementIdentique(couleur))
    {
        std::cout << "La couleur: " << couleur << "vient de réaliser un alignement de ses 3 cercles de meme taille." << std::endl;
        return true;
    }
    if (victoireAlignementOrdonnee(couleur))
    {
        std::cout << "La couleur: " << couleur << "vient de réaliser un alignement de ses 3 cercles ordonnes." << std::endl;
        return true;
    }
    return false;
    std::cout << "la couleur" << couleur << "a gagné la partie" << std::endl;
}
