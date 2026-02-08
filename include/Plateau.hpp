#pragma once

#include "Case.hpp"
#include "Coup.hpp"

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
    bool placerCercle(Coup coup);
    bool victoireEmpilement(CouleurCercle couleur);
    bool victoireAlignementIdentique(CouleurCercle couleur);
    bool victoireAlignementOrdonnee(CouleurCercle couleur);
    bool victoire(CouleurCercle couleur);

    // Destructeurs
};