#include <iostream>
#include "Joueur.hpp"


// Constructeurs
Joueur::Joueur(int idJoueur, CouleurCercle c){
    this->IdJoueur = idJoueur;
    this->Couleur = c;
}


//getters
int Joueur::getIdJoueur() {
    return this->IdJoueur;
}

CouleurCercle Joueur::getCouleur(){
    return this->Couleur;
}