#include <iostream>
#include "Joueur.hpp"


// Constructeurs
Joueur::Joueur(Plateau* plateau, CouleurCercle c){
    this->plateau = plateau;
    this->Couleur = c;
}


//getters

CouleurCercle Joueur::getCouleur(){
    return this->Couleur;
}