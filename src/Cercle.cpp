#include "Cercle.hpp"
#include <iostream>
#include <string>

// Constructeurs
Cercle::Cercle()
{
    this->taille = TailleCercle::petite;
    this->couleur = CouleurCercle::rouge;
}

Cercle::Cercle(TailleCercle taille, CouleurCercle couleur)
{
    this->taille = taille;
    this->couleur = couleur;
}

// Accesseurs
TailleCercle Cercle::getTaille()
{
    return taille;
}

CouleurCercle Cercle::getCouleur()
{
    return couleur;
}

// Mutateurs
void Cercle::setTaille(TailleCercle taille)
{
    this->taille = taille;
}

void Cercle::setCouleur(CouleurCercle couleur)
{
    this->couleur = couleur;
}

// Méthodes
void Cercle::AffichageCercle(int Pos_X, int Pos_Y)
{
    switch (taille)
    {
    case TailleCercle::petite:
        for (int i = Pos_X - 2; i <= Pos_X + 2; i++)
        {
            for (int j = Pos_Y - 2; j <= Pos_Y + 2; j++)
            {
                if (i == Pos_X-2 && j == Pos_Y-2) { std::cout << "╔"; } else if (i == Pos_X+2 && j == Pos_Y-2) { std::cout <<}
            }
        }
    }"═"
    break;
case TailleCercle::moyenne:

    break;
case TailleCercle::grande:

    break;
}
}