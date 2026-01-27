#pragma once

#include <iostream>
#include "CouleurCercle.hpp"
#include "Plateau.hpp"

class Joueur {
    private :
        
    protected:
        int IdJoueur;
        CouleurCercle  Couleur;

    public :
        // Constructeurs
        Joueur(int idJoueur, CouleurCercle c);

        virtual  Coup Jouer()=0; //propose un coup

        //getters
        int getIdJoueur();
        CouleurCercle getCouleur();
};


