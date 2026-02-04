#pragma once
#include <iostream>
using namespace std;

#include "Cercle.hpp"
#include "Case.hpp"

class Coup {

private:
    Cercle *cercle;
    Case *caseCible;

public:

/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
    Coup();
    Coup(Cercle* cercle, Case* caseCible);
//-------------------------------------------------------------------------------*/
// Accesseurs
/*-------------------------------------------------------------------------------*/
    Cercle* getCercle();
    Case* getCaseCible();

};