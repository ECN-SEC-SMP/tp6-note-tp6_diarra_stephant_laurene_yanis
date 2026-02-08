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
void Cercle::AffichageCercle(int Pos_X, int Pos_Y)  // Affichage cercle en fonction de sa taille et de sa couleur
{
    std::string couleurCase;
    switch (couleur)
    {
    case CouleurCercle::bleu:
        couleurCase = "\033[34m";
        break;
    case CouleurCercle::jaune:
        couleurCase = "\033[33m";
        break;
    case CouleurCercle::rouge:
        couleurCase = "\033[31m";
        break;
    case CouleurCercle::vert:
        couleurCase = "\033[32m";
        break;
    default:
        couleurCase = "\033[40m";
        break;
    }
    switch (taille)
    {
    case TailleCercle::moyenne:
        std::cout << "\033[" << Pos_X + 1 << ";" << Pos_Y + 1 << "H" << "X";
        for (int i = Pos_X + 1; i <= Pos_X + 5; i++)
        {
            for (int j = Pos_Y + 1; j <= Pos_Y + 8; j++)
            {
                if (i == Pos_X + 2 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╔" << "\033[0m";
                }
                else if (i == Pos_X + 2 && j == Pos_Y + 8)
                {
                    std::cout << couleurCase << "╗" << "\033[0m";
                }
                else if (i == Pos_X + 5 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╚" << "\033[0m";
                }
                else if (i == Pos_X + 5 && j == Pos_Y + 8)
                {
                    std::cout << couleurCase << "╝" << "\033[0m";
                }
                else if ((j == Pos_Y + 1 || j == Pos_Y + 8) && i == Pos_X + 3)
                {
                    std::cout << couleurCase << "║" << "\033[0m";
                }
                else if (i == Pos_X + 2 || i == Pos_X + 5)
                {
                    std::cout << couleurCase << "═" << "\033[0m";
                }
                else
                {
                    std::cout << " " << "\033[0m";
                }
            }
            std::cout << "\033[" << i << ";" << Pos_Y + 1 << "H";
        }
        break;
    case TailleCercle::grande:
        std::cout << "\033[" << Pos_X << ";" << Pos_Y << "H";
        for (int i = Pos_X; i <= Pos_X + 6; i++)
        {
            for (int j = Pos_Y; j <= Pos_Y + 9; j++)
            {
                if (i == Pos_X + 6 && j == Pos_Y)
                {
                    std::cout << couleurCase << "╚" << "\033[0m";
                }
                else if (i == Pos_X + 6 && j == Pos_Y + 9)
                {
                    std::cout << couleurCase << "╝" << "\033[0m";
                }
                else if (i == Pos_X + 1 && j == Pos_Y)
                {
                    std::cout << couleurCase << "╔" << "\033[0m";
                }
                else if (i == Pos_X + 1 && j == Pos_Y + 9)
                {
                    std::cout << couleurCase << "╗" << "\033[0m";
                }
                else if (j == Pos_Y || j == Pos_Y + 9)
                {
                    std::cout << couleurCase << "║" << "\033[0m";
                }
                else if (i == Pos_X + 6 || i == Pos_X + 1)
                {
                    std::cout << couleurCase << "═" << "\033[0m";
                }
                else
                {
                    std::cout << " " << "\033[0m";
                }
            }
            std::cout << "\033[" << i << ";" << Pos_Y << "H";
        }
        break;
    case TailleCercle::petite:
        std::cout << "\033[" << Pos_X + 2 << ";" << Pos_Y + 2 << "H" << couleurCase << "\033[0m";

        for (int i = Pos_X + 2; i <= Pos_X + 4; i++)
        {
            for (int j = Pos_Y; j <= Pos_Y + 4; j++)
            {

                if (i == Pos_X + 4 && j == Pos_Y)
                {
                    std::cout << couleurCase << "╚" << "\033[0m";
                }
                else if (i == Pos_X + 4 && j == Pos_Y + 4)
                {
                    std::cout << couleurCase << "╝" << "\033[0m";
                }
                else if (i == Pos_X + 3 && j == Pos_Y)
                {
                    std::cout << couleurCase << "╔" << "\033[0m";
                }
                else if (i == Pos_X + 3 && j == Pos_Y + 4)
                {
                    std::cout << couleurCase << "╗" << "\033[0m";
                }
                else
                {
                    std::cout << couleurCase << "═" << "\033[0m";
                }
            }
            std::cout << "\033[" << i << ";" << Pos_Y + 2 << "H";
        }
        break;
    }
}
