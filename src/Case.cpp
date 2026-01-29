#include <string>
#include <array>
#include <iostream>

#include "Cercle.hpp"
#include "Case.hpp"

// Constructeurs
Case::Case()
{
    this->Pos_X = 0;
    this->Pos_Y = 0;
    this->cercles = {nullptr, nullptr, nullptr};
}

Case::Case(int Pos_X, int Pos_Y)
{
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;
    this->cercles = {nullptr, nullptr, nullptr};
}

// Accesseurs
int Case::getPosX()
{
    return Pos_X;
}

int Case::getPosY()
{
    return Pos_Y;
}

std::array<Cercle *, 3> Case::getCercles()
{
    return cercles;
}

// Mutateurs
void Case::setPosX(int Pos_X)
{
    this->Pos_X = Pos_X;
}

void Case::setPosY(int Pos_Y)
{
    this->Pos_Y = Pos_Y;
}

void Case::setCercles(Cercle *cercle, int index)
{
    this->cercles[index] = cercle;
}

// Méthodes

void Case::AffichageCase(int Pos_X, int Pos_Y)
{
    // Pour que les cases soient séparéées les unes des autres
    Pos_X = (Pos_X) * 13;
    Pos_Y = (Pos_Y) * 13;

    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;

    // Les codes ANSI ne font pas ce que j'attend. 
    //J'ai l'impression qu'il faut génerer un plateau de caractères vides avant d'afficher les cases

    for (int i = Pos_X; i <= Pos_X + 7; i++)
    {
        for (int j = Pos_Y; j <= Pos_Y + 7; j++)
        {
            std::cout << "X";
        }
        std::cout << "\033[" << Pos_X + 1 << ";" << Pos_Y << "H";
    }

    //std::cout << std::endl; // Seule ligne qui permet d'afficher + que 5 cases lol
    // Affichage de la case en stockant dans le buffer
    /*
            if (i == Pos_X && j == Pos_Y)
            {
                std::cout << "┌──────────┐" << "\033[1E";
            }
            else if (i == Pos_X && j == Pos_Y + 1)
            {
                std::cout << "│          │";
            }
            else if (i == Pos_X && j == Pos_Y + 2)
            {
                std::cout << "│          │";
            }
            else if (i == Pos_X && j == Pos_Y + 3)
            {
                std::cout << "│          │";
            }
            else if (i == Pos_X && j == Pos_Y + 4)
            {
                std::cout << "│          │";
            }
            else if (i == Pos_X && j == Pos_Y + 5)
            {
                std::cout << "│          │";
            }
            else if (i == Pos_X && j == Pos_Y + 6)
            {
                std::cout << "└──────────┘" << "\033[0m";
            }

            // Affichage des cercles ensuite
            for (int idx = 0; idx < cercles.size(); idx++)
            {
                if (cercles[idx] != nullptr)
                {
                    // cercles[idx]->AffichageCercle(Pos_x, Pos_y);
                }
            }
        }
    }

    */
}
// buffer[startLine + (i - Pos_X)] += ligne;

// Destructeurs
Case::~Case()
{
    for (Cercle *cercle : cercles)
    {
        if (cercle != nullptr)
        {
            delete cercle;
            cercle = nullptr;
        }
    }
}