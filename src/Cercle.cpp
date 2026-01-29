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
    for (int i = Pos_X; i <= Pos_X + 4; i++)
    {
        for (int j = Pos_Y; j <= Pos_Y + 4; j++)
        {
            switch (taille)
            {
            case TailleCercle::grande:
                if (i == Pos_X && j == Pos_Y)
                {
                    std::cout << couleurCase << "╔══════╗" << "\033[0m" << "\033[1B" << "\033[5D";
                }
                else if (i == Pos_X && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "║      ║" << "\033[0m" << "\033[1B" << "\033[5D";
                }
                else if (i == Pos_X && j == Pos_Y + 2)
                {
                    std::cout << couleurCase << "║      ║" << "\033[0m" << "\033[1B" << "\033[5D";
                }
                else if (i == Pos_X && j == Pos_Y + 3)
                {
                    std::cout << couleurCase << "║      ║" << "\033[0m" << "\033[1B" << "\033[5D";
                }
                else if (i == Pos_X && j == Pos_Y + 4)
                {
                    std::cout << couleurCase << "╚══════╝" << "\033[0m";
                }
                /*
                                if (i == Pos_X && j == Pos_Y)
                                {
                                    std::cout << couleurCase << "╔" << "\033[0m" ;
                                }
                                else if (i == Pos_X + 4 && j == Pos_Y)
                                {
                                    std::cout << couleurCase << "╗" << "\033[0m" << "\033[1B" << "\033[5D";
                                }
                                else if (i == Pos_X && j == Pos_Y + 4)
                                {
                                    std::cout << couleurCase << "╚" << "\033[0m";
                                }
                                else if (i == Pos_X + 4 && j == Pos_Y + 4)
                                {
                                    std::cout << couleurCase << "╝" << "\033[0m" << std::endl;
                                }
                                else if (j == Pos_Y || j == Pos_Y + 4)
                                {
                                    std::cout << couleurCase << "═" << "\033[0m";
                                }
                                else if (i == Pos_X || i == Pos_X + 4)
                                {
                                    std::cout << couleurCase << "║" << "\033[0m";
                                }
                                else
                                {
                                    std::cout << " ";
                                }
                */

                break;
            case TailleCercle::moyenne:

                if (i == Pos_X + 1 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╔" << "\033[0m";
                }
                else if (i == Pos_X + 3 && j == Pos_Y + 1)
                {
                    std::cout << couleurCase << "╗" << "\033[0m";
                }
                else if (i == Pos_X + 1 && j == Pos_Y + 3)
                {
                    std::cout << couleurCase << "╚" << "\033[0m";
                }
                else if (i == Pos_X + 3 && j == Pos_Y + 3)
                {
                    std::cout << couleurCase << "╝" << "\033[0m";
                }
                else if (j == Pos_Y + 1 || j == Pos_Y + 3)
                {
                    std::cout << couleurCase << "═" << "\033[0m";
                }
                else if (i == Pos_X + 1 || i == Pos_X + 3)
                {
                    std::cout << couleurCase << "║" << "\033[0m";
                }
                else if (i == Pos_X + 2 && j == Pos_Y + 2)
                {
                    std::cout << " ";
                }
                else
                {
                    ;
                }

                break;
            case TailleCercle::petite:
                if (i == Pos_X + 2 && j == Pos_Y + 2)
                {
                    std::cout << couleurCase << "O" << "\033[0m";
                }
                break;
            }
        }
    }
}