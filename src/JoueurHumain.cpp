#include <iostream>
#include "JoueurHumain.hpp"

// constructeur
JoueurHumain::JoueurHumain(Plateau *p, CouleurCercle c,int id) : Joueur(p, c, id) {
    this->plateau = p;
    this->Couleur = c;
    this->idJoueur = id;
}

JoueurHumain::~JoueurHumain() = default;

Coup JoueurHumain::Jouer()  {
    bool retry = 1;
    Cercle* newCercle;
    Case* newCaseCible;
    Coup newCoup(newCercle, newCaseCible);
    bool coupDejaFait = 0;
    TailleCercle newTailleCercle;

    while(retry){
        retry = 0;
        int ligne=0; 
        int colonne=0;
        std::cout<<"Quel est ton coup ?"<<std::endl;
        std::cout<<"1 2 : colonne 1 & ligne 2"<<std::endl;
        std::cin>>colonne>>ligne; // espace = séparateur

        std::string taille;
        std::cout<<"Quelle taille ? S:small M:medium L:large"<<std::endl;
        std::cin>>taille; // espace = séparateur


        if((ligne>3 || ligne<=0)){
            std::cout<<"Il faut réunir votre équipe avant d'aller plus loin"<<std::endl;
            retry=1;
        }
        if((colonne>3 || colonne<=0)){
            std::cout<<"Ceci ne respecte pas l'ensemble de définition : 1-2-3"<<std::endl;
            retry=1;
        }
        if(taille!="S" && taille!="M" && taille!="L"){
            std::cout<<"Veuillez respecter l'ensemble de définition : S-M-L"<<std::endl;
            retry=1;
        }

        // vérif la disponibilité
        if(plateau->getCase(colonne, ligne)->getCercles()[static_cast<int>(newTailleCercle)] != nullptr){
            coupDejaFait = 1;
        }

        // si la propal est bonne, l'enregistrer
        if(ligne<3 && ligne>=0 && colonne<3 && colonne>=0 && (taille=="S" || taille=="M" || taille=="L") && !(coupDejaFait)){
            if(taille == "S") newTailleCercle = petite;
            else if(taille == "M") newTailleCercle = moyenne;
            else newTailleCercle = grande;

            std::cout<<"Votre coup est bien enregistré"<<std::endl;
            newCercle->setTaille(newTailleCercle);
            newCaseCible->setPosX(colonne);
            newCaseCible->setPosY(ligne);
        }

    }
    return newCoup;
}