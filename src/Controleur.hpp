#pragma once
#include <string>

#include "Plateau.hpp"
#include "Joueur.hpp"



class Controleur {
    private:
    int nbrJoueur;
    Plateau *plateau;
    int joueurCouant;
    Joueur * joueurs[nbrJoueur];



    public:
    // Constructeurs
    Controleur();
    
    Controleur(int nbrJoueurs, Plateau* plateau, Joueur* joueurs[]);

    // Getters
    int getNbrJoueur();

    Plateau* getPlateau();

    int getJoueurCourant();

    Joueur* getJoueurs(int i);

    Joueur* getlistJoueurs();

    // Setters
    void setNbrJoueur(int nbrJoueurs);

    void setPlateau(Plateau* plateau);

    void setJoueurCourant(int joueurCourant);



    // Méthodes de la classe
    bool verifierVictoire();

    bool verifierDeplacement();


    Plateau updatePlateau(Cercle *cercle, Case *Case);

    void GérerTour(); //choix joueur + gestion de son tour

    // Destructeur
    ~Controleur();
};