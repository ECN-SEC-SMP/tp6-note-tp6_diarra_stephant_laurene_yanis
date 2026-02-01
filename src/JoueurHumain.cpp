#include <iostream>
#include "JoueurHumain.hpp"

JoueurHumain::JoueurHumain() {
    
}

Coup JoueurHumain::Jouer() {
    bool retry = 1;
    while(retry){
        retry = 0;
        int ligne=0; 
        int colonne=0;
        std::cout<<"Quel est ton coup ?"<<std::endl;
        std::cout<<"1 2 : colonne 1 & ligne 2"<<std::endl;
        std::cin>>colonne>>ligne; // espace = séparateur

        std::string taille=0;
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
    }

}