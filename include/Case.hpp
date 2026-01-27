#pragma once

#include <string>
#include <array>

#include "Cercle.hpp"

class Case
{
private:
    int Pos_X;
    int Pos_Y;
    std::array<Cercle,3> cercles;

public:
    // Constructeurs
    Case();
    Case(int Pos_X, int Pos_Y);

    // Accesseurs
    int getPosX();
    int getPosY();

    // Mutateurs
    void setPosX(int Pos_X);
    void setPosY(int Pos_Y);

    // Méthodes
    void AffichageCase();

    // Destructeurs
};