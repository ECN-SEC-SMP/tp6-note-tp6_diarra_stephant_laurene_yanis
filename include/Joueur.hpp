#pragma once

#include "CouleurCercle.hpp"
#include "Coup.hpp"
#include "Plateau.hpp"

class Joueur {
        
    protected:
        CouleurCercle  Couleur;
        Plateau* plateau;

    public :
        // Constructeurs
        Joueur(Plateau* plateau, CouleurCercle c);

        virtual Coup Jouer()=0; //propose un coup

        //getters
        CouleurCercle getCouleur();
        int getIdJoueur();
};


