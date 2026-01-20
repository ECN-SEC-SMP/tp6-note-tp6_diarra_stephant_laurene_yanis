#pragma once

#include <string>

#include "Case.hpp"

class Plateau
{
private:
    int l;
    int L;
    
public:
    // Constructeurs
    Plateau();
    Plateau(int l, int L);

    // Accesseurs
    int getLongueur();
    int getLargeur();

    // Mutateurs
    void setLongueur(int L);
    void setLargeur(int l);

    // Méthodes
    void Affichage();

    // Destructeurs
};