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
    std::string couleurCase;
    switch (couleur)
    {
    case CouleurCercle::bleu:
        couleurCase = "\033[44m";
        break;
    case CouleurCercle::jaune:
        couleurCase = "\033[43m";
        break;
    case CouleurCercle::rouge:
        couleurCase = "\033[41m";
        break;
    case CouleurCercle::vert:
        couleurCase = "\033[42m";
        break;
    default:
        couleurCase = "\033[41m";
        break;
    }

    switch (taille)
    {
    case TailleCercle::grande:
        for (int i = Pos_X - 2; i <= Pos_X + 2; i++)
        {
            for (int j = Pos_Y - 2; j <= Pos_Y + 2; j++)
            {
                if (i == Pos_X - 2 && j == Pos_Y - 2)
                {
                    std::cout << couleurCase << "╔";
                }
                else if (i == Pos_X + 2 && j == Pos_Y - 2)
                {
                    std::cout << couleurCase << "╗";
                }
                else if (i == Pos_X - 2 && j == Pos_Y + 2)
                {
                    std::cout << couleurCase << "╚";
                }
                else if (i == Pos_X + 2 && j == Pos_Y + 2)
                {
                    std::cout << couleurCase << "╝";
                }
                else if (j == Pos_Y - 2 || j == Pos_Y + 2)
                {
                    std::cout << couleurCase << "═";
                }
                else if (i == Pos_X - 2 || i == Pos_X + 2)
                {
                    std::cout << couleurCase << "║";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }
        break;
    case TailleCercle::moyenne:
        for (int i = Pos_X - 1; i <= Pos_X + 1; i++)
        {
            for (int j = Pos_Y - 1; j <= Pos_Y + 1; j++)
            {
                if (i == Pos_X - 1 && j == Pos_Y - 1)
                {
                    std::cout << couleurCase << "╔";
                }
                else if (i == Pos_X + 1 && j == Pos_Y - 1)
                {
                    std::cout << couleurCase << "╗";
                }
                else if (i == Pos_X - 1 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╚";
                }
                else if (i == Pos_X + 1 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╝";
                }
                else if (j == Pos_Y - 1 || j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "═";
                }
                else if (i == Pos_X - 1 || i == Pos_X + 1)
                {
                    std::cout << couleurCase << "║";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }
        break;
    case TailleCercle::petite:
        std::cout << couleurCase << "O";
        break;
    }
}