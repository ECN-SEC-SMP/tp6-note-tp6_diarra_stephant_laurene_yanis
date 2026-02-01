#pragma once
#include <iostream>
#include "Joueur.hpp"

class JoueurHumain : public Joueur
{
private:
public:
    Coup Jouer() override;
    JoueurHumain::JoueurHumain( Plateau *p, CouleurCercle c,int id)
        : Joueur(p, c, id)
    {
    }
};
