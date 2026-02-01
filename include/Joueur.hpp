#pragma once

#include "CouleurCercle.hpp"
#include "Coup.hpp"
#include "Plateau.hpp"

class Joueur {
        
    protected:
        CouleurCercle  Couleur;
        Plateau* plateau;
        int idJoueur;

    public :
        // Constructeurs
        Joueur(Plateau* plateau, CouleurCercle c, int id);
        virtual Coup Jouer()=0; //propose un coup

        //getters
        CouleurCercle getCouleur() const;
        int getIdJoueur()const ;
};


