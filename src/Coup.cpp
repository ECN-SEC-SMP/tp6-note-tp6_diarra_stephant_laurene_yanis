#include <iostream>
using namespace std;

#include "Coup.hpp"
/*-------------------------------------------------------------------------------*/
//Constructeurs
/*-------------------------------------------------------------------------------*/
Coup::Coup() {
    cercle = nullptr;
    caseCible = nullptr;
}
Coup::Coup(Cercle* cercle, Case* caseCible) {
    this->cercle = cercle;
    this->caseCible = caseCible;
}
/*-------------------------------------------------------------------------------*/
//Getters
/*-------------------------------------------------------------------------------*/
Cercle* Coup::getCercle() {
    return cercle;
}
Case* Coup::getCaseCible() {
    return caseCible;
}