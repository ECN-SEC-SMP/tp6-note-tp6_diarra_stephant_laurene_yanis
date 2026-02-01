#pragma once
#include <string>

#include "Plateau.hpp"
#include "Joueur.hpp"


class Controleur {

    private:
    int nbrJoueur;
    Plateau *plateau;
    int joueurCouant;
    Joueur * joueurs[ 4 ];
    bool partieTerminee;

    public:

/*-------------------------------------------------------------------------------*/
// Constructeurs
/*-------------------------------------------------------------------------------*/
    Controleur();
    Controleur(int nbrJoueurs, Plateau* plateau, Joueur* joueurs[]);

/*-------------------------------------------------------------------------------*/
// Getters
/*-------------------------------------------------------------------------------*/
    int getNbrJoueur()const;

    Plateau* getPlateau() const;

    int getJoueurCourant() const;

    Joueur* getJoueurs(int i) const;

/*-------------------------------------------------------------------------------*/
// Setters
/*-------------------------------------------------------------------------------*/
    void setNbrJoueur(int nbrJoueurs);

    void setPlateau(Plateau* plateau);

    void setJoueurCourant(int joueurCourant);


/*-------------------------------------------------------------------------------*/
// Méthodes de la classe
/*-------------------------------------------------------------------------------*/
/**
 * @brief gère le déroulement de la partie
 * boucle prinicpale de la partie
 * Affiche plateau,
 * appèle gérerTour() tant que la partie n'est pas terminée
 * vérifier s'il y a victoire après chaque tour
 * appelle le joueur suivant
 */
    void runPartie();

/**
 * @brief Sélectionne le joueur suivant
 * 
 */
    void nextJoueur();

/**
 * @brief récupére l'action du joueur courant
 * valide l'action via le plateau
 * met à jour l'état de la partie
 * vérifie la condition de fin de partie
 * passe au joueur suivant
 */
    void gererTour();
    
/**
 * @brief Vérifie via le plateau si le coup proposé par le joueur est valide
 * Si le coup est valide, le coup est joué sur le plateau
 * sinon on demande au joueur de rejouer
 * @param joueur 
 */
    bool jouerCoup(Joueur* joueur); //gestion du coup joué par le joueur

/*-------------------------------------------------------------------------------*/
// Destructeurs
/*-------------------------------------------------------------------------------*/
    ~Controleur()= default; // Ne delete pas plateau ni joueurs : ils ne sont pas possédés ici.

};