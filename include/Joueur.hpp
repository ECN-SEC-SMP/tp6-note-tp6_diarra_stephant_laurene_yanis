#pragma once

#include <iostream>
#include "CouleurCercle.hpp"
#include "Plateau.hpp"

class Joueur {
    private :
        
    protected:
        int IdJoueur;
        couleurCercle  Couleur;

    public :
        // Constructeurs
        Joueur(int idJoueur, couleurCercle c);

        virtual  void Jouer(Cercle* cercle, Case* cible); //propose un coup

        //getters
        int getIdJoueur();
        couleurCercle getCouleur();
};


