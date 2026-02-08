#include <iostream>
#include "JoueurHumain.hpp"

// constructeur

/**
 * @brief Constructeur de JoueurHumain
 *
 * Initialise un joueur humain en appelant le constructeur
 * de la classe mère Joueur.
 */
JoueurHumain::JoueurHumain(Plateau *p, CouleurCercle c, int id) : Joueur(p, c, id) {
    this->plateau = p;
    this->Couleur = c;
    this->idJoueur = id;
}




/**
 * @brief Méthode permettant au joueur humain de jouer un coup
 *
 * La méthode demande à l'utilisateur :
 * - la position de la case (ligne, colonne)
 * - la taille du cercle (S, M ou L)
 *
 * Elle vérifie :
 * - que les coordonnées sont valides
 * - que la taille est correcte
 * - que la case est disponible pour la taille choisie
 *
 * @return Coup valide créé à partir des entrées utilisateur
 */
Coup JoueurHumain::Jouer()  {
    bool retry = 1;
    bool coupDejaFait = 0;
    TailleCercle newTailleCercle;
    int ligne=0; 
    int colonne=0;
    std::string taille;

    while(retry){
        retry = 0;
        
        std::cout<<"Quel est ton coup ?"<<std::endl;
        std::cout<<"1 2 : colonne 1 & ligne 2 /!/ à lespace"<<std::endl;
        std::cin>>colonne>>ligne; // il faut un espace = séparateur

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

        if(ligne<3 && ligne>=0 && colonne<3 && colonne>=0 && (taille=="S" || taille=="M" || taille=="L") && !(coupDejaFait)){
            retry = 0;
        }
    }
    // si la propal est bonne, l'enregistrer
    if(taille == "S") newTailleCercle = petite;
    else if(taille == "M") newTailleCercle = moyenne;
    else newTailleCercle = grande;

    std::cout<<"Votre coup est bien enregistré"<<std::endl;
    Cercle* c1 = plateau->getCase(colonne, ligne)->getCercles()[newTailleCercle];
    Case* c2 = plateau->getCase(colonne, ligne);
    Coup newCoup(plateau->getCase(colonne, ligne), c1, c2);

    return newCoup;
}