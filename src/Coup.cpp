#include "Coup.hpp"
/*-------------------------------------------------------------------------------*/
//Constructeurs
/*-------------------------------------------------------------------------------*/
Coup::Coup() {
    origine = nullptr;
    cercle = nullptr;
    caseCible = nullptr;
}
Coup::Coup(Case* origine, Cercle* cercle, Case* caseCible) {
    this->origine = origine;
    this->cercle = cercle;
    this->caseCible = caseCible;
}
/*-------------------------------------------------------------------------------*/
//Getters
/*-------------------------------------------------------------------------------*/
Case* Coup::getOrigine() {
    return origine;
}

Cercle* Coup::getCercle() {
    return cercle;
}
Case* Coup::getCaseCible() {
    return caseCible;
}