#pragma once

#include "Case.hpp"

class Plateau
{
private:
    Case* cases[5][5]; //Plateau 5*5 pour les pièces qui ne sont pas encore en jeu

public:
    // Constructeurs
    Plateau();
    ~Plateau();

    // Accesseurs
    Case* getCase(int x, int y);

    // Méthodes
    void Affichage();
    bool placerCercle(Cercle* cercle, Case* cible);
    bool victoire(CouleurCercle couleur);

    // Destructeurs
};