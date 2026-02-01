#include <iostream>
#include "Joueur.hpp"


// Constructeurs
Joueur::Joueur(Plateau* plateau, CouleurCercle c, int id){
    this->plateau = plateau;
    this->Couleur = c;
    this-> idJoueur= id;
}

//getters
CouleurCercle Joueur::getCouleur()const {
    return this->Couleur;
}

int Joueur::getIdJoueur()const {
    return this->idJoueur;
}