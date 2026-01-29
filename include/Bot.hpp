#pragma once
#include "Joueur.hpp"

class Bot : public Joueur
{
public:
    Bot(/* args */);

    Coup Jouer() override;
    int verifierColonne(int num);
};
