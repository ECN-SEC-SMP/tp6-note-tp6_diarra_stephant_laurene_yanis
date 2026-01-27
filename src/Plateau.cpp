#include <cassert>

#include "Case.hpp"
#include "Plateau.hpp"

// Constructeurs
Plateau::Plateau() {        
    //Instancier toutes les cases du plateau
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 5; x++) {
            //Ne pas instancier les coins
            if((y == 0 || y == 4) && (x == 0 || x == 4)) {
                continue;
            }

            cases[x][y] = new Case(x, y);
        }
    }
}

Plateau::~Plateau() {
    //Détruire toutes les instances de case
    for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
            Case* c = cases[x][y];
            if(c) {
                delete c;
            }
        }
    }
}

// Accesseur
Case* Plateau::getCase(int x, int y) {
    //Validation des entrées
    assert(x >= 0 && x<5);
    assert(y >= 0 && y<5);
    return cases[x][y];
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
