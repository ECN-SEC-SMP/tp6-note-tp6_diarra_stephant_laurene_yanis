#include <string>
#include <array>

#include "Cercle.hpp"
#include "Case.hpp"

// Constructeurs
Case::Case() {
    this->Pos_X = 0;
    this->Pos_Y = 0;
}

Case::Case(int Pos_X, int Pos_Y) {
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;
    this->cercles = cercles;
}

// Accesseurs
int Case::getPosX() {
    return Pos_X;
}

int Case::getPosY() {
    return Pos_Y;
}

// Mutateurs
void Case::setPosX(int Pos_X) {
    this->Pos_X = Pos_X;
}

void Case::setPosY(int Pos_Y) {
    this->Pos_Y = Pos_Y;
}

// Méthodes
void Case::AffichageCase() {
    ;
}