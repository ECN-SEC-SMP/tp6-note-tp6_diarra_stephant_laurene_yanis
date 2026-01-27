#pragma once
#include "Joueur.hpp"

class Bot : public Joueur
{
public:
    Bot(/* args */);

    void Jouer(Cercle* cercle, Case* caseCible) override;
};
