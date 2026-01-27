#include <cstdlib> // Pour rand et srand

#include <iostream>
using namespace std;


#include "Controleur.hpp"
#include "Coup.hpp"
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
    joueurCouant = (joueurCouant + 1) % nbrJoueur; //passe au joueur suivant de façon circulaire
}

void Controleur::jouerCoup(Joueur*joueur){
    Coup propal;
    propal = joueur->Jouer(); //récupère le coup proposé par le joueur
    bool coupValide;
    coupValide = plateau->placerCercle(propal.getCercle(), propal.getCaseCible()); //vérifie si le coup est valide
    //Si le coup est valide, je place le cercle sur la case cible
    //si le coup n'est pas valide, je demanande au joueur de rejouer
    if (coupValide){
        plateau->placerCercle(propal.getCercle(), propal.getCaseCible()); //place le cercle sur la case cible dans la case cible
        propal.getCaseCible()->AffichageCase();
    }
    else{
        cout << "Coup invalide, veuillez rejouer." << endl;
        jouerCoup(joueur);
}
}

void Controleur::gererTour(){
    for(int i = 0; i<nbrJoueur; i++){
        cout << "C'est au joueur " << joueurs[joueurCouant]->getIdJoueur() << " de jouer." << endl;
        jouerCoup(joueurs[joueurCouant]);
    }
}
void Controleur::runPartie(){
    //Détermination du premier joueur de façon aléatoire
    srand(time(NULL));
    joueurCouant = rand() % nbrJoueur; //génére soit 0, 1, 2 ,3de façon aléatoire
    while (!partieTerminee){
        plateau->Affichage(); //affiche le plateau
        gererTour(); //gère le tour du joueur courant
        //vérifie s'il y a victoire après chaque tour
        if (plateau->victoire(joueurs[joueurCouant]->getCouleur())){
            partieTerminee = true;
            cout << "Le joueur " << joueurs[joueurCouant]->getIdJoueur() << " a gagné !" << endl;
        }
        else{
            nextJoueur(); //passe au joueur suivant
        }
    }
}
