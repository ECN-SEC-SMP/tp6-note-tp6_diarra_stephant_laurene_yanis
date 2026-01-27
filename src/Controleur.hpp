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
    void runPartie();

    void nextJoueur();

    void gererTour(); //choix joueur + gestion de son tour

    void jouerCoup(Joueur* joueur); //gestion du coup joué par le joueur

    // Destructeur
    ~Controleur();
};