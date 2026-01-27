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

std::array<Cercle*,3> Case::getCercles()
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

void Case::setCercles(Cercle* cercle, int index)
{
    this->cercles[index] = cercle;
}

// Méthodes
void Case::AffichageCase()
{
    int Pos_x = this->Pos_X;
    int Pos_y = this->Pos_Y;
    // Affichage de la case en premier
    for (int i = Pos_X; i <= Pos_X + 6; i++)
    {
        for (int j = Pos_Y; j <= Pos_Y + 6; j++)
        {
            if (i == Pos_X && j == Pos_Y)
            {
                std::cout << "┌";
            }
            else if (i == Pos_X + 6 && j == Pos_Y)
            {
                std::cout << "┐";
            }
            else if (i == Pos_X && j == Pos_Y + 6)
            {
                std::cout << "└";
            }
            else if (i == Pos_X + 6 && j == Pos_Y + 6)
            {
                std::cout << "┘";
            }
            else if (j == Pos_Y || j == Pos_Y + 6)
            {
                std::cout << "─";
            }
            else if (i == Pos_X || i == Pos_X + 6)
            {
                std::cout << "│";
            }
            else
            {
                std::cout << " ";
            }
        }
    };

    // Affichage des cercles ensuite
    for (int idx = 0; idx < cercles.size(); idx++)
    {
        if (cercles[idx] != nullptr) {
            cercles[idx]->AffichageCercle(Pos_x, Pos_y);    // Pas d'affichage si le contenu de l'array à l'index idx est vide (nullptr)
        }
    }
}

// Destructeurs
Case::~Case()
{
    for (Cercle* cercle : cercles)
    {
        if (cercle != nullptr)
        {
            delete cercle;
            cercle = nullptr;
        }
    }
}