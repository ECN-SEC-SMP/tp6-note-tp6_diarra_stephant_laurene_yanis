#pragma once

#include <string>
#include <vector>

#include "Case.hpp"

class Plateau
{
private:
    int l = 0;
    int L = 0;
    
    Case* cases[3][3];  // Pas possible de faire un tableau dynamique avec l et L
    std::vector<std::vector<Case*>> cases1;  // Proposition Copilot

public:
    // Constructeurs
    Plateau();
    Plateau(int l, int L);

    // Accesseurs
    int getLongueur();
    int getLargeur();
    Case* getCase(int x, int y);

    // Mutateurs
    void setLongueur(int L);
    void setLargeur(int l);
    void setCase(int x, int y, Case* c);    // ?

    // Méthodes
    void Affichage();
    bool placerCercle(Cercle* cercle, Case* cible);
    bool victoire(CouleurCercle couleur);

    // Destructeurs
};