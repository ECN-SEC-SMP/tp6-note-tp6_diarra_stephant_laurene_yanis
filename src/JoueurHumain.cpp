#include <iostream>
#include "JoueurHumain.hpp"
#include "Bot.hpp"

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
    // cercle d'origine
    Case* caseOrigine = nullptr;
    int caseColonneOrigine = 0;
    int caseLigneOrigine = 0;
    Bot* bot;

    while(retry){
        retry = 0;

        std::cout<<"Quel est ton coup ?"<<std::endl;
        std::cout<<"1 2 : colonne 1 & ligne 2 /!/ à l'espace"<<std::endl;
        std::cin>>colonne>>ligne; // il faut un espace = séparateur

        std::cout<<"Quelle taille de cercle ? (S:small M:medium L:large)"<<std::endl;
        std::cin>>taille; // espace = séparateur

        std::cout<<"Dans tes ressources, le cercle de quel case prends-tu (case(colonne ligne))) ? \n Exemple : 0 1 -> Un cercle de la case de la colonne 0 et de la ligne 1"<<std::endl;
        std::cin>>caseColonneOrigine>>caseLigneOrigine;

        // Conversion des tailles
        if(taille == "S") newTailleCercle = petite;
        else if(taille == "M") newTailleCercle = moyenne;
        else newTailleCercle = grande;

        // Case d'origine
        Case* caseOrigine = plateau->getCase(caseColonneOrigine, caseLigneOrigine);
        Cercle* cercle = bot->possedeCercle(newTailleCercle, &caseOrigine);

        
        // Vérification du respect des ensembles de définitions
        if((ligne>3 || ligne<=0)){
            std::cout<<"Ceci ne respecte pas l'ensemble de définition : 1-2-3"<<std::endl;
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
        
        // vérif la disponibilité de la case cible
        if(plateau->getCase(colonne, ligne)->getCercles()[static_cast<int>(newTailleCercle)] != nullptr){
            std::cout<<"La case cible n'est pas disponible ! Réessayer !"<<std::endl;
            coupDejaFait = 1;
        }

        // Tester la case/cercle d'origine
        if (cercle == nullptr || caseOrigine == nullptr) {
            std::cout<<"Vous ne disposez pas d'un tel cercle dans vos ressources !"<<std::endl;
            retry=1;
        } 
        if (cercle->getCouleur() != this->getCouleur()) {
            std::cout << "Ce cercle ne t'appartient pas"<<std::endl;
            retry = 1;
        }

        if(ligne<3 && ligne>=0 && colonne<3 && colonne>=0 && (taille=="S" || taille=="M" || taille=="L") && !(coupDejaFait)){
            retry = 0;
        }
    }
    // si la propal est bonne, l'enregistrer

    std::cout<<"Votre coup est bien enregistré"<<std::endl;
    Cercle* cercleCible = plateau->getCase(colonne, ligne)->getCercles()[newTailleCercle]; // cercle cible
    Case* caseCible = plateau->getCase(colonne, ligne);  // case cible
    Coup newCoup(caseOrigine, cercleCible, caseCible);

    return newCoup;
}


