#include <iostream>
#include "Joueur.hpp"


// Constructeurs
Joueur(int idJoueur, couleurCercle c){
    this->IdJoueur = idJoueur;
    this->Couleur = couleurCercle;
}


//getters
int getIdJoueur() {
    return this->IdJoueur;
}

couleurCercle getCouleur(){
    return this->Couleur;
}