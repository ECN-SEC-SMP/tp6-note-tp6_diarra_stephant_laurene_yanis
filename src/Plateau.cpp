#include <string>
#include <vector>

#include "Case.hpp"
#include "Plateau.hpp"

// Constructeurs
Plateau::Plateau() {        
    this->l = 3;
    this->L = 3;
}

Plateau::Plateau(int l, int L) {
    this->l = l;
    this->L = L;
}

// Accesseurs
int Plateau::getLongueur() {
    return L;
}

int Plateau::getLargeur() {
    return l;
}

Case* Plateau::getCase(int x, int y) {
    return cases[x][y];
}

// Mutateurs
void Plateau::setLongueur(int L) {
    this->L = L;
}

void Plateau::setLargeur(int l) {
    this->l = l;
}

void Plateau::setCase(int x, int y, Case* c) {
    ;
}

// Méthodes
void Plateau::Affichage() {
    ;
}

bool Plateau::placerCercle(Cercle* cercle, Case* cible) {
    ;
}

bool Plateau::victoire(CouleurCercle couleur) {
    ;
}
