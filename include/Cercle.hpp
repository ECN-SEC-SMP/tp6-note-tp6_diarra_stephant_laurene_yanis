#pragma once

#include <string>

#include "TailleCercle.hpp"
#include "CouleurCercle.hpp"

class Cercle
{
private:
    TailleCercle taille;
    CouleurCercle couleur;

public:
    // Constructeurs
    Cercle();
    Cercle(TailleCercle taille, CouleurCercle couleur);

    // Accesseurs
    TailleCercle getTaille();
    CouleurCercle getCouleur();

    // Mutateurs
    void setTaille(TailleCercle taille);
    void setCouleur(CouleurCercle couleur);

    // Méthodes
    void AffichageCercle(int Pos_X,int Pos_Y); // Compléter avec Case.hpp

    // Destructeurs
};