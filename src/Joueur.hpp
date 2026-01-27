#pragma once

#include <iostream>
#include "CouleurCercle.hpp"
#include "Plateau.hpp"

class Joueur {
    private :
        int IdJoueur;
        int tour;
        CouleurCercle  Couleur;
        bool victoire;
        Plateau * plateau;

    public :
        // Constructeurs
        Joueur();
        Joueur(int idJoueur, CouleurCercle couleur);

        virtual  void Jouer(Cercle* cercle, Case* caseCible);

        //getters
        int getIdJoueur();
        int getTour();
        int getDeplacement();
        std::string getCouleur();
        bool getVictoire();
};


