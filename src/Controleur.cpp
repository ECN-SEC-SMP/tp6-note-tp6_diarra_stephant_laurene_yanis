#include <iostream>
using namespace std;


#include "Controleur.hpp"
/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
Controleur::Controleur() {
    nbrJoueur = 0;
    plateau = nullptr;
    joueurCouant = 0;
    partieTerminee = false;
}

Controleur::Controleur(int nbrJoueurs, Plateau* plateau, Joueur* joueurs[]) {
    this->nbrJoueur = nbrJoueurs;
    this->plateau = plateau;
    this->joueurCouant = 0;
    for (int i = 0; i < nbrJoueurs; i++) {
        this->joueurs[i] = joueurs[i];
    }
    partieTerminee = false;
}
/*-------------------------------------------------------------------------------*/
// Getters
/*-------------------------------------------------------------------------------*/

int Controleur::getNbrJoueur() {
    return nbrJoueur;
}

Plateau* Controleur::getPlateau() {
    return plateau;
}

int Controleur::getJoueurCourant() {
    return joueurCouant;
}

Joueur* Controleur::getJoueurs(int i) {
    return joueurs[i];
}

Joueur* Controleur::getlistJoueurs() {
    for(int i=0; i<nbrJoueur; i++){
        return joueurs[i];
    }
}
/*-------------------------------------------------------------------------------*/
// Setters
/*-------------------------------------------------------------------------------*/
void Controleur::setNbrJoueur(int nbrJoueurs) {
    nbrJoueur = nbrJoueurs;
}

void Controleur::setPlateau(Plateau* plateau) {
    this->plateau = plateau;
}

void Controleur::setJoueurCourant(int joueurCourant) {
    joueurCouant = joueurCourant;
}
/*-------------------------------------------------------------------------------*/
// Méthodes de la classe
/*-------------------------------------------------------------------------------*/
void Controleur::nextJoueur() {
    joueurCouant = (joueurCouant + 1) % nbrJoueur;
}

void Controleur::jouerCoup(Joueur*joueur){



}
void Controleur::gererTour(){

}
void Controleur::runPartie(){

}