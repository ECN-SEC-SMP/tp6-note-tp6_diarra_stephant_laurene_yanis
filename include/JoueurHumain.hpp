#pragma once
#include <iostream>
#include "Joueur.hpp"



class JoueurHumain : public Joueur {
    private :
    public :
        Coup Jouer() override;
};
