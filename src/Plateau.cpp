#include <cassert>
#include <iostream>

#include "Case.hpp"
#include "CouleurCercle.hpp"
#include "TailleCercle.hpp"
#include "joueur.hpp"
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
              << std::endl;
}

bool Plateau::placerCercle(Cercle *cercle, Case *cible)
{
    // TODO: STUB
    return false;
}

/**
 * @brief Vérifie s'il y a empilement de trois cercles de la meme couleur sur une case
 *
 * @return true
 * @return false
 */
bool Plateau::victoireEmpilement(CouleurCercle couleur)
{
    bool empilement;
    Case *laCase;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            laCase = this->getCase(i, j); // parcours de toutes les cases du tableau
            uint8_t count[4] = {0};
            for (Cercle *cercle : laCase->getCercles()) // parcours des cercles dans la case
            {
                if (cercle)
                {
                    count[cercle->getCouleur()]++;
                    if (count[cercle->getCouleur()] == 3)
                    {
                        empilement = true;
                        return empilement;
                    }
                }
            }
        }
    }
}
bool Plateau::victoireAlignementIdentique(CouleurCercle couleur)
{
    


}
bool Plateau::victoireAlignementOrdonnee(CouleurCercle couleur){

}
bool Plateau::victoire(CouleurCercle couleur)
{
    bool victoire;
    if (victoireEmpilement(couleur))
    {
        std::cout << "Le cercle de couleur: " << couleur << "vient de réaliser un empilement de ses trois cercles." << std::endl;
        victoire = true;
    }
    if (victoireAlignementIdentique(couleur))
    {
        std::cout << "La couleur: " << couleur << "vient de réaliser un alignement de ses 3 cercles de meme taille." << std::endl;
        victoire = true;
    }
    if(victoireAlignementOrdonnee(couleur)){
        std::cout << "La couleur: " << couleur << "vient de réaliser un alignement de ses 3 cercles ordonnes." << std::endl;
        victoire = true;

    }
    else{
        victoire= false;
    }
    std::cout << "la couleur" << couleur << "a gagné la partie" << std::endl;

    return victoire;
}
