#include "Cercle.hpp"
#include <iostream>

// Constructeurs
Cercle::Cercle() {
    this->taille = TailleCercle::petite;
    this->couleur = CouleurCercle::rouge;
}

Cercle::Cercle(TailleCercle taille, CouleurCercle couleur) {
    this->taille = taille;
    this->couleur = couleur;
}

// Accesseurs
TailleCercle Cercle::getTaille()
{
    return taille;
}

CouleurCercle Cercle::getCouleur()
{
    return couleur;
}

// Mutateurs
void Cercle::setTaille(TailleCercle taille)
{
    this->taille = taille;
}

void Cercle::setCouleur(CouleurCercle couleur)
{
    this->couleur = couleur;
}

// Méthodes
void Cercle::AffichageCercle(int Pos_X, int Pos_Y)
{
    
}
