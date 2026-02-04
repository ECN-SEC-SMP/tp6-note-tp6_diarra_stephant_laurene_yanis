#include <iostream>
#include "Joueur.hpp"


// Constructeurs
/**
 * @brief Constructeur de la classe Joueur
 *
 * Initialise les attributs communs à tous les joueurs :
 * le plateau, la couleur et l'identifiant.
 */
Joueur::Joueur(Plateau* plateau, CouleurCercle c, int id){
    this->plateau = plateau;
    this->Couleur = c;
    this-> idJoueur= id;
}


//getters
/**
 * @brief Retourne la couleur du joueur
 *
 * @return Couleur du joueur
 */
CouleurCercle Joueur::getCouleur()const {
    return this->Couleur;
}


/**
 * @brief Retourne l'identifiant du joueur
 *
 * @return Identifiant du joueur
 */
int Joueur::getIdJoueur()const {
    return this->idJoueur;
}