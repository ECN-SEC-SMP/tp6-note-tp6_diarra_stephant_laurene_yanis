#pragma once
#include <string>

#include "Plateau.hpp"
#include "Joueur.hpp"


class Controleur {

    private:
    int nbrJoueur;
    Plateau *plateau;
    int joueurCouant;
    Joueur * joueurs[ 4 ];
    bool partieTerminee;

    public:

/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
    Controleur();
    Controleur(int nbrJoueurs, Plateau* plateau, Joueur* joueurs[]);

/*-------------------------------------------------------------------------------*/
// Getters
/*-------------------------------------------------------------------------------*/
    int getNbrJoueur();

    Plateau* getPlateau();

    int getJoueurCourant();

    Joueur* getJoueurs(int i);

    Joueur* getlistJoueurs();

/*-------------------------------------------------------------------------------*/
// Setters
/*-------------------------------------------------------------------------------*/
    void setNbrJoueur(int nbrJoueurs);

    void setPlateau(Plateau* plateau);

    void setJoueurCourant(int joueurCourant);


/*-------------------------------------------------------------------------------*/
// Méthodes de la classe
/*-------------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
    void runPartie();

/**
 * @brief Sélectionne le joueur suivant
 * 
 */
    void nextJoueur();

/**
 * @brief gère le tour du joueur courant
 * 
 */
    void gererTour(); //choix joueur + gestion de son tour
    
/**
 * @brief Vérifie via le plateau si le coup proposé par le joueur est valide
 * Si le coup est valide, le coup est joué sur le plateau
 * sinon on demande au joueur de rejouer
 * @param joueur 
 */
    void jouerCoup(Joueur* joueur); //gestion du coup joué par le joueur

    // Destructeur
    ~Controleur();
};