#pragma once

#include "Cercle.hpp"
#include "Case.hpp"

class Coup {

private:
    Case *origine;
    Cercle *cercle;
    Case *caseCible;

public:

/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
    Coup();
    Coup(Case* origine, Cercle* cercle, Case* caseCible);
//-------------------------------------------------------------------------------*/
// Accesseurs
/*-------------------------------------------------------------------------------*/
    Case* getOrigine();
    Cercle* getCercle();
    Case* getCaseCible();

};